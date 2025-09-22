// TOKENIZER

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// Prototype before "Globals.cpp" & "symbolTable.cpp"; Both files use lex() function
void lex();

// Include Global variables, Symbol Table, and Tokenizer (bnf.cpp)
#include "Q2Globals.cpp"
#include "Q2bnf.cpp"  
// #include "Q2symbolTable.cpp"      // Don't need Symbol Table to store variables
        

ifstream infp;
// const int MAX_SIZE = 100;        // maximum size per line <--Commented: Already declared in Globals.cpp
// char nextChar = ' ';             // Now included in Global.cpp: variable used both here lex.cpp and bnf.cpp

// Returns a single character from a file
char getChar() 
{
    char c = infp.get();     
    if (c == '\n') 
        line++;
    return c;
}

// Adds character to the lexeme string
void addChar(char c) 
{
    lexeme = lexeme + c;
    if (lexeme.length() > MAX_SIZE - 1) 
    {
        cout << "ERROR: lexeme too long… \n";
        errors++;
    }
}

// Determines if "lexeme" is a keyword ('a', 'b' or 'c')
Tokens lookupKeyword(string lexeme) 
{
    Tokens t;
    if (lexeme[0] == 'a') 
        t = A;
    else if (lexeme[0] == 'b') 
        t = B;    
    else //(lexeme[0] == 'c') 
        t = C;
    return t;
}

// Helping function to display the token as a string
void prt (Tokens nt) 
{
    switch (nt) 
    {
        case A: cout << "<A>"; break;
        case B: cout << "<B>"; break;
        case C: cout << "<C>"; break;
        case ENDFILE: cout << "<ENDFILE>"; break;
        case UNKNOWN: cout << "Unknow "; break;
    }
}

// Create a lexeme. Example: for "aacbb" --> lexmes: "aa", "c", and "bb"
void lex() 
{
    lexeme = "";

    while (nextChar == '\n')                    // If there's an empty line (or the end of input), skip it  
        nextChar = getChar();
 
    if (nextChar == 'a' || nextChar == 'b')     // If character/s "a's" or "b's", get them all
    {
        addChar(nextChar);
        nextChar = getChar();
        while (nextChar == lexeme[0])
        {
            addChar(nextChar);
            nextChar = getChar();
        }
        nextToken = lookupKeyword(lexeme);
    }

    else if (nextChar == 'c')                   // If character "c" just take one
    {
        addChar(nextChar);
        nextToken = lookupKeyword(lexeme);
        nextChar = getChar();
    }

    else if (nextChar == EOF) 
        nextToken = ENDFILE;

    else 
        nextToken = UNKNOWN;

    cout << "Next token is: "; prt(nextToken); cout << " Next lexeme is " << lexeme << endl;
}

int main() 
{
    string filename;
    filename = "prg4.in"; // <--------------------------------[FILE TO INCLUDE]--------------------

    infp.open(filename);

    if (!infp) 
    {
        cout << "ERROR - cannot open " << filename << "\n";
        errors++;
        return 0;
    }

    nextChar = getChar();                       // Initialize: get the first character

    lex();

    do 
    {
        term1(); 
    } while (nextToken != ENDFILE);

    cout << "Total number of errors: " << errors << endl;
    return 0;
}