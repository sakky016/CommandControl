#ifndef _COMMAND_CONTROL_H_
#define _COMMAND_CONTROL_H_
#include<string>
#include <unordered_map> 

using namespace std;

// Command structure
typedef struct command_tag
{
    int index;
    string name;
    void (*command_fn)();
}command_t;


// Central Command Control
class CommandControl
{
private:
    int m_totalCommands;                                    // Total registered commands in the system
    unordered_map<string, command_t> m_commandMap;          // Map of  commandName and command_t

    CommandControl() {};                                    // We are going to use GetInstance to create object

public:
    CommandControl(CommandControl const &) = delete;        // Don't implement
    void operator=(CommandControl const&) = delete;         // Don't implement
    ~CommandControl();
    static CommandControl& GetInstance();
    int registerCommand(const string & commandName, void(*fn)());
    int validateCommand(const string &  commandName);
    bool doCommand(const string & commandName);
    void startCommandControl();
};

#endif