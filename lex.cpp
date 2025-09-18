// TOKENIZER

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// Prototype before "Globals.cpp" & "symbolTable.cpp"; Both files use lex() function
void lex();

// Include Global variables, Symbol Table, and Tokenizer (bnf.cpp)
#include "Globals.cpp"
#include "symbolTable.cpp"
#include "bnf.cpp"

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
    if (lexeme == "int") 
        t = INT_KEYWORD;
    else 
        t = VAR;
    return t;
}

// Converts operator to token operator
Tokens lookupOp(string lexeme) 
{
    if (lexeme == "(") return LEFT_PAREN;
    if (lexeme == ")") return RIGHT_PAREN;
    if (lexeme == "+") return ADD_OP;
    if (lexeme == "-") return SUB_OP;
    if (lexeme == "/") return MUL_OP;
    if (lexeme == "*") return DIV_OP;
    if (lexeme == "=") return ASSIGN_OP;
    if (lexeme == ",") return COMMA;
    return UNKNOWN;
}

bool isOperator(char c) 
{
    if (c=='+' || c=='-' || c=='*' || c=='/' || c==',' || c=='(' || c==')' || c=='=') 
        return true;
    return false;
}

// Helping function to display the token as a string
void prt (Tokens nt) 
{
    switch (nt) 
    {
        case LETTER: cout << "<Letter>"; break;
        case DIGIT: cout << "<DIGIT>"; break;
        case INT_KEYWORD: cout << "<INT_KEYWORD>"; break;
        case INT_LIT: cout << "<INT_LIT>"; break;
        case VAR: cout << "<VAR>"; break;
        case ASSIGN_OP: cout << "<ASSIGN>"; break;
        case ADD_OP: cout << "<ADD_OP>"; break;
        case SUB_OP: cout << "<SUB_OP>"; break;
        case MUL_OP: cout << "<MUL_OP>"; break;
        case DIV_OP: cout << "<DIV_OP>"; break;
        case LEFT_PAREN: cout << "<LEFT_PAREN>"; break;
        case RIGHT_PAREN: cout << "<RIGHT_PAREN>"; break;
        case COMMA: cout << "<COMMA>"; break;
        case ENDFILE: cout << "<ENDFILE>"; break;
        case UNKNOWN: cout << "Unknow "; break;
    }
}

void lex() 
{
    lexeme = "";
    if (isspace(nextChar)) 
        nextChar = getNonSpaceChar();
    if (isalpha(nextChar) || nextChar == '_')
    {
        while (isalpha(nextChar) || isdigit(nextChar) || nextChar == '_') 
        {
            addChar(nextChar);
            nextChar = getChar();
        }
        nextToken = lookupKeyword(lexeme);
    }
    else if (isdigit(nextChar))
    {
        while (isdigit(nextChar)) 
        {
            addChar(nextChar);
            nextChar = getChar();
        }
        nextToken = INT_LIT;
    }
    else if (isOperator(nextChar)) 
    {
        while (isOperator(nextChar)) 
        {
            addChar(nextChar);
            nextChar = getChar();
        }
        nextToken = lookupOp(lexeme);
    }
    else if (nextChar == EOF) 
        nextToken = ENDFILE;
    else 
        nextToken = UNKNOWN;
    cout << "Next token is: "; prt (nextToken); cout << " Next lexeme is " << lexeme << endl;
}

int main() 
{
    string filename;
    filename = "prg3.in"; // <---------------------------------------------------------FILE TO INCLUDE
    infp.open(filename);
    if (!infp) 
    {
        cout << "ERROR - cannot open " << filename << "\n";
        errors++;
        return 0;
    }
    // string str;  <--Commented: This variable in the slides is not being used
    lex();
    do 
    {
        stmt();
    } while (nextToken != ENDFILE);
    cout << "Total number of errors: " << errors << endl;
    return 0;
}