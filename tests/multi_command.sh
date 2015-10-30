#!/bin/sh
# multi_command.sh
# tests bin/rshell with multiple commands

# Makes bin/rshell
make
echo "Multiple Commands Test"

# Test 1: Tests the ","
echo -e "Test 1: Multiple Commands - \";\"\n"
bin/rshell << 'EOF'
echo "Hello world!"; ls
echo "This is another set"; cal; ls
echo "This is the third set"; git status; ls; git log
exit
EOF
echo -e "\n"

# Test 2: Tests the "&&"
echo -e "Test 2: Multiple Commands - \"&&\"\n"
bin/rshell << 'EOF'
echo "Hello world" && echo "And all of its inhabitants"
ls && echo "One echo" && echo "Two echoes"
cd && echo "A middle connector" && git status && ls
exit
EOF
echo -e "\n"

# Test 3: Tests the "||"
echo -e "Test 3: Multiple Commands - \"||\"\n"
bin/rshell << 'EOF'
echo "Hello world" || echo "It's today!"
ls || echo "One echo" || "Two echoes"
cd || echo "A middle connection" || git status
exit
EOF
echo -e "\n"

# Test 4: Tests a mix of connectors
echo -e "Test 4: Multiple Commands - Multiple connectors"
bin/rshell << 'EOF'
echo "Hello world!" || echo "We have a problem"; ls
git status && git log || echo "Error playing with git"
ls; cd && "AND connector worked"
exit
EOF

# Cleans up the area
make clean
