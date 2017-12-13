//
//      Implementation of the Errors class.
//
#include "stdafx.h"
#include "Errors.h"

//since this is a static vector, this needs to be included here to work
static vector<string> m_ErrorMsgs;

/**/
/*
Errors::InitErrorReporting()

NAME

    Errors::InitErrorReporting - initializer for the class.

SYNOPSIS

    void Errors::InitErrorReporting();

DESCRIPTION

    Initialize the class for error reporting. This is done by clearing the vector that stores all the errors.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void Errors::InitErrorReporting()
{
     m_ErrorMsgs.clear();
} /* void Errors::InitErrorReporting() */


/**/
/*
Errors::RecordError(string & a_emsg)

NAME

    Errors::RecordError - record encountered error.

SYNOPSIS

    void Errors::RecordError(string & a_emsg);
    a_emsg        --> this parameter is the error in the form of a string which is recorded by the Errors class.

DESCRIPTION

    This function records errors into a vector so they can be used to keep a log of the errors.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void Errors::RecordError(string & a_emsg)
{
     m_ErrorMsgs.push_back(a_emsg);
} /* void Errors::RecordError(string & a_emsg) */


/**/
/*
Errors::DisplayErrors()

NAME

    Errors::DisplayErrors - display the recorded errors.

SYNOPSIS

    void Errors::DisplayErrors();

DESCRIPTION

    Print out all the recorded errors with a number at the beginning of each line indicating the number of that particular error.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void Errors::DisplayErrors()
{
     int count = 0;
     for (vector<string>::iterator it = m_ErrorMsgs.begin(); it != m_ErrorMsgs.end(); ++it) {
          cout << "!ERROR " << setw(2) << count++ << "! " << *it << endl;
     }
} /* void Errors::DisplayErrors() */


/**/
/*
bool Errors::Empty()

NAME

    Errors::Empty - check if empty.

SYNOPSIS

    bool Errors::Empty();

DESCRIPTION

    Check if any errors have been recorded. This is done by checking the size of the vector that stores the error. 
    If the size is 0, no errors have been reported and vice versa.

RETURNS

    'true' if no errors have been reported,
    'false' otherwise.

AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
bool Errors::Empty()
{
     return (m_ErrorMsgs.size() == 0) ? true : false;
} /* bool Errors::Empty() */
