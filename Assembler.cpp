//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"


/**/
/*
Assembler::Assembler( int argc, char *argv[] )

NAME

	Assembler::Assembler - constructor for the Assembler class.

SYNOPSIS

    Assembler::Assembler( int argc, char *argv[] );
    argc              --> total number of arguments received in the command line.
    *argv[]           --> a pointer to the array of arguments passed through the command line.

DESCRIPTION

    Constructor for the assembler. Note: we are passing argc and argv to the file access constructor.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{

    // Nothing else to do here at this point.

} /* Assembler::Assembler( int argc, char *argv[] ) */


/**/
/*
Assembler::PassI()

NAME

    Assembler::PassI - first pass through the source code.

SYNOPSIS

    Assembler::PassI();

DESCRIPTION

    This function is the first pass for the Assembler. Pass I establishes the location of the 
    labels and constructs a symbol table using the SymbolTable class.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void Assembler::PassI()
{
     int loc = 0;        // Tracks the location of the instructions to be generated.

     // Successively process each line of source code.
     for (; ; ) {
          // Read the next line from the source file.
          string buff;
          if (!m_facc.GetNextLine(buff)) {

               // If there are no more lines, we are missing an end statement.
               // We will let this error be reported by Pass II.
               return;
          }
          // Parse the line and get the instruction type.
          Instruction::InstructionType st = m_inst.ParseInstruction(buff);

          // If this is an end statement, there is nothing left to do in pass I.
          // Pass II will determine if the end is the last statement.
          if (st == Instruction::ST_End) return;

          // Labels can only be on machine language and assembler language
          // instructions.  So, skip other instruction types.
          if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
          {
               continue;
          }
          // If the instruction has a label, record it and its location in the
          // symbol table.
          if (m_inst.isLabel()) {

               m_symtab.AddSymbol(m_inst.GetLabel(), loc);
          }
          // Compute the location of the next instruction.
          loc = m_inst.LocationNextInstruction(loc);
     }
} /* void Assembler::PassI() */


/**/
/*
Assembler::PassII()

NAME

    Assembler::PassII - second pass through the source code.

SYNOPSIS

    void Assembler::PassII();

DESCRIPTION

    Pass II does a second traversal of the source code. It uses the symbol table established in Pass I 
    and starts translating the source code into code for the VC-3600 computer. Pass II does the most 
    work in this project as it translates the instructions, it records any errors encountered, and stores 
    the translated instruction in a vector of pairs for further use. Pass II also prints out the original 
    statement and the translated code for every line of instruction in the source code with help from the 
    TranslateInstruction function in the Instruction class. At the end, if errors have been encountered, 
    the function prints them out.

RETURNS


AUTHOR

	Abish Jha

DATE

    12/05/2017

*/
/**/
void Assembler::PassII()
{
     m_facc.rewind(); // Resets the flags for the open file so it can be read again from the top
     int loc = 0;        // Tracks the location of the instructions to be generated.
     bool is_end = false; // Flag to indicate if the code has hit the end statement
     Errors::InitErrorReporting(); 

     // Clearing the vector which will hold the (location, content) pair which will be fed into the emulator
     m_machinecode.clear();

     // Print the header for the translation table output . The rest is printed by the Instruction class
     cout << setw(12) << left << "Location" << setw(12) << left << "Contents" << "Original Statement" << endl;

     // Successively process each line of source code.
     for (; ; ) {
          // Read the next line from the source file.
          string buff;
          if (!m_facc.GetNextLine(buff)) {

               // Returned as was expected with no lines after code
               if (is_end == true) 
                    break;

               // Report error : since there are no more lines, we are missing an end statement
               string error = "(location " + to_string(loc) + ") Missing end statement";
               Errors::RecordError(error);
               break;
          }

          if (is_end == true) {
               string error = "(location " + to_string(loc) + ") Lines after end statement";
               Errors::RecordError(error);
               break;
          }

          pair<int, string>  translation = m_inst.TranslateInstruction(buff, loc);

          // Set the is_end flag to true to indicate the apperance of end statement
          if (translation == pair<int, string>(0, "end") )
               is_end = true;
          // Do not push the pair onto the vector if there is no valid machine code
          else if (translation != pair<int, string>(0, "n/a"))
               m_machinecode.push_back(translation);

          // Compute the location of the next instruction.
          loc = m_inst.LocationNextInstruction(loc);
     }
     if (!Errors::Empty())
          Errors::DisplayErrors();

     cout << "Press Enter to continue...";
     cin.ignore();
} /* void Assembler::PassII() */


/**/
/*
Assembler::RunEmulator()

NAME

    Assembler::RunEmulator - run the emulator on the translated code.

SYNOPSIS

    void Assembler::RunEmulator();

DESCRIPTION

    Run the emulator on the translated code from Pass II. If errors have been encountered, emulation is halted. 
    If not, the function loads all the translated instruction into the emulator's memory and then runs the emulator. 
    This function also  detects errors encountered during emulation and reports them after.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void Assembler::RunEmulator()
{
     // Terminate emulation if errors are encountered
     if (!Errors::Empty()) {
          cout << "Errors were encountered during compilation...\nExiting emulation\n";
          return;
     }

     // Insert the machine code into the emulator class and report errors.
     for (vector<pair<int, string>>::iterator it = m_machinecode.begin(); it != m_machinecode.end(); ++it) {
          bool insertion_check = m_emul.insertMemory(it->first, stoi(it->second));
          if (insertion_check == false) {
               string error = "Error inserting the command " + to_string(it->first) + " " + it->second + " into the emulator memory";
               Errors::RecordError(error);
          }
     }

     // Run program and report error if encountered any.
     bool run_check = m_emul.runProgram();
     if (run_check == false) {
          string error = "Error running the emulator";
          Errors::RecordError(error);
     }

     // Display any errors encountered during emulation.
     if (!Errors::Empty())
          Errors::DisplayErrors();

     cout << "Press Enter to continue...\n";
     cin.ignore();
} /* void Assembler::RunEmulator() */

