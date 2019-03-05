#include"command_control.h"
#include<iostream>
#include <stdlib.h>
#include<windows.h>
#include"random.h"

using namespace std;

//*******************************************************************************************
// global variables
//*******************************************************************************************
vector<char*> g_stringSamples;

//*******************************************************************************************
// Commands to be registered
//*******************************************************************************************

// Show help
void showHelp()
{
    printf("Usage: \n");
    printf("--------\n");
    printf("help                                : Displays the help\n");
    printf("generate samples                    : Generate some sample strings\n");
    printf("show     samples                    : Display sample strings\n");
    printf("clear samples                       : Clear sample strings vector\n");
    printf("exit                                : Terminate application\n");
    printf("quit                                : Terminate application\n");

}

// Quit
void quitCommandControl()
{
    printf("\nTerminating application...\n");
    Sleep(2000);
    exit(0);
}

// Generate some sample strings
void generateSamples()
{
    int num = 5;
    RandomGenerator rng;
    for (int i = 0; i < num; i++)
    {
        char *value = rng.generateRandomString(5, false, false);
        g_stringSamples.push_back(value);
    }
}

// Display sample strings
void showSamples()
{
    printf("Sample size: %d\n", g_stringSamples.size());
    for (int i = 0; i < g_stringSamples.size(); i++)
    {
        printf("%s ", g_stringSamples[i]);
    }
    printf("\n");
}

// Clear sample strings vector
void clearSamples()
{
    for (int i = 0; i < g_stringSamples.size(); i++)
    {
        free(g_stringSamples[i]);
    }

    g_stringSamples.clear();
}

//*******************************************************************************************
// M A I N
//*******************************************************************************************
int main()
{
    // Registration of commands
    int commandIndex = -1;

    commandIndex = CommandControl::GetInstance().registerCommand("help", &showHelp);
    commandIndex = CommandControl::GetInstance().registerCommand("help", &showHelp);  // This will not be registered as it already exists
    commandIndex = CommandControl::GetInstance().registerCommand("quit", &quitCommandControl);
    commandIndex = CommandControl::GetInstance().registerCommand("exit", &quitCommandControl);
    commandIndex = CommandControl::GetInstance().registerCommand("generate samples", &generateSamples);
    commandIndex = CommandControl::GetInstance().registerCommand("show samples", &showSamples);
    commandIndex = CommandControl::GetInstance().registerCommand("clear samples", &clearSamples);

    // Show the prompt and start processing commands
    CommandControl::GetInstance().startCommandControl();

    return 0;
}