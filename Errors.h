#ifndef _ERRORS_H
#define _ERRORS_H

/**/
/*
Errors Class

NAME

     Errors - hold and display errors encountered during code execution.

DESCRIPTION

     Emulator class - Class to manage error reporting. 
     Note: all members are static so we can access them anywhere.

AUTHOR

     Abish Jha

DATE

     12/05/2017

*/
/**/


#include <string>
#include <vector>

class Errors {

public:
    
    // Initializes error reports.
    static void InitErrorReporting( );

    // Records an error message.
    static void RecordError( string &a_emsg );

    // Displays the collected error message.
    static void DisplayErrors( );

    // Check if the error list is empty.
    static bool Empty();

private:


};
#endif