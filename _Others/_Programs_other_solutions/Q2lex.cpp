// TOKENIZER

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// Prototype before "Globals.cpp" & "symbolTable.cpp"; Both files use lex() function
void lex();

// Include Global variables, Symbol Table, and Tokenizer (bnf.cpp)
#include "Q2Globals.cpp"
#include "Q2symbolTable.cpp"
#include "Q2bnf.cpp"

ifstream infp;
// const int MAX_SIZE = 100;   // maximum size per line <--Commented: Already declared in Globals.cpp
char nextChar = ' ';        // next character to read

// Returns a single character from a file
char getChar() 
{
    char c = infp.get();     
    if (c == '\n') line++;
        return c;
}

// Skips spaces and return first non-space character from the file
char getNonSpaceChar() 
{
    char c = ' ';
    while (isspace(c))
        c = getChar();
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

// Determines if "lexeme" is a keyword or Var
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


  

void lex() 
{
    lexeme = "";
    
    if (isspace(nextChar))         
    {
        nextChar = getNonSpaceChar();
    }     
        
    if (isalpha(nextChar))   // CHECK FOR CAPITALIZED
    {
        if (nextChar == 'c')                     // If nexChar is 'c'... 
        {
            addChar(nextChar);
            nextToken = lookupKeyword(lexeme);  //      ...get the Token.
            nextChar = getChar();
        }
        
        else if (nextChar == 'a' || nextChar == 'b')
        {
            lexeme = lexeme + nextChar;         // If nexChar is NOT 'c' (it's 'a' or 'b')...
            nextChar = getChar();   
            while (nextChar == lexeme[0])       //      ...concatenate characters...
            {
                addChar(nextChar);
                nextChar = getChar();
            } 
            nextToken = lookupKeyword(lexeme);  //      ...and then get the Token.
        }

        else
        {
            nextToken = UNKNOWN;
        } 
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

    lex();

    do 
    {
        term1(); 
    } while (nextToken != ENDFILE);


    cout << "Total number of errors: " << errors << endl;
    return 0;
}