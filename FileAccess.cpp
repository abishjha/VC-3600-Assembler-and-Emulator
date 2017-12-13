//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"


/**/
/*
FileAccess::FileAccess( int argc, char *argv[] )

NAME

    FileAccess::FileAccess - initializer for the FileAccess class.

SYNOPSIS

    FileAccess::FileAccess( int argc, char *argv[] );
    argc    --> total number of arguments pass through the terminal. should be two.
    *argv[] --> array of arguments passed from the terminal. second argument in the array is supposed to be the file name for the source file.

DESCRIPTION

    Initialize the class by opening the file passed as a command line argument. Report errors if file does not exist or could not be opened.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        cerr << "Usage: Assem <FileName>" << endl;
        exit( 1 );
    }
    // Open the file.
    m_sfile.open( argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        cerr << "Source file could not be opened, assembler terminated."
            << endl;
        exit( 1 ); 
    }
} /* FileAccess::FileAccess( int argc, char *argv[] ) */


/**/
/*
FileAccess::~FileAccess( )

NAME

    FileAccess::~FileAccess - destroyer for FileAccess class.

SYNOPSIS

    FileAccess::~FileAccess( );

DESCRIPTION

    Destroyer for the class object. Closes the file when the class object goes out-of-scope.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
FileAccess::~FileAccess( )
{
    // Not that necessary in that the file will be closed when the program terminates.
    m_sfile.close( );
} /* FileAccess::~FileAccess( ) */


/**/
/*
FileAccess::GetNextLine( string &a_buff )

NAME

    FileAccess::GetNextLine - get next line from the source code.

SYNOPSIS

    bool FileAccess::GetNextLine( string &a_buff );
    a_buff    --> address of the string to which we store the next line in the file.

DESCRIPTION

    Get the next line from the file. The function stores the line into the argument being passed.

RETURNS

    'false' if the end-of-file has been reached,
    'true' otherwise.

AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
// Get the next line from the file.
bool FileAccess::GetNextLine( string &a_buff )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) {
    
        return false;
    }
    getline( m_sfile, a_buff );
    
    // Return indicating success.
    return true;
} /* bool FileAccess::GetNextLine( string &a_buff ) */


/**/
/*
FileAccess::rewind( )

NAME

    FileAccess::rewind - rewind the file for re-read.

SYNOPSIS

    void FileAccess::rewind( );

DESCRIPTION

    This function rewinds the file by resetting all the flags including the end-of-file flag. 
    It also moves the file access pointer to the beginning of the file for a re-read.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
} /* void FileAccess::rewind( ) */
    