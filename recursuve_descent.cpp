#include <stdio.h>
#include <stdlib.h>
#include "diff.h"

int GetN ();
int GetP ();
int GetE ();
int GetT ();
int GetG ();
void SyntaxError ();


const char* s = "(5+5)*(18-8)/2+2$";
int p = 0;

//==================================================================================================
int main ()
{
    printf ("im here\n");  
    int result =  GetG();
    printf ("result = %d", result);
}

//==================================================================================================
int GetP ()
{
    if (s[p] == '(')
    {
        p++;
        int val = GetE ();
        if (s[p] != ')')
            SyntaxError ();
        p++;
        return val;
    }

    else 
        return GetN ();
}
//==================================================================================================
int GetE ()
{
    int val = GetT ();
    while (s[p] == '+' || s[p] == '-')
    {
        int op = s[p];
        p++;
        int val2 = GetT ();

    if ((char)op == '+')
         val += val2;
    else val -= val2;
    }

    return val;
}
//==================================================================================================
int GetT ()
{
    int val = GetP ();
    while (s[p] == '*' || s[p] == '/')
    {
        int op = s[p];
    p++;
    int val2 = GetP ();

    if ((char)op == '*')
        val *= val2;
    else val /= val2;
    }

    return val;
}
//==================================================================================================
int GetG ()
{
    int val = GetE ();
    if (s[p] != '$')
        SyntaxError ();
    else p++;
    return val;
}
//==================================================================================================
void SyntaxError ()
{
    printf ("Syntax Error\n");
    exit (1);
}
//==================================================================================================
