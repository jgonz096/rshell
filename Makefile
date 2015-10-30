#Makefile

#Variables
COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic
OBJS = $(RSHELL)
RSHELL = src/rshell.cpp

#Targets
all: src/main.cpp $(RSHELL) 
	mkdir bin
	$(COMPILE) $(FLAGS) -o bin/rshell src/main.cpp $(OBJS)
rshell: src/rshell.cpp src/rshell.h
	mkdir bin
	$(COMPILE) $(FLAGS) -o bin/rshell src/main.cpp $(RSHELL)

clean:
	rm bin/rshell; rmdir bin
