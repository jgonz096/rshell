#ifndef RSHELL_H
#define RSHELL_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Rshell
{
    public:
        //  Class constructor
        Rshell();
        //  Parses command inputs
        void parseCommand(string& input, char line[100][256], char* argv[64][64]);
        void parseConnect(string&, unsigned, char line[100][256], char, unsigned&, unsigned&);
        void clearArray(char line[100][256]);
        void clearArrayP(char* argv[][64]);
	void executeCommand(char* argv[][64]);
};
#endif  //  RSHELL_H
