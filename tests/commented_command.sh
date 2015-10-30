#!/bin/sh
# commented_command.sh
# tests bin/rshell with commented commands

# Makes the rshell executable
make
echo "Commented Commands Test"

# Test 1: commented command at the end of single command
echo -e "Test 1: Commented Command - Single Command/Comment at End"
bin/rshell << 'EOF'
echo "Hello world"
ls #-a
exit
EOF
echo -e "\n"

# Test 2: commented command at end of multiple command
echo -e "Test 2: Commented Command - Multiple Command/Comment at End"
bin/rshell << 'EOF'
echo "Hello world"; ls #-a
exit
EOF
echo -e "\n"

# Test 3: commented command in multple command
echo -e "Test 3: Commented Command - Multiple Command/Comment"
bin/rshell << 'EOF'
#echo "Failed comment" && echo "Nope, still wrong"
echo "Hello world"; #ls -a || cd
ls -a; echo hello && mkdir test || echo world;# git status
exit
EOF

# Cleans up the tests
make clean
