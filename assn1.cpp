#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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

int main()
{
	string input = "";
	//myFork();
	while(input != "exit")
	{
		//myFork();
		cout << "$ ";
		cin >> input;
		//myWait();
		myExec();
	}
	return 0;
}
