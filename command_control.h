#ifndef _COMMAND_CONTROL_H_
#define _COMMAND_CONTROL_H_
#include<string>
#include <unordered_map> 
#include<list>

using namespace std;

const int HISTORY_MAX = 20;

//*******************************************************************************************
// Command structure
//*******************************************************************************************
typedef struct command_tag
{
    int index;
    string name;
    void (*command_fn)();
}command_t;

//*******************************************************************************************
// Central Command Control class
//*******************************************************************************************
class CommandControl
{
private:
    bool m_initialized;
    int m_totalCommands;                                               // Total registered commands in the system
    unordered_map<string, command_t> m_commandMap;                     // Map of  commandName and command_t
    list<string> m_commandHistoryList;

    CommandControl();                                               // We are going to use GetInstance to create object

public:
    CommandControl(CommandControl const &) = delete;                   // Don't implement
    void operator=(CommandControl const&) = delete;                    // Don't implement
    ~CommandControl();
    static CommandControl& GetInstance();
    void initializeCommandControl();
    void displayRegisteredCommands();
    int registerCommand(const string & commandName, void(*fn)());
    int validateCommand(const string &  commandName);
    bool doCommand(const string & commandName);
    void startCommandControl();
    void addTohistory(const string & commandName);
    void showCommandHistory();
};

#endif
