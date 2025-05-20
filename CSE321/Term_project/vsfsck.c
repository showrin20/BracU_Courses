#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 4096
#define TOTAL_BLOCKS 64
#define INODE_SIZE 256
#define INODES_PER_BLOCK (BLOCK_SIZE / INODE_SIZE)
#define INODE_TABLE_BLOCKS 5
#define DATA_BLOCK_START 8
#define MAX_INODES (INODE_TABLE_BLOCKS * INODES_PER_BLOCK)
#define MAX_DATA_BLOCKS (TOTAL_BLOCKS - DATA_BLOCK_START)
#define SUPERBLOCK_MAGIC 0xd34d

typedef struct {
    uint16_t magic;
    uint32_t block_size;
    uint32_t total_blocks;
    uint32_t inode_bitmap_block;
    uint32_t data_bitmap_block;
    uint32_t inode_table_block;
    uint32_t first_data_block;
    uint32_t inode_size;
    uint32_t inode_count;
    char reserved[4058];
} __attribute__((packed)) Superblock;

typedef struct {
    uint32_t mode;
    uint32_t uid;
    uint32_t gid;
    uint32_t size;
    uint32_t atime;
    uint32_t ctime;
    uint32_t mtime;
    uint32_t dtime;
    uint32_t links_count;
    uint32_t blocks;
    uint32_t block;
    uint32_t indirect_block;
    uint32_t double_indirect;
    uint32_t triple_indirect;
    char reserved[156];
} __attribute__((packed)) Inode;

uint8_t block[BLOCK_SIZE];

void read_block(FILE *fp, int block_num, void *buf) {
    fseek(fp, block_num * BLOCK_SIZE, SEEK_SET);
    fread(buf, BLOCK_SIZE, 1, fp);
}

void validate_superblock(Superblock *sb) {
    printf("Superblock\n");
    printf("Magic Number       : 0x%04x\n", sb->magic);
    printf("Block Size         : %u\n", sb->block_size);
    printf("Total Blocks       : %u\n", sb->total_blocks);
    printf("Inode Bitmap Block : %u\n", sb->inode_bitmap_block);
    printf("Data Bitmap Block  : %u\n", sb->data_bitmap_block);
    printf("Inode Table Start  : %u\n", sb->inode_table_block);
    printf("First Data Block   : %u\n", sb->first_data_block);
    printf("Inode Size         : %u\n", sb->inode_size);
    printf("Inode Count        : %u\n", sb->inode_count);
    printf("\n");

    if (sb->magic != SUPERBLOCK_MAGIC) printf("Invalid magic number: 0x%x\n", sb->magic);
    if (sb->block_size != BLOCK_SIZE) printf("Invalid block size: %u\n", sb->block_size);
    if (sb->total_blocks != TOTAL_BLOCKS) printf("Invalid total blocks: %u\n", sb->total_blocks);
    if (sb->inode_bitmap_block != 1) printf("Invalid inode bitmap block: %u\n", sb->inode_bitmap_block);
    if (sb->data_bitmap_block != 2) printf("Invalid data bitmap block: %u\n", sb->data_bitmap_block);
    if (sb->inode_table_block != 3) printf("Invalid inode table block: %u\n", sb->inode_table_block);
    if (sb->first_data_block != DATA_BLOCK_START) printf("Invalid first data block: %u\n", sb->first_data_block);
    if (sb->inode_size != INODE_SIZE) printf("Invalid inode size: %u\n", sb->inode_size);
    if (sb->inode_count == 0 || sb->inode_count > MAX_INODES)
        printf("Invalid inode count: %u\n", sb->inode_count);
}

int is_block_valid(uint32_t block_num) {
    return block_num >= DATA_BLOCK_START && block_num < TOTAL_BLOCKS;
}

void print_bitmap(uint8_t *bitmap, int bits, const char *label) {
    printf("%s Bitmap (%d bits)\n", label, bits);
    for (int i = 0; i < bits; i++) {
        printf("%d", (bitmap[i / 8] >> (i % 8)) & 1);
        if ((i + 1) % 32 == 0) printf("\n");
    }
    printf("\n");
}

int main() {
    FILE *fp = fopen("vsfs.img", "rb+");
    if (!fp) {
        perror("vsfs.img not found");
        return 1;
    }

    Superblock sb;
    read_block(fp, 0, &sb);
    validate_superblock(&sb);

    uint8_t inode_bitmap[BLOCK_SIZE];
    read_block(fp, sb.inode_bitmap_block, inode_bitmap);
    print_bitmap(inode_bitmap, sb.inode_count, "Inode");

    uint8_t data_bitmap[BLOCK_SIZE];
    read_block(fp, sb.data_bitmap_block, data_bitmap);
    print_bitmap(data_bitmap, TOTAL_BLOCKS, "Data");

    int data_block_ref[TOTAL_BLOCKS] = {0};

    printf("Inode Validation\n");
    for (int i = 0; i < sb.inode_count; i++) {
        int block_num = sb.inode_table_block + (i * INODE_SIZE) / BLOCK_SIZE;
        int offset = (i * INODE_SIZE) % BLOCK_SIZE;
        read_block(fp, block_num, block);
        Inode *inode = (Inode *)(block + offset);

        int used_in_bitmap = inode_bitmap[i / 8] & (1 << (i % 8));
        int is_valid_inode = (inode->links_count > 0 && inode->dtime == 0);

        if (used_in_bitmap || is_valid_inode) {
            printf("Inode %d [valid=%s, bitmap=%s]\n", i,
                   is_valid_inode ? "Valid" : "Invalid",
                   used_in_bitmap ? "1" : "0");

            if (is_valid_inode) {
                printf("  Mode: %x, Size: %u, Links: %u\n", inode->mode, inode->size, inode->links_count);
                printf("  Blocks: direct=%u indirect=%u double=%u triple=%u\n",
                       inode->block, inode->indirect_block,
                       inode->double_indirect, inode->triple_indirect);
            }
        }

        if (used_in_bitmap && !is_valid_inode)
            printf("Inode %d marked used in bitmap but invalid\n", i);
        if (!used_in_bitmap && is_valid_inode)
            printf("Inode %d not marked in bitmap but valid\n", i);

        if (!is_valid_inode) continue;

        uint32_t blocks[] = {inode->block, inode->indirect_block,
                             inode->double_indirect, inode->triple_indirect};
        for (int j = 0; j < 4; j++) {
            if (blocks[j] == 0) continue;
            if (!is_block_valid(blocks[j]))
                printf("Inode %d has bad block pointer: %u\n", i, blocks[j]);
            else {
                if (data_block_ref[blocks[j]] > 0)
                    printf("Block %u is referenced by multiple inodes\n", blocks[j]);
                data_block_ref[blocks[j]]++;

                // Check and correct data bitmap
                int bit_pos = blocks[j] % 8;
                int byte_pos = blocks[j] / 8;
                if (!(data_bitmap[byte_pos] & (1 << bit_pos))) {
                    printf("Block %u used by inode %d but not marked in data bitmap - correcting...\n", blocks[j], i);
                    data_bitmap[byte_pos] |= (1 << bit_pos);
                    // Write the updated data bitmap back to the file
                    fseek(fp, sb.data_bitmap_block * BLOCK_SIZE + byte_pos, SEEK_SET);
                    fwrite(&data_bitmap[byte_pos], 1, 1, fp);
                    printf("Proof of correction: Block %u is now marked as used in the data bitmap.\n", blocks[j]);
                    fflush(fp);
                }
            }
        }
    }

    printf("Orphan Data Blocks\n");
    for (int i = DATA_BLOCK_START; i < TOTAL_BLOCKS; i++) {
        if ((data_bitmap[i / 8] & (1 << (i % 8))) && data_block_ref[i] == 0)
            printf("Block %d marked used in bitmap but not referenced\n", i);
    }

    printf("\nUpdated Data Bitmap (%d bits)\n", TOTAL_BLOCKS);
    read_block(fp, sb.data_bitmap_block, data_bitmap);
    print_bitmap(data_bitmap, TOTAL_BLOCKS, "Data");

    fclose(fp);
    printf("\nCheck complete.\n");
    return 0;
}
