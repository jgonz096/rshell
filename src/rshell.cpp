#include "rshell.h"

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <vector>
#include <sstream>

using namespace std;

//  Constructors
//  Default constructor (creates an Rshell object for commands)
Rshell::Rshell()
{}

//  Rshell functions
//  These functions takes command input from the user and parses them
//  parseCommand(string& input, char line[][], char **argv) - 
//      parses out whitespace and puts charaters from string into array of char
void Rshell::parseCommand(string& input, char line[100][256],  char **argv)
{
    unsigned row = 0;
    unsigned col = 0;
    bool quote = false;     //  Has a flag if the argument is in quotations

    //  Parses string into the array (takes out whitespace)
    for(unsigned i = 0; i < input.size(); ++i)
    {
        //  char con;
        if(input.at(i) == '#')  //  Aborts early from comments
        {
            break;
        }
        if(!quote && ((input.at(i) != ' ') || 
            (input.at(i) != '\t') || 
            (input.at(i) != '\n')))     //  If the pos in string !=  whitespace
        {
            if(input.at(i) == ';')      //  Treat ';' as a newline
            {
                line[row][col] = '\0';
                row++;
                col = 0;
            }
            else if(input.at(i) == '&')     //  Checks for &&
            {
                parseConnect(input, i, line, '&', row, col);
            }
            else if(input.at(i) == '|')     //  Checks for ||
            {
                parseConnect(input, i, line, '|', row, col);
            }
            else    //  Any other character
            {
                line[row][col] = input.at(i);
                col++;
                if(input.at(i) == '"')      //  Checks for "
                {
                    quote = true;
                }
            }
        }
        else
        {
            line[row][col] = input.at(i);
            col++;
            if(input.at(i) == '"')
            {
                quote = false;
            }
        }
    } 

    //  Once all cmd retrieved->end array with last row having '\0'
    row++;
    line[row][0] = '\0';
    return;
}

//  void parseConnect(string&, unsigned, char [][], char, unsigned&, unsigned&)-
//      checks if an '&' or '|'  is a connector or not
void Rshell::parseConnect(string& input, unsigned pos, char line[100][256], char con, unsigned& row, unsigned& col)
{
    if(col == 1)
    {
        line[row][col] = input.at(pos);
        col++;
        if(line[row][0] == con)     //if prev char is an & -> &&
        {
            line[row][col] = '\0';
            row++;
            col = 0;
        }
    }
    else if(input.at(pos + 1) == con)
    {
        line[row][col] = '\0';
        row++;
        col = 0;
        line[row][col] = input.at(pos);
    }
    else
    {
        line[row][col] = input.at(pos);
        col++;
    }
    return;
}
