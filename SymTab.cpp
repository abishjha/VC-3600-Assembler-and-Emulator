//
//		Implementation of the symbol table class.
//
#include "stdafx.h"
#include "SymTab.h"

// This is the actual symbol table.  The symbol is the key to the map.
static map<string, int> m_symbolTable;


/**/
/*
SymbolTable::AddSymbol(string &a_symbol, int a_loc)

NAME

    SymbolTable::AddSymbol - add a label to the table.

SYNOPSIS

    void SymbolTable::AddSymbol(string &a_symbol, int a_loc);
    a_symbol    --> the symbol being added to be the table.
    a_loc       --> the location of the symbol being added.

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc" into the symbol table.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void SymbolTable::AddSymbol(string &a_symbol, int a_loc)
{
     // If the symbol is already in the symbol table, record it as multiply defined.
     map<string, int>::iterator st;
     st = m_symbolTable.find(a_symbol);
     if (st != m_symbolTable.end()) {

          st->second = multiplyDefinedSymbol;
          return;
     }
     // Record a the  location in the symbol table.
     m_symbolTable[a_symbol] = a_loc;
} /* void SymbolTable::AddSymbol( string &a_symbol, int a_loc ) */


/**/
/*
SymbolTable::DisplaySymbolTable()

NAME

    SymbolTable::DisplaySymbolTable - print symbol table.

SYNOPSIS

    void SymbolTable::DisplaySymbolTable();

DESCRIPTION

    This function will print out the symbol table in a neat format.

RETURNS


AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
void SymbolTable::DisplaySymbolTable()
{
     cout << setw(12) << left << "Symbol #" << setw(12) << left << "Symbol" << setw(12) << left << "Location" << endl;
     int count = 0;
     for (map<string, int>::iterator it = m_symbolTable.begin(); it != m_symbolTable.end(); ++it) {
          cout << setw(12) << left << count++ << setw(12) << left << it->first << setw(12) << left << it->second << endl;
     }
     cout << "_______________________________________________________________________________________________________\n\n";
     cout << "Press Enter to continue...";
     cin.ignore();
} /* void SymbolTable::DisplaySymbolTable() */


/**/
/*
SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc)

NAME

    SymbolTable::LookupSymbol - lookup a symbol in the table.

SYNOPSIS

    bool SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc);
    a_symbol    --> the symbol to be searched for. const before the argument indicates the function is not going to change the value at the address of a_symbol.
    a_loc       --> if the symbol is found, the location is stored in a_loc. if not, a_loc is unchanged.

DESCRIPTION

    This function will lookup a symbol in the symbol table and if found, store the location of the symbol in a_loc.

RETURNS

    'true' if symbol was found in the table,
    'false' otherwise.

AUTHOR

    Abish Jha

DATE

    12/05/2017

*/
/**/
bool SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc)
{
     map<string, int>::iterator it = m_symbolTable.find(a_symbol);
     if (it != m_symbolTable.end()) {
          a_loc = it->second;
          return true;
     }
     return false;
} /* bool SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc) */
