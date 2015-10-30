#README
# CS100 - Homework 1
<h1>rshell - Writing a Basic Command Shell</h1>
<p>In this project, we will try to build a basic command shell using C++ source code.</p> 
<p>This command shell is will allow print a command prommpt ($) that will then read in a command on one line. The command will take in an <strong>exectuable</strong> program in the <strong>PATH</strong> as well as an <strong>argumentList</strong>.</p>
<p>In addition we will have a few connectors to run multiple commands.</p>
<ul>
    <li>If a command is followed by <strong>,</strong> then the next command will always be executed.</li>
    <li>If a command is followed by <strong>&&</strong>, then the next command will only be executed if the first one succeeds.</li>
    <li>If the command is followed by <strong>||</strong>, then the next command will only be executed if the first one fails.</li>
</ul>

<h2>Source Files</h2>
<h3>main.cpp</h3>
<p>Acts as a testing area for various functions as well as the main bash. The exit has already been dealt well.</p>

<h3>rshell.cpp/rshell.h</h3>
<p>The rshell class will be used to parse out commands and their arguments that are directed into the shell. We will also find the connectors and be able to parse those into commands as well.</p> 

<p>We also have the following functions in order for our shell to work:</p>

<h4>Input Parser</h4>
<p>After receiving user input from the main.cpp, we need to parse out the commands to make sure that we get the command, its flags, and any arguments it has. We will also need to check for any connectors (',', '&&', and '||').</p>
<ul>
    <li><em>void removeSpace(string input)</em> - removes extraneous whitespace from <em>input</em>.</li>
    <li><em>void convertCommands(string &input, vector<string> &inputs)</em> - takes in the commands from the <em>input</em> and parses them into a vector of <em>inputs</em></li>
</ul>
