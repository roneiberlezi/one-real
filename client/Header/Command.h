#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <stdio.h>
#include <cstdlib>

class Command
{
public:
	virtual bool execute(int argc, char* argv[]) = 0;
};

class CommandHelp : public Command{
public:
    bool execute(int argc, char* argv[]);
};

class CommandSave : public Command{
public:
	bool execute(int argc, char* argv[]);
};

class CommandLoad : public Command{
public:
    bool execute(int argc, char* argv[]);
};

class CommandResize : public Command{
public:
    bool execute(int argc, char* argv[]);
};

class CommandNew : public Command{
public:
	bool execute(int argc, char* argv[]);
};

class CommandSetPage : public Command{
public:
	bool execute(int argc, char* argv[]);
};

class CommandQuit : public Command{
public:
	bool execute(int argc, char* argv[]);
};

class CommandSpeed : public Command{
public:
    bool execute(int argc, char* argv[]);
};

class CommandPosition : public Command{
public:
    bool execute(int argc, char* argv[]);
};

class CommandLayer : public Command{
public:
    bool execute(int argc, char* argv[]);
};

class CommandFill : public Command{
public:
    bool execute(int argc, char* argv[]);
};

class CommandPlayerDemo : public Command{
public:
    bool execute(int argc, char* argv[]);
};

class CommandConnect : public Command{
public:
	bool execute(int argc, char* argv[]);
};

class CommandDisconnect : public Command{
public:
	bool execute(int argc, char* argv[]);
};

class CommandDemoServer : public Command{
public:
    bool execute(int argc, char* argv[]);
};

#endif