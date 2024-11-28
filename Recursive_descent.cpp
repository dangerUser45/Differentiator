#include <stdio.h>
#include <stdlib.h>
#include "diff.h"
#include "Recursive_descent.h"

static node* GetExpression ();
static node* GetTerm ();
static node* GetPrime ();
static node* GetTrigonometry ();
static node* GetVar ();
static node* GetBracketEx ();
static node* GetNumber ();
static void SyntaxError ();

const char* string  = 0;
int         pointer = 0;

//==================================================================================================
node* GetGrammatic (const char* buffer)
{
    string = buffer;
    node* node_val = GetExpression ();

    if (string[pointer] != '$')
        SyntaxError ();
    else 
        pointer++;
    
    return node_val;
}
//==================================================================================================
node* GetExpression ()
{
    node* node_val1 = GetTerm ();

    while (string[pointer] == '+' || string[pointer] == '-')
    {
        char op = string[pointer];
        pointer++;
        node* node_val2 = GetTerm ();

    if (op == '+')
         node_val1 = _ADD (node_val1, node_val2);
    else node_val1 = _SUB (node_val1, node_val2);
    }

    return node_val1;
}
//==================================================================================================
node* GetTerm ()
{
    node* node_val1 = GetPrime ();

    while (string[pointer] == '*' || string[pointer] == '/')
    {
        char op = string[pointer];
    pointer++;
    node* node_val2 = GetPrime ();

    if (op == '*')
         node_val1 = _MUL (node_val1, node_val2);
    else node_val1 = _DIV (node_val1, node_val2);
    }

    return node_val1;
}
//==================================================================================================
node* GetPrime ()
{
    node* node_val = 0;
    if (string[pointer] == '(')
    {
        pointer++;
        node_val = GetExpression ();
        if (string[pointer] != ')')
            SyntaxError ();
        pointer++;
        return node_val;
    }
    else if (string[pointer] == 'x')
        return GetVar ();

    else node_val = GetTrigonometry ();
        if (node_val)
            return node_val;      
        else 
            return GetNumber ();
}
//==================================================================================================
node* GetNumber()
{
    int val = 0;
    int old_pointer = pointer;
    while ('0' <= string[pointer] && string[pointer] <= '9')
    {
        val = val * 10 + string[pointer] - '0';
        pointer++; 
    }
    if (old_pointer == pointer) SyntaxError ();

    return Create_node (NUM, val, 0, 0);
}
//==================================================================================================
node* GetVar ()
{
    pointer++;
    node* node_var = _X;
    
    return node_var;
}
//==================================================================================================
node* GetTrigonometry ()
{
    if (string[pointer] == 'c')              {
    pointer++;
    node* node = GetBracketEx ();
    return _COS(node);                       }

    else if (string[pointer] == 's')         {
    pointer++;
    node* node = GetBracketEx ();
    return _SIN(node);                       }

    else return 0;
}
//==================================================================================================
node* GetBracketEx ()
{
   if (string[pointer] == '(')
    {
        pointer++;
        node* node_val = GetExpression ();
        if (string[pointer] != ')')
            SyntaxError ();
        pointer++;
        return node_val;
    }
    else SyntaxError;
    return 0;
}
//==================================================================================================
void SyntaxError ()
{
    printf ("Syntax Error\n");
    exit (1);
}
//==================================================================================================
