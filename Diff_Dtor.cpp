#include "Diff_common.h"
#include "Diff_Dtor.h"

 void Del_tree (node* Node, node** Node_addr)
{
	if (Node -> left  != NULL) Del_tree(Node -> left,  &Node -> left);  
	if (Node -> right != NULL) Del_tree(Node -> right, &Node -> right); 

	if (Node != NULL) {free(Node); *Node_addr =  NULL;}
}
//==================================================================================================    