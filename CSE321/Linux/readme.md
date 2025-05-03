# Linux Shell Commands Practice Guide

System and User Information
Accessing Command Manuals
Creating Files
File Operations
Directory and File Listings
File and Directory Permissions
Mathematical Operations
Redirection
Calendar
File Viewing
Piping
Pattern Searching with grep
Finding Files with find
Creating Links


System and User Information
Commands:

uname: Displays system information (e.g., kernel name).
whoami: Shows the current user's username.

Examples:
# Display system name
uname
# Output: Linux

# Show current user
whoami
# Output: user1

# Combine system and user info
echo "System: $(uname), User: $(whoami)"
# Output: System: Linux, User: user1


Accessing Command Manuals
Command:

man: Displays the manual page for a specified command.

Examples:
# View manual for uname
man uname
# Scroll with arrow keys, quit with 'q'

# View manual for ls and search for sorting options
man ls
# Type '/sort' and press Enter


Creating Files
Commands:

touch: Creates empty files.
cat: Creates files with content, displays file contents, or concatenates files.

Examples:
# Create empty files
touch file1.txt file2.txt
ls
# Output: file1.txt file2.txt

# Create a file with content
cat > test.txt
Hello world
I love Linux
# Press Ctrl+D to save
cat test.txt
# Output:
# Hello world
# I love Linux

# Concatenate files
echo "First file" > sample1.txt
echo "Second file" > sample2.txt
cat sample1.txt sample2.txt > newsample.txt
cat newsample.txt
# Output:
# First file
# Second file


File Operations
Commands:

cp: Copies files or directories.
rm: Removes files or directories.
mv: Moves or renames files or directories.

Examples:
# Copy a file
cp test.txt test_copy.txt
ls
# Output: test.txt test_copy.txt

# Copy a directory recursively
mkdir mydir
touch mydir/file3.txt
cp -r mydir mydir_copy
ls mydir_copy
# Output: file3.txt

# Remove a file with prompt
rm -i test_copy.txt
# Respond 'y' to confirm

# Move and rename a file
mv newsample.txt renamed_sample.txt
ls
# Output: renamed_sample.txt


Directory and File Listings
Command:

ls: Lists directory contents with options (-a, -A, -h, -l, -S).

Examples:
# Basic listing
ls
# Output: file1.txt file2.txt mydir

# Show hidden files
touch .hidden.txt
ls -a
# Output: . .. .hidden.txt file1.txt file2.txt mydir

# Long listing format
ls -l
# Output: -rw-r--r-- 1 user1 group ... file1.txt

# Sort by file size
ls -lS
# Output: Files sorted by size


File and Directory Permissions
Command:

chmod: Changes file or directory permissions (symbolic or numeric).

Examples:
# View permissions
ls -l test.txt
# Output: -rw-r--r-- ...

# Add read/write for group and others
chmod go+rw test.txt
ls -l test.txt
# Output: -rw-rw-rw- ...

# Set permissions numerically
chmod 744 test.txt
ls -l test.txt
# Output: -rwxr--r-- ...

# Remove execute for group and others
chmod go-x mydir
ls -ld mydir
# Output: drwxr-xr-x ...


Mathematical Operations
Commands:

bc: Interactive calculator for arithmetic, floating-point, and base conversions.
factor: Finds prime factors of a number.

Examples:
# Basic arithmetic
bc
10 + 5
8.25 * 2
quit
# Output: 15
#         16.50

# Set scale for precision
bc
scale=2
10 / 3
quit
# Output: 3.33

# Base conversion
bc
obase=16
ibase=2
11010011
quit
# Output: D3

# Factorize a number
factor 15
# Output: 15: 3 5


Redirection
Commands:

<: Input redirection.
>: Output redirection (overwrites).
>>: Append output.

Examples:
# Output redirection
ls -l > note.txt
cat note.txt
# Output: Directory listing

# Append output
echo "Additional line" >> note.txt
cat note.txt
# Output: Original listing + "Additional line"

# Input redirection
wc -l < note.txt
# Output: Number of lines


Calendar
Command:

cal: Displays a calendar.

Examples:
# Current month
cal
# Output: Calendar for May 2025

# Specific year
cal 2012
# Output: Calendar for 2012

# Specific month
cal feb 2001
# Output: Calendar for February 2001


File Viewing
Commands:

head: Displays the first 10 lines of a patient.
tail: Displays the last 10 lines of a patient.
sort: Sorts lines of text files.
wc: Counts lines, words, and bytes.

Examples:
# View first 5 lines
head -n 5 note.txt
# Output: First 5 lines

# View last 3 lines
tail -n 3 note.txt
# Output: Last 3 lines

# Sort file contents
echo -e "banana\napple\ncherry" > fruits.txt
sort fruits.txt
# Output:
# apple
# banana
# cherry

# Count lines and words
wc -lw test.txt
# Output: Lines and words in test.txt


Piping
Operator:

|: Pipes output of one command as input to another.

Examples:
# View lines 15-20
head -20 note.txt | tail -5
# Output: Lines 15-20

# Sort and count files
ls | sort | wc -l
# Output: Number of files

# Filter with grep
ls -l | grep txt
# Output: Lines with "txt"


Pattern Searching with grep
Command:

grep: Searches for patterns in files or input.

Examples:
# Basic search
grep "Hello" test.txt
# Output: Hello world

# Case-insensitive search
grep -i "hello" test.txt
# Output: Hello world

# Count matches
grep -c "world" test.txt
# Output: 1

# Show line numbers
grep -n "Linux" test.txt
# Output: 2:I love Linux


Finding Files with find
Command:

find: Searches for files in a directory hierarchy.

Examples:
# List all files
find .
# Output: All files and directories

# Search by name
find . -name "*.txt"
# Output: All .txt files

# Search by type
find . -type d
# Output: All directories

# Execute an action
find . -type f -name "*.txt" -exec chmod a+rwx {} \;
# Output: Changes permissions of .txt files


Creating Links
Command:

ln: Creates hard or symbolic links.

Examples:
# Create a hard link
ln test.txt test_link.txt
ls -l
# Output: Same inode for test.txt and test_link.txt

# Create a symbolic link
ln -s test.txt test_symlink.txt
ls -l
# Output: test_symlink.txt -> test.txt




