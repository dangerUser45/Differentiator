#define TX_COMPILED
#include "..\SuperLibs\TXLib.h"

#include "Diff_Common.h"
#include "Recursive_descent.h"
#include "Diff_init.h"
#include "Eval.h"
#include "Diff.h"
#include "Diff_Dump.h"
#include "LaTeX.h"

extern FILE* Log_File;
extern FILE* Graph_File;
extern FILE* Graph_File_Utf8;

//==================================================================================================
int main (int argc, char* argv[])
{
    diff* diff_data = Diff_init (argc, argv);

    node* node_root =  GetGrammatic(diff_data ->onegin->buffer_addr); 
    Dump_tree (node_root);

    val_t value = Eval(node_root);
    printf ("Eval value = %" TYPE "", value);

    node* node_d = Diff(node_root);
    Dump_tree (node_d);

    LaTeX_print_expression (node_root, node_d);

    txDisableAutoPause ();  
}
//==================================================================================================
