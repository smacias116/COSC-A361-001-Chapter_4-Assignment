// PARSER

#include <iostream>
using namespace std;

void term1(); 


void term3()    // (2) FUNCTION CALLED (IF REQUIRED)
{
    lex();                                  //Generate next Lexeme

    if (nextToken == B)                     //IF Token is B...
        lex();                                  //...sequence COMPLITED. Start a new lexeme.
                                  
    else                                    //IF Token is NOT B, END sequence...
        errMsg ("After <C> Expected <B>");      //...and write error message.     
}


void term2()    // (1) FUNCTION CALLED (IF REQUIRED)
{
    lex();                                  // Generate next Lexeme

    if (nextToken == C)                     //IF Token is C...
        term3();                                //...CONTINUE sequence:   opt.1: ...<C><B>

    else if (nextToken == A)                //IF Token is A (again)... 
        term1();                                //...It's a new lexeme: start again with (tem1()) <----is this needed??? WHEN OUT OF Do {} starts again

    else                                    //IF Token is NOT C and NOT A, END sequence...
        if (nextToken != ENDFILE)               //(write the message only if document not finished) <-----CHECK THIS
            errMsg ("After <A> Expected <C>");  //...and write error error message.                              
}


void term1()    // (1) FUNCTION CALLED   
{      
    if (nextToken == A)                     //IF Token is A.... 
        term2();                                //...CONTINUE sequence:   opt.1: <A><C><B>   OR   opt.2: <A> 
    
        else                                //IF Token is NOT A, END sequence....
    {
        if (nextToken != B)                     //(write the message only if nextToken NOT B) <-----CHECK THIS
            errMsg ("The first must be <A>");   //...and write error message.  
        lex();                                  //...and generate new lexeme.     
    }
}