#define TX_COMPILED
#include "..\SuperLibs\TXLib.h"

#include "Diff_Common.h"
#include "Recursive_descent.h"
#include "Diff_init.h"
#include "Eval.h"
#include "Diff.h"
#include "Diff_Dump.h"
#include "LaTeX.h"
#include "Diff_Dtor.h"
#include "Diff_Simpl.h"

extern FILE* Log_File;
extern FILE* Graph_File;
extern FILE* Graph_File_Utf8;

//==================================================================================================
int main (int argc, char* argv[])
{
    diff* diff_data = Diff_init (argc, argv);

    node* Node =  GetGrammatic(diff_data ->onegin->buffer_addr);        
    Dump_tree (Node);
    Simplification (&Node); 
    Dump_tree (Node);


    val_t value = Eval(Node);
    printf ("Eval value = %" TYPE "\n", value);

    node* node_d = Diff(Node);
    Dump_tree (node_d);
    Simplification (&node_d);
    Dump_tree (node_d);


    LaTeX_print_expression (Node, node_d);

    Del_tree(Node, &Node);
    Del_tree(node_d, &node_d);

    printf ("All Good\n");
    txDisableAutoPause ();
}
//==================================================================================================
