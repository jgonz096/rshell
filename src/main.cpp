/** 
 * Name: Rebecca Hom
 * This is the main file that will be used to run the rshell.
 * Tests the system calls
 *
* */
#include "rshell.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    Rshell rshell = Rshell();
    // Initial variables for taking in commands
    string input = "";
    //  vector<string> inputs;
    char line[100][256];
    char *argv[64]; 

    //  Gets the command(s) from user input until exit
    while(input != "exit")
    {
        cout << "$ ";
        getline(cin, input);
        rshell.parseCommand(input, line, argv);
    } 
    return 0;
}
