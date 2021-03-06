/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                     *
 *                                 Console Header File                                 *
 *                                      TRICLYSM                                       *
 *                                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                     *
 *  This file contains the main definitions of all console-related functions,          *
 *  including parsing the actual user's input. Actual console commands are defined     *
 *  in console_commands.cpp.                                                           *
 *                                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                     *
 *  Copyright (C) 2011 Brandon Castellano, Ryan Mantha. All rights reserved.           *
 *  Triclysm is provided under the BSD-2-Clause license. This program uses the SDL     *
 *  (Simple DirectMedia Layer) library, and the Lua scripting language. See the        *
 *  included LICENSE file or <http://www.triclysm.com/> for more details.              *
 *                                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

///
/// \file  console.h
/// \brief This file contains the definitions of all console-related functions for the
///        Triclysm program itself, including the command output and command history.
///


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                               PREPROCESSOR DIRECTIVES                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once
#ifndef TC_CONSOLE_
#define TC_CONSOLE_

#include "SDL.h"
#include <string>
#include <vector>
#include <list>


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                  GLOBAL VARIABLES                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class ConsoleCommand;               // Console command class, defined below in this file.
class CommandAlias;                 // Command alias class, defined below in this file.

extern bool        consoleEnabled;  // True to draw the console, false to hide it.

extern size_t      cursorPos;       // Position of the cursor.
extern std::string currInput;       // The string of the actual current input.

extern const std::string          inputPrefix;      // Prefix prepended to currInput.

extern std::list<ConsoleCommand*> cmdList;          // The command list itself.
extern std::list<CommandAlias*>   aliasList;        // The alias list itself.

extern std::list<std::string>     outputList,       // The console output list.
                                  historyList;      // The console history list.

extern std::list<std::string>::iterator outputIt;   // The output list iterator.

extern unsigned int waitMode,                  // The current wait mode (0 to run).
                    waitAmount,                // The current wait amount.
                    waitInitAmount;            // The initial wait condition value.


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                 FUNCTION PROTOTYPES                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

namespace TC_Console_Commands
{
    void RegisterCommands();    // Defined in console_commands.cpp.
}

void InitConsole(size_t maxInputLen, size_t maxHistLines, size_t maxOutLines);

bool cmpConsoleCmd(ConsoleCommand const *first, ConsoleCommand const *second);
bool cmpCmdAlias(CommandAlias const *first, CommandAlias const *second);
bool cmpStrNoCase(std::string const& first, std::string const& second);
void StripWhitespaceLT(std::string &toTrim);

void WriteOutput(std::string const& outputStr);
void WriteHistory(std::string const& historyStr);
void ClearOutput();
void ClearHistory();


void CallCommand(std::string const& cmd);
void ParseInput();
void ParseInput(std::string const& inputStr);
bool LoadScript(char const *fileName);
ConsoleCommand *GetCommand(std::string const& cmdName);
void SuggestCommand();

void ScrollHistory(bool up);
void ScrollOutput(bool up);

void MoveCursor(bool left);
void InputBackspace();
void InputAddChar(char c);

void RunCommandQueue();
void CheckWaitMode();
void SetWaitMode(unsigned int mode, unsigned int delay);




/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                  CLASS DEFINITIONS                                  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

///
/// \brief Console Command Object
///
/// This class defines a single console command, which is made up of a name, description,
/// help entry (if needed), and a call-back function representing the command. 
///
class ConsoleCommand {
  public:
    ConsoleCommand(std::string const& callingName, void (*cmdFunc)(std::vector<std::string> const&),
                   std::string const& helpEntry)
    {
        name = callingName;
        func = cmdFunc;
        help = helpEntry;
    }
    std::string name,
                help;
    void (*func)(std::vector<std::string> const&);
};


///
/// \brief Command Alias Object
///
/// This class defines a command alias for a console command.  Calling a command alias
/// is identical to calling the actual command itself.
///
class CommandAlias {
  public:
    CommandAlias(std::string const& cmdName, std::string const& aliasName)
    {
        name  = cmdName;
        alias = aliasName;
    }
    std::string name,
                alias;
};


#endif
