#include"command_control.h"
#include<iostream>

//******************************************************************************************
// @name                    : displayRegisteredCommandsExt
//
// @description             : Displays the list of registered commands. This is just a wrapper
//                            function which calls displayRegisteredCommands() of the 
//                            CommandControl class
//
// @returns                 : Nothing
//********************************************************************************************
void displayRegisteredCommandsExt()
{
    CommandControl::GetInstance().displayRegisteredCommands();
}

//******************************************************************************************
// @name                    : showCommandHistoryExt
//
// @description             : Displays the list of previously executed commands. This is just a wrapper
//                            function which calls showCommandHistory() of the 
//                            CommandControl class
//
// @returns                 : Nothing
//********************************************************************************************
void showCommandHistoryExt()
{
    CommandControl::GetInstance().showCommandHistory();
}

//******************************************************************************************
// @name                    : CommandControl
//
// @description             : Private constructor. Object to be created only via GetInstance()
//
// @returns                 : Nothing
//********************************************************************************************
CommandControl::CommandControl()
{
    initializeCommandControl();
}


//******************************************************************************************
// @name                    : ~CommandControl
//
// @description             : Destructor
//
// @returns                 : Nothing
//********************************************************************************************
CommandControl::~CommandControl()
{

}

//******************************************************************************************
// @name                    : GetInstance
//
// @description             : Fetches an instance of CommandControl. This provides instance
//                            of a singleton class.
//
//
// @returns                 : Instance to CommandControl
//********************************************************************************************
CommandControl& CommandControl::GetInstance()
{
    static CommandControl instance;
    return instance;
}

//******************************************************************************************
// @name                    : initializeCommandControl
//
// @description             : initializeCommandControl.
//
// @returns                 : Nothing
//********************************************************************************************
void CommandControl::initializeCommandControl()
{
    this->registerCommand("show", &displayRegisteredCommandsExt);
    this->registerCommand("history", &showCommandHistoryExt);
    
}

//******************************************************************************************
// @name                    : displayRegisteredCommands
//
// @description             : Displays the list of registered commands.
//
// @returns                 : Nothing
//********************************************************************************************
void CommandControl::displayRegisteredCommands()
{
    printf("\nRegistered commands:\n");
    for (auto it = m_commandMap.begin(); it != m_commandMap.end(); it++)
    {
        printf("* %s\n", it->second.name.c_str());
    }

    printf("\n");
}

//******************************************************************************************
// @name                    : registerCommand
//
// @description             : Registers a command and corresponding function pointer.
//
// @param commandName       : Command name string
// @param fn                : Function pointer to be registered with this command.
//
// @returns                 : Total number of registered commands on success, -1 otherwise.
//********************************************************************************************
int CommandControl::registerCommand(const string & commandName, void (*fn)())
{
    auto it = m_commandMap.find(commandName);
    if (it != m_commandMap.end())
    {
        printf("'%s' already registered!\n", commandName.c_str());
        return -1;
    }

    command_t command;
    command.command_fn = fn;
    command.index = ++m_totalCommands;
    command.name = commandName;

    m_commandMap[commandName] = command;
    
    return m_totalCommands;
}

//******************************************************************************************
// @name                    : validateCommand
//
// @description             : Checks if a given command name is registered in the system.
//
// @param commandName       : Command name string
//
// @returns                 : Index of the command if found, -1 otherwise.
//********************************************************************************************
int CommandControl::validateCommand(const string &  commandName)
{
    auto it = m_commandMap.find(commandName);
    if (it != m_commandMap.end())
    {
        return it->second.index;
    }

    return -1;
}

//******************************************************************************************
// @name                    : startCommandControl
//
// @description             : Starts the terminal and waits for user input. This will
//                            process the user input, validate if it is a registered command,
//                            execute the command if found.
//
// @returns                 : Nothing
//********************************************************************************************
void CommandControl::startCommandControl()
{
    printf("\n>> Launching terminal...\n");
    while (1)
    {
        string commandName;
        int commandIndex = -1;
        bool retval = false;

        cout << "$ ";
        getline(cin, commandName);

        // Don't process if nothing was entered
        if (commandName == "")
        {
            continue;
        }

        //Store this commandName to history
        this->addTohistory(commandName);

        // Validate the command
        commandIndex = this->validateCommand(commandName);
        if (commandIndex == -1)
        {
            printf("'%s' command not found! Try 'help'\n", commandName.c_str());
            continue;
        }

        // Execute the command
        retval = this->doCommand(commandName);

    }// End of command line processing
}

//******************************************************************************************
// @name                    : doCommand
//
// @description             : Executes the provided command.
//
// @param commandName       : Command name string
//
// @returns                 : True if command was executed successfully, false otherwise
//********************************************************************************************
bool CommandControl::doCommand(const string & commandName)
{
    auto it = m_commandMap.find(commandName);
    if (it == m_commandMap.end())
    {
        return false;
    }

    void (*fn_ptr)() = m_commandMap[commandName].command_fn;
    (*fn_ptr)();

    // This is an additional operation in case 'help' command is used.
    if (commandName == "help")
    {
        printf("show                                : Display list of registered commands\n");
        printf("history                             : Display list of previously executed commands\n");
    }

    return true;
}

//******************************************************************************************
// @name                    : addTohistory
//
// @description             : Adds this command name string to history
//
// @param commandName       : Command name string
//
// @returns                 : Nothing
//********************************************************************************************
void CommandControl::addTohistory(const string & commandName)
{
    if (m_commandHistoryList.size() == HISTORY_MAX)
    {
        m_commandHistoryList.pop_front();
    }
    
    m_commandHistoryList.push_back(commandName);

}

//******************************************************************************************
// @name                    : showCommandHistory
//
// @description             : Displays the list of previously executed commands.
//
// @returns                 : Nothing
//********************************************************************************************
void CommandControl::showCommandHistory()
{
    for (auto it = m_commandHistoryList.begin(); it != m_commandHistoryList.end(); it++)
    {
        printf("%s\n", (*it).c_str());
    }
}