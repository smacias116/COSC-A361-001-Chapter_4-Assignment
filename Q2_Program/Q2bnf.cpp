// PARSER

#include <iostream>
using namespace std;

void term1(); 

void term3()            // (3)rd FUNCTION to be executed:
{
    lex();                                              //First, Generate NEXT Lexeme...

    if (nextToken == B)                                 //IF Token is B, and...
    {
        if (nextChar == '\n')                               //...then there's a new line:   Sequence COMPLETED...
            lex();                                              //...Generate new lexeme (next line to parse)

        else                                                //...then there's any other character ('\n')...
        {
            lex();                                              //(Generate new lexeme to continue)
            errMsg ("Sequence should ends after <B>");          //...WRONG! --> write error message
        }
    }       

    else                                                //IF Token is NOT B...
    {
        lex();                                              //(Generate new lexeme to continue)
        errMsg ("Sequence should ends after <B>");          //...WRONG! --> write error message  
    }
}



void term2()            // (2)st FUNCTION to be executed:
{
    lex();                                              //First, Generate NEXT Lexeme...

    if (nextToken == C)                                 //IF Token is C, and...
    {
        if (nextChar == 'b')                                //...the next character is 'b': CONTINUE sequence   --> opt.1: ...<C><B>  
            term3();
        else                                                //...the next character is NOT 'b'...
        {
            lex();                                              //(Generate new lexeme to continue)
            errMsg ("After token <C>, expected token <B>");     //...WRONG! --> write error message  
        }
    }    

    else                                                //IF Token is NOT C...
    {
        lex();                                              //(Generate new lexeme to continue)
        errMsg ("After token <A>, expected token <C>");     //...WRONG! --> write error message
    }                   
}



void term1()            // (1)st FUNCTION to be executed:
{      
    if (nextToken == A)                                 //IF Token is A, and...
    {
        if (nextChar == 'c')                                //...the next character is 'c': CONTINUE sequence   --> opt.1: <A><C><B>
            term2();
        else if (nextChar == '\n')                          //...then there's a new line:   Generate NEXT lexme --> opt.2: <A>
            lex();      
        else                                                //...then there's any other character (other than 'c' or '\n')...
        {
            lex();                                              //(Generate new lexeme to continue)
            errMsg ("After token <A>, expected token <C>");     //...WRONG! --> write error message 
        }
    }

    else                                                //IF Token is NOT A...
    {
        lex();                                              //(Generate new lexeme to continue)
        if (nextToken != ENDFILE)                           //(Avoid writing messages if already at the EOF)
            errMsg ("The first token must be <A>");         //...WRONG! --> write error message.
    }   
}