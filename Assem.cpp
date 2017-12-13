 /**/
 /*
 Assem

 NAME

     Assem - entry point for the program.

 DESCRIPTION

     Assem - this file invokes the functions that runs the program.
     In other words, this file contains the main method which is
     the entry point for any C++ program.

 AUTHOR

     Abish Jha

 DATE

     12/05/2017

 */
 /**/

#include "stdafx.h"     // This must be present if you use precompiled headers which you will use.
#include <stdio.h>

#include "Assembler.h"
#include "Errors.h"

int main( int argc, char *argv[] )
{
    Assembler assem( argc, argv );

    // Establish the location of the labels:
    assem.PassI( );

    // Display the symbol table.
    assem.DisplaySymbolTable();

    // Output the symbol table and the translation.
    assem.PassII( );

    // Run the emulator on the VC3600 program that was generated in Pass II.
    assem.RunEmulator();
   
    // Terminate indicating all is well.  If there is an unrecoverable error, the 
    // program will terminate at the point that it occurred with an exit(1) call.
    return 0;
}
