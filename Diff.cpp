#include <stdio.h>
#include "..\Processor\Onegin_for_proc\Onegin_processing.h"
#include "..\Processor\Onegin_for_proc\Onegin_General.h"
#include "..\Akinator\akinator.h"
#include "Diff.h" 

extern FILE* Log_File;

//==================================================================================================
int main (int argc, char* argv[])
{
    Diff_init (argc, argv);
    //Create_node (OP, DIV, Create_node (OP, ADD, _NUM(30), _NUM(150)), Create_node (OP, SUB, _NUM(12),_X));
    //Create_node (OP, SUB, _NUM(12),_X);    
    _X;



}
//==================================================================================================
node* Create_node (type_t type, double data, node* node_left, node* node_right)
{
    node* new_node = (node *) calloc (1, sizeof (node));
    if (!new_node) {fprintf (Log_File, "Error!"); assert (new_node);}

    new_node -> type = type;
    new_node -> val = data;
    
    return new_node;
}