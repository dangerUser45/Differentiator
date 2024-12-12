#include "Diff_common.h"
#include "Diff_Dtor.h"

 void Del_tree (node* Node)
{
	if (Node -> left  != NULL) {Del_tree(Node -> left);  printf ("Im want del node: %p\n", Node ->left); }
	if (Node -> right != NULL) {Del_tree(Node -> right); printf ("Im want del node: %p\n", Node ->right);}

	free(Node);
}
//==================================================================================================
void Dtor_tree (node* Node)
{
    Del_tree (Node);
    //Node = NULL;
}
//==================================================================================================