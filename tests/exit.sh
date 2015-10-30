#!/bin/sh
# exit.sh
# tests bin/rshell with variations of exit command

# Makes the rshell executable
make
echo -e "Exit Command Test"

# Test 1: Tests exit by itself
echo -e "Test 1: Exit Command - Exit/Itself"
bin/rshell << EOF
exit
EOF
echo -e "\n"

# Test 2: Tests exit after single command
echo -e "Test 2: Exit Command - Exit/Single Command"
bin/rshell << EOF
echo "Hello world"
exit
EOF
echo -e "\n"

# Test 3: Tests exit after multiple commands
echo -e "Test 3: Exit Command - Exit/Multiple Command"
bin/rshell << EOF
echo "Hello world" && ls -a || mkdir test; git status
exit
EOF
echo -e "\n"

# Test 4: Tests exit at end of multiple command
echo -e "Test 4: Exit Command - Exit/Multiple Command_End"
bin/rshell << EOF
echo "Hello world" || mkdir test; echo "Let's leave" && exit
EOF
echo -e "\n"

# Test 5: Tests exit inside multiple commands
echo -e "Test 5: Exit Command - Exit/Multiple Command_Mid"
bin/rshell << EOF
echo "Hello world" && exit; echo "So interesting" || echo "What a bummer"
EOF
echo -e "\n"

# Test 6: Tests exit with commented command
echo -e "Test 6: Exit Command - Exit/Comment Command"
bin/rshell << EOF
echo "Hello world"
#exit
echo "This is nice"
exit
EOF
echo -e "\n"

# Test 7: Tests exit with exit in a quotation
echo -e "Test 7: Exit Command - Exit/\"exit\"_in-argument"
bin/rshell << EOF
echo "Hello world"; echo "Let us leave" && "Exit stage right"; git status
echo "No, not that exit" || exit
EOF
echo -e "\n"

# Cleans and exits
make clean
