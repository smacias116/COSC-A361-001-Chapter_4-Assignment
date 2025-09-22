// GLOBAL VARIABLES

#include <iostream>
using namespace std;

enum Tokens {A, B, C, UNKNOWN, ENDFILE};
const int MAX_SIZE = 100;   // maximum size per line
string lexeme = "";         // current lexeme
Tokens nextToken;
char nextChar;              // next character to read
int errors = 0;             // keep track of number of errors
int line = 1;               // keep track of current line reached

// Function to display the error message with line number of error detected.
void errMsg (string msg)
{
    cout << "Error at line: " << line << ": " << msg << endl;
    errors++;
    //lex();
}