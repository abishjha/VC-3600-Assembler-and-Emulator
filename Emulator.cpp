//
//      Implementation of the Emulator class.
//
#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"

/**/
/*
emulator::insertMemory(int a_location, int a_contents)

NAME

    emulator::insertMemory - insert instruction into emulator memory.

SYNOPSIS

    bool emulator::insertMemory(int a_location, int a_contents);
	a_location     --> location of the instruction coming in. location should be less than 10,000.
    a_contents     --> content of the instruction coming in. this is a 6 digit number.

DESCRIPTION

    Insert machine code instruction with its respective location into the memory of the emulator. 
    This function also establishes the location of the first instruction so emulation can be done.

RETURNS

    'true' if the instruction was successfully inserted into memory of the emulator,
    'false' otherwise.

AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
bool emulator::insertMemory(int a_location, int a_contents)
{
     if (a_location < MEMSZ && a_location >= 0) {
          m_memory[a_location] = a_contents;
     }
     else {
          string error = "Location out of bounds error";
          Errors::RecordError(error);
          return false;
     }

     if (m_firstInst) {
          m_org = a_location;
          m_firstInst = false;
     }

     return true;
} /* bool emulator::insertMemory(int a_location, int a_contents) */


/**/
/*
emulator::runProgram()

NAME

    emulator::runProgram - run the emulator.

SYNOPSIS

    bool emulator::runProgram();

DESCRIPTION

    Run the emulator on the code stored in the emulator's memory. Instruction is parsed one line 
    at a time into op-code and operand and the respective function is called for the op-code.

RETURNS

    'true' if the emulator was successfully run,
    'false' otherwise.

AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
bool emulator::runProgram()
{
     // Moving the program pointer to point to the origin location
     m_loc = m_org;
     for (int i = 0; i < MEMSZ; i++) {
          m_opcode = m_memory[m_loc] / 10000;
          m_operand = m_memory[m_loc] % 10000;

          // Opcode 0 means the line is either declaring storage or a constant or something along the lines 
          // which has already been processed during instruction parsing
          if (m_opcode == 0) {
               m_loc++;
               continue;
          }

          switch (m_opcode) {
          case 1:
               add();
               break;
          case 2:
               sub();
               break;
          case 3:
               mult();
               break;
          case 4:
               div();
               break;
          case 5:
               load();
               break;
          case 6:
               store();
               break;
          case 7:
               read();
               break;
          case 8:
               write();
               break;
          case 9:
               b();
               break;
          case 10:
               bm();
               break;
          case 11:
               bz();
               break;
          case 12:
               bp();
               break;
          case 13:
               halt();
               break;
          }

          if (m_kill) {
               return true;
          }
     }
     // Reaching this point in the program means there is a missing halt statement
     return false;
} /* bool emulator::runProgram() */


/**/
/*
emulator::add()

NAME

    emulator::add - add function for emulator.

SYNOPSIS

    void emulator::add();

DESCRIPTION

    Add the number in the specified address to the accumulator.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void emulator::add()
{
     int sum = m_accumulator + m_memory[m_operand];
     if (sum > 999999) {
          cout << "Overflow in the accumulator when executing command\n";
          return;
     }
     
     m_accumulator = sum;
     m_loc++;
} /* void emulator::add() */


/**/
/*
emulator::sub()

NAME

    emulator::sub - sub function for emulator.

SYNOPSIS

    void emulator::sub();

DESCRIPTION

    Subtract the number at the specified address from the accumulator.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void emulator::sub()
{
     int diff = m_accumulator - m_memory[m_operand];
     if (diff < -999999) {
          cout << "Overflow in the accumulator when executing command\n";
          return;
     }

     m_accumulator = diff;
     m_loc++;
} /* void emulator::sub() */


/**/
/*
emulator::mult()

NAME

    emulator::mult - mult function for emulator.

SYNOPSIS

    void emulator::mult();

DESCRIPTION

    Multiply the number at the specified address with the number present in the accumulator.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void emulator::mult()
{
     int multi = m_accumulator * m_memory[m_operand];
     if (multi > 999999 || multi < -999999) {
          cout << "Overflow in the accumulator when executing command\n";
          return;
     }

     m_accumulator = multi;
     m_loc++;
} /* void emulator::mult() */


/**/
/*
emulator::div()

NAME

    emulator::div - div function for emulator.

SYNOPSIS

    void emulator::div();

DESCRIPTION

    Divide the number present in the accumulator with the number at the specified address.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void emulator::div()
{
     int divi = m_accumulator / m_memory[m_operand];
     if (divi > 999999 || divi < -999999) {
          cout << "Overflow in the accumulator when executing command\n";
          return;
     }

     m_accumulator = divi;
     m_loc++;
} /* void emulator::div() */


/**/
/*
emulator::load()

NAME

    emulator::load - load function for emulator.

SYNOPSIS

    void emulator::load();

DESCRIPTION

    Load the number at the specified address to the accumulator.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void emulator::load()
{
     m_accumulator = m_memory[m_operand];
     m_loc++;
} /* void emulator::load() */


/**/
/*
emulator::store()

NAME

    emulator::store - store function for emulator.

SYNOPSIS

    void emulator::store();

DESCRIPTION

    Store the contents of the accumulator into the specified address.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void emulator::store()
{
     m_memory[m_operand] = m_accumulator;
     m_loc++;
} /* void emulator::store() */


/**/
/*
emulator::read()

NAME

    emulator::read - read function for emulator.

SYNOPSIS

    void emulator::read();

DESCRIPTION

    Read a line from the console and place the first 6 digits in the specified address.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void emulator::read()
{
     string input;
     cout << "? ";
     cin >> input;

     char sign = 'z';
     if (input[0] == '-' || input[0] == '+') {
          sign = input[0];
          input = input.erase(0, 1);
     }

     // Cutting off any digits after the first 6
     if(input.size() > 6)
          input = input.substr(0, 6);

     for (int i = 0; i < input.size(); i++) {
          if (!isdigit(input[i])) {
               cout << "Input is not all digits\n";
               return;
          }
     }

     m_memory[m_operand] = stoi(input);
     if (sign == '-')
          m_memory[m_operand] *= -1;
     m_loc++;
} /* void emulator::read() */


/**/
/*
emulator::write()

NAME

    emulator::write - write function for emulator.

SYNOPSIS

    void emulator::write();

DESCRIPTION

    Write the contents of the specified address to the console.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void emulator::write()
{
     cout << m_memory[m_operand] << endl;
     m_loc++;
} /* void emulator::write() */


/**/
/*
emulator::b()

NAME

    emulator::b - b function for emulator.

SYNOPSIS

    void emulator::b();

DESCRIPTION

    Branch the program execution to the specified address.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void emulator::b()
{
     m_loc = m_operand;
} /* void emulator::b() */


/**/
/*
emulator::bm()

NAME

    emulator::bm - bm function for emulator.

SYNOPSIS

    void emulator::bm();

DESCRIPTION

    Branch the program execution to the specified address if the value stored in the accumulator is negative i.e. less than 0.

RETURNS


AUTHOR

    Abish Jha
    
DATE

    12/05/2017

*/
/**/
void emulator::bm()
{
     if (m_accumulator < 0)
          m_loc = m_operand;
     else
          m_loc++;
} /* void emulator::bm() */


/**/
/*
emulator::bz()

NAME

    emulator::bz - bz function for emulator.

SYNOPSIS

    void emulator::bz();

DESCRIPTION

    Branch the program execution to the specified address if the value stored in the accumulator is 0.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void emulator::bz()
{
     if (m_accumulator == 0)
          m_loc = m_operand;
     else
          m_loc++;
} /* void emulator::bz() */


/**/
/*
emulator::bp()

NAME

    emulator::bp - bp function for emulator.

SYNOPSIS

    void emulator::bp();

DESCRIPTION

    Branch the program execution to the specified address if the value stored in the accumulator is positive i.e. greater than 0.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void emulator::bp()
{
     if (m_accumulator > 0)
          m_loc = m_operand;
     else
          m_loc++;
} /* void emulator::bp() */


/**/
/*
emulator::halt()

NAME

    emulator::halt - halt function for emulator.

SYNOPSIS

    void emulator::halt();

DESCRIPTION

    Terminate the program execution. This is done by setting the kill switch to true which will 
    result in a termination of the emulation. The emulation is terminated by the RunEmulator function.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void emulator::halt()
{
     m_kill = true;
} /* void emulator::halt() */

