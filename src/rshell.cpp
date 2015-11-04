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
//  parseCommand(string& input, char line[][256], char* argv[][64]) - 
//      parses out whitespace and puts charaters from string into array of char
void Rshell::parseCommand(string& input, char line[][256], char* argv[][64])
{
    unsigned row = 0;
    unsigned col = 0;
    bool quote = false;     //  Has a flag if the argument is in quotations
    clearArray(line);       //  Cleans array

    //  Parses string into the array (takes out whitespace)
    for(unsigned i = 0; i < input.size(); ++i)
    {
        if(!quote)
        {
            if(input.at(i) == '#')  //  Finishes with a comment
            {
                break;
            }
            if((input.at(i) == ' ') || (input.at(i) == '\t') || 
                (input.at(i) == '\n'))  //  Replaces whitespace with ' ' if dne
            {
                if((col > 0) && 
                    !((input.at(i + 1) == '&') || 
                    (input.at(i + 1) == '|') ||
                    (input.at(i + 1) == ';')))  //  Makes sure !connector
                {
                    if(line[row][col-1] != ' ')
                    {
                        line[row][col] = ' ';
                        ++col;
                    }
                }
            }
            else if(input.at(i) == ';')     //  Treat ';' as a newline
            {
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
        else    //  Character is in quotes
        {
            line[row][col] = input.at(i);
            col++;
            if(input.at(i) == '"')
            {
                quote = false;
            }
        }
    } 

    //  Sets up the argv array
    row = 0;
    col = 0;
    quote = false;
    clearArrayP(argv);


    //  Looks thrugh lin eand replaces any ' ' with \0'
    for(unsigned i = 0; line[i][0] != '\0'; ++i)
    {
        for(unsigned j = 0; line[i][j] != '\0'; ++j)
        {
            if(j == 0)  //  Gets the command
            {
                argv[row][col] = &line[i][j];
                ++col;
            }
            if(!quote && (line[i][j] == ' '))   //  Replaces space with '\0'
            {
                line[i][j] = '\0';
                argv[row][col] = &line[i][j + 1];
                ++col;
            }
            if(line[i][j] == '"')   //  Triggers quotes
            {
                quote = !quote;
            }    
        }
        ++row;      //  Goes to the next row
        col = 0;
    }

   //  Shows all addresses in argv
    for(unsigned i = 0; argv[i][0] != '\0'; ++i)
    {
        cout << "Argument " << i << ": " << argv[row] << endl;   
        for(unsigned j = 0; argv[i][j] != '\0'; ++j)
        {
            cout << "Argument [" << i << "][" << j << "]: " << argv[i][j]
                    << endl;
        }
        cout << endl;
    } 
    return;
}

//  void parseConnect(string&, unsigned, char [][], char, unsigned&, unsigned&)-
//      checks if an '&' or '|'  is a connector or not
void Rshell::parseConnect(string& input, unsigned pos, char line[][256], char con, unsigned& row, unsigned& col)
{
    if(col == 1)
    {
        line[row][col] = input.at(pos);
        col++;
        if(line[row][0] == con)         //  if prev char is connector
        {
            row++;
            col = 0;
        }
    }
    else 
    {
        if(input.at(pos + 1) == con)    //  if next char is connector
        {
            row++;
            col = 0;
        }
        line[row][col] = input.at(pos);
        col++;
    }
    return;
}

//  void clearArray(char line[100][256]) - puts '\0' for all spots in the array
void Rshell::clearArray(char line[][256])
{
    for(unsigned row = 0; line[row][0] != '\0'; ++row)
    {
        for(unsigned col = 0; col < 256; ++col)
        {
            line[row][col] = '\0';
        }
    }
    return;
}

//  void clearArrayP(char* argv[][]) - puts '\0' for all spots in the pointer
//      array
void Rshell::clearArrayP(char* argv[][64])
{
    for(unsigned row = 0; argv[row][0] != '\0'; ++row)
    {
        for(unsigned col = 0; argv[row][col] != '\0'; ++col)
        {
            argv[row][col] = '\0';
        }
    }
    return;
}

//  void executeCommand(char* argv[][]) - takes the array of commands and 
//      executes them
void Rshell::executeCommand(char* argv[][64])
{
    pid_t pid;
    int status;
    bool conA = false;  //  '&&'
    bool conB = false;  //  '||'
    unsigned prev = 0;
    bool success = false;   //  If connector succeeds
    
    for(unsigned i = 0; argv[i][0] != '\0'; ++i)
    {
        if ((pid = fork()) < 0)
        {
            cout << "Error: forking child process failed\n";
	    exit(1);
        }
        else if (pid == 0)
        {
	    if(execvp(*argv[i], argv[i]) < 0)
	    {
	        cout << "Error: exec failed\n";
	        exit(1);
	    }
        }
        else
        {
            while(wait(&status) != pid)
	    {
	        ;
	    }
        }
    }
    return;
}

