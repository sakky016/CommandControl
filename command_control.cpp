#include"command_control.h"
#include<iostream>

CommandControl::~CommandControl()
{

}

CommandControl& CommandControl::GetInstance()
{
    static CommandControl instance;
    return instance;
}

int CommandControl::registerCommand(const string & commandName, void (*fn)())
{
    command_t command;
    command.command_fn = fn;
    command.index = ++m_totalCommands;
    command.name = commandName;

    m_commandMap[commandName] = command;
    
    return m_totalCommands;
}

int CommandControl::validateCommand(const string &  commandName)
{
    auto it = m_commandMap.find(commandName);
    if (it != m_commandMap.end())
    {
        return it->second.index;
    }

    return -1;
}

void CommandControl::startCommandControl()
{
    while (1)
    {
        string commandName;
        int commandIndex = -1;
        bool retval = false;

        cout << "$ ";
        cin >> commandName;

        commandIndex = this->validateCommand(commandName);
        if (commandIndex == -1)
        {
            printf("'%s' command not found!\n", commandName.c_str());
            continue;
        }

        retval = this->doCommand(commandName);

    }// End of command line processing
}

bool CommandControl::doCommand(const string & commandName)
{
    void (*fn_ptr)() = m_commandMap[commandName].command_fn;
    (*fn_ptr)();

    return true;
}