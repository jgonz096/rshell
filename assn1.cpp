#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <vector>
using namespace std;

void myFork()
{
	pid_t pid = fork();
	if(pid < 0)
	{
		cout << "Fork Failed" << endl;
		exit(1);
	}
	else if (pid == 0)
	{
		cout << "Child: I'm the child: " << pid << endl;
	}
	else if (pid > 0)
	{
		cout << "Parent: I'm the parent: " << pid << endl;
	}
}

void myWait()
{
	pid_t c_pid, pid;
	int status;
	c_pid = fork();
	
	if(pid < 0)
	{
		cout << "Fork failed" << endl;
		exit(1);
	}
	else if(c_pid == 0)
	{
		pid = getpid();
		
		//printf("Child: %d: I'm the child\n", pid, c_pid);
		cout << "Child: " << pid << ": I'm the child\n" << endl;
		cout << "Child: sleeping for 3 seconds \n" << endl;
		
		sleep(3);
		exit(12);
	}
	else if (c_pid > 0)
	{
		pid = wait(&status);

		if (WIFEXITED(status))
		{
			cout << "Parent: Child exited with status: ";
			cout << WEXITSTATUS(status) << endl;
		} 
	}
}

void myExec()
{
	char * args[2] = {"ls", NULL};
	pid_t c_pid, pid;
	int status;

	c_pid = fork();
	
	if(c_pid < 0)
	{
		cout << "Fork Failed" << endl;
		exit(1);
	}
	else if(c_pid == 0)
	{
		cout << "Child: executing ls" << endl;
		execvp(args[0], args);
		cout << "execve failed" << endl;
	}
	else if (c_pid > 0)
	{
		if((pid = wait(&status)) < 0)
		{
			cout << "Wait";
			exit(1);
		}
		cout << "Parent: finished" << endl;
	}
}

void removeSpace(string &input)
{
	while((input[0] == ' ') || (input[0] == '\t'))
	{
		input.erase(input.begin());
	}

}

void convertCommands(string &input, string &temp, int &loc, vector<string> &inputs)
{
	loc = input.find(";");
	while(loc != string::npos)
	{
		//cout << "loc: " << loc << endl;
		temp = input.substr(0,loc);
		//cout << "temp: " << temp << endl;
		input = input.substr(loc + 1);
		removeSpace(input);
		//cout << "input: " << input << endl;
		inputs.push_back(temp);
		loc = input.find(";");
		//cout << temp << endl << input << endl;
	}
	if((!input.empty()) && (input != "exit"))
	{
		removeSpace(input);
		temp = input;
		input.clear();
		inputs.push_back(temp);
	}
	if(input == "exit")
	{
		inputs.push_back(input);
	}

}

void printVector(vector<string> &inputs)
{
	for(int i = 0; i < inputs.size(); i++)
	{
		cout << inputs.at(i) << endl;
	}	
}

int main(int argc, char * argv[])
{
	string input = "";
	string temp;
	vector<string>inputs;
	int loc;
	//myFork();
	while(input != "exit")
	{
		//myFork();
		cout << "$ ";
		getline(cin, input);
		removeSpace(input);
		convertCommands(input,temp,loc,inputs);
		//myWait();
		//myExec();
		printVector(inputs);
		inputs.clear();
	}
	return 0;
}
