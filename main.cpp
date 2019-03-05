#include"command_control.h"
#include<iostream>
#include <stdlib.h>
#include<windows.h>

using namespace std;

//*******************************************************************************************
// Commands to be registered
//*******************************************************************************************

// Show help
void showHelp()
{
    printf("Usage: \n");
    printf("--------\n");
    printf("help            : Displays the help\n");
    printf("quit/exit       : Terminate application\n");

}

// Quit
void quitCommandControl()
{
    printf("\nTerminating application...\n");
    Sleep(2000);
    exit(0);
}


//*******************************************************************************************
// M A I N
//*******************************************************************************************
int main()
{
    // Registration of commands
    CommandControl::GetInstance().registerCommand("help", &showHelp);
    CommandControl::GetInstance().registerCommand("quit", &quitCommandControl);
    CommandControl::GetInstance().registerCommand("exit", &quitCommandControl);

    // Show the prompt and start processing commands
    CommandControl::GetInstance().startCommandControl();

    return 0;
}