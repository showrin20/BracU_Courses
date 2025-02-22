

## [**🔹 Introduction to Linux Shell**](https://drive.google.com/drive/folders/1sgF89FZmPuiN0qJkhdJumGYu6iwQdPEX)
- Many people believe Linux is **command-based**, making it seem less **user-friendly**.  
- However, Linux supports a **Graphical User Interface (GUI)** and includes a **powerful shell**.  
- The shell allows users to **interact** with the system through commands.



### **1. System Information Commands**
```sh
uname             # Display system name
whoami           # Show current user
```

---

### **2. Manual and Help Commands**
```sh
man uname       # Show manual for the 'uname' command
man ls          # Show manual for the 'ls' command
```

---

### **3. File Creation Commands**
```sh
touch file1.txt         # Create an empty file
cat > file2.txt         # Create a file and allow text input (Ctrl+D to save)
```

---

### **4. File Viewing Commands**
```sh
cat file1.txt           # Display file contents
head file1.txt          # Show first 10 lines
head -5 file1.txt       # Show first 5 lines
tail file1.txt          # Show last 10 lines
tail -5 file1.txt       # Show last 5 lines
sort file1.txt          # Sort file contents
wc file1.txt            # Show line, word, and byte count
wc -l file1.txt         # Show only line count
wc -w file1.txt         # Show only word count
```

---

### **5. File Operations**
```sh
cp file1.txt copy_file1.txt    # Copy file
cp -i file1.txt copy_file1.txt # Prompt before overwrite
cp -r dir1 dir2                # Copy directories recursively

rm file1.txt           # Delete file
rm -i file1.txt        # Prompt before delete
rm -r dir1             # Remove directory and its contents

mv file1.txt file2.txt  # Rename or move a file
mv -i file1.txt file2.txt # Prompt before overwriting
```

---

### **6. Directory Management**
```sh
ls                  # List files in a directory
ls -a               # Show hidden files
ls -l               # Long listing format
ls -h               # Show human-readable sizes
ls -S               # Sort by file size
```

---

### **7. File Permissions**
```sh
chmod 777 file1.txt        # Full permissions to everyone
chmod go+rw file1.txt      # Give read & write to group and others
chmod a+rwx file1.txt      # Full access to all
chmod 555 file1.txt        # Read & execute for all
```

---

### **8. Mathematical Operations**
```sh
bc                      # Open calculator
factor 24               # Show prime factors (Output: 2 2 2 3)
```

---

### **9. Redirection and Piping**
```sh
cat file1.txt > file2.txt   # Redirect output to file2.txt (overwrite)
cat file1.txt >> file2.txt  # Append output to file2.txt
ls | grep "txt"             # List all .txt files
```

---

### **10. Searching Commands**
```sh
grep "pattern" file.txt       # Search for 'pattern' in file.txt
grep -i "pattern" file.txt    # Case insensitive search
grep -n "pattern" file.txt    # Show line numbers
grep -c "pattern" file.txt    # Count occurrences

find / -name "file.txt"        # Find file.txt in the system
find . -type d                # Find all directories
find . -type f                # Find all files
find /home/user -name "*.txt" # Find all .txt files in /home/user
```
