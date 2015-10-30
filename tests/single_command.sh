#!/bin/sh
# single_command.sh
# tests bin/rshell with single commands

# Makes bin/rshell via Makefile
make
echo "Single Command Test"

# Test 1: One single command
echo -e "Test 1: Single command - echo \"Hello world\"\n"
bin/rshell << 'EOF'
echo "Hello world"
exit
EOF
echo -e "\n"

# Test 2: Multiple single commands (3)
echo -e "Test 2: Multiple single commands - Set 1 (3 commands)\n"
bin/rshell << 'EOF'
echo "Hello world"
ls
git status
exit
EOF
echo -e "\n"

# Cleans up the bin/rshell
make clean;
