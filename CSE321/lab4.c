#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 5
#define MAX_RESOURCES 5
#define MAX_NAME_LEN 20

typedef enum {
    READ = 1,
    WRITE = 2,
    EXECUTE = 4
} Permission;

typedef struct {
    char name[MAX_NAME_LEN];
} User;

typedef struct {
    char name[MAX_NAME_LEN];
} Resource;

typedef struct {
    char username[MAX_NAME_LEN];
    int permissions;
} ACLEntry;

typedef struct {
    Resource resource;
    ACLEntry acl[MAX_USERS];
    int acl_count;
} ACLControlledResource;

typedef struct {
    char resource_name[MAX_NAME_LEN];
    int permissions;
} Capability;

typedef struct {
    User user;
    Capability capabilities[MAX_RESOURCES];
    int capability_count;
} CapabilityUser;

void printPermissions(int perm) {
    if (perm == 0) {
        printf("None");
        return;
    }
    int first = 1;
    if (perm & READ) {
        printf("Read");
        first = 0;
    }
    if (perm & WRITE) {
        if (!first) printf(", ");
        printf("Write");
        first = 0;
    }
    if (perm & EXECUTE) {
        if (!first) printf(", ");
        printf("Execute");
    }
}

int hasPermission(int userPerm, int requiredPerm) {
    return (userPerm & requiredPerm) == requiredPerm;
}

void checkACLAccess(ACLControlledResource *res, const char *userName, int perm) {
    for (int i = 0; i < res->acl_count; i++) {
        if (strcmp(res->acl[i].username, userName) == 0) {
            if (hasPermission(res->acl[i].permissions, perm)) {
                printf("ACL Check: User %s requests ", userName);
                printPermissions(perm);
                printf(" on %s: Access GRANTED\n", res->resource.name);
            } else {
                printf("ACL Check: User %s requests ", userName);
                printPermissions(perm);
                printf(" on %s: Access DENIED\n", res->resource.name);
            }
            return;
        }
    }
    printf("ACL Check: User %s has NO entry for resource %s: Access DENIED\n", userName, res->resource.name);
}

void checkCapabilityAccess(CapabilityUser *user, const char *resourceName, int perm) {
    for (int i = 0; i < user->capability_count; i++) {
        if (strcmp(user->capabilities[i].resource_name, resourceName) == 0) {
            if (hasPermission(user->capabilities[i].permissions, perm)) {
                printf("Capability Check: User %s requests ", user->user.name);
                printPermissions(perm);
                printf(" on %s: Access GRANTED\n", resourceName);
            } else {
                printf("Capability Check: User %s requests ", user->user.name);
                printPermissions(perm);
                printf(" on %s: Access DENIED\n", resourceName);
            }
            return;
        }
    }
    printf("Capability Check: User %s has NO capability for %s: Access DENIED\n", user->user.name, resourceName);
}

int main() {
    User users[MAX_USERS] = {{"Alice"}, {"Bob"}, {"Charlie"}, {"Dave"}, {"Eve"}};
    Resource resources[MAX_RESOURCES] = {{"File1"}, {"File2"}, {"File3"}, {"File4"}, {"Database"}};

    ACLControlledResource acl_resources[MAX_RESOURCES] = {
        {{"File1"}, {{"Alice", READ | WRITE}, {"Bob", READ}}, 2},
        {{"File2"}, {{"Bob", READ | EXECUTE}, {"Charlie", WRITE}}, 2},
        {{"File3"}, {{"Alice", EXECUTE}}, 1},
        {{"File4"}, {{"Dave", READ | WRITE}, {"Eve", READ}}, 2},
        {{"Database"}, {{"Eve", WRITE | EXECUTE}, {"Charlie", READ}}, 2}
    };

    CapabilityUser cap_users[MAX_USERS] = {
        {{"Alice"}, {{"File1", READ | WRITE}, {"File3", EXECUTE}}, 2},
        {{"Bob"}, {{"File1", READ}, {"File2", READ | EXECUTE}}, 2},
        {{"Charlie"}, {{"File2", WRITE}, {"Database", READ}}, 2},
        {{"Dave"}, {{"File4", READ | WRITE}}, 1},
        {{"Eve"}, {{"File4", READ}, {"Database", WRITE | EXECUTE}}, 2}
    };

    checkACLAccess(&acl_resources[0], "Alice", READ);
    checkACLAccess(&acl_resources[0], "Bob", WRITE);
    checkACLAccess(&acl_resources[1], "Charlie", EXECUTE); 
    checkACLAccess(&acl_resources[2], "Charlie", READ);
    checkACLAccess(&acl_resources[3], "Dave", WRITE);
    checkACLAccess(&acl_resources[4], " Eve", EXECUTE);
    checkACLAccess(&acl_resources[4], "Alice", READ);
    checkCapabilityAccess(&cap_users[0], "File1", WRITE);
    checkCapabilityAccess(&cap_users[1], "File2", EXECUTE);
    checkCapabilityAccess(&cap_users[2], "File2", READ);
    checkCapabilityAccess(&cap_users[3], "File4", READ);
    checkCapabilityAccess(&cap_users[4], "Database", WRITE);
    checkCapabilityAccess(&cap_users[0], "File4", READ);
    checkCapabilityAccess(&cap_users[2], "File3", EXECUTE);
    return 0;
}
