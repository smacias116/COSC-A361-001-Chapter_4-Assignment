// SYMBOL TABLE

#include <iostream>
using namespace std;

struct item 
{
    string name;    // to store variable name
    int intValue;   // to store value
};
item symbolTable[100];
int ind = 0;      // index to top of symbol table

void add_symbol(string name, int value) 
{
    symbolTable[ind].name = name;
    symbolTable[ind].intValue = value;
    ind++;
}

void prt_symbol() 
{
    cout << "Symbol table:";
    cout << "Name\tValue\n";
    for (int i=0; i<ind; i++) 
        cout << symbolTable[i].name << "\t" << symbolTable[i].intValue << endl;
}

bool search_symbol (string lexeme) 
{
    for (int i=0; i<ind; i++)
        if (symbolTable[i].name == lexeme) 
            return true;
    return false;
}