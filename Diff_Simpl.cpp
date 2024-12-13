#include <math.h>
#include "Diff_Common.h"
#include "Eval.h"
#include "Diff.h"
#include "Diff_Simpl.h"
#include "Diff_Dtor.h"

extern FILE* Log_File;

static node* Const_Folding (node* Node);
static node* Clear_redundant (node* Node);

//==================================================================================================
void Simplification (node** Node_addr)
{
    *Node_addr = Const_Folding (*Node_addr);
    *Node_addr = Clear_redundant (*Node_addr);
    *Node_addr = Const_Folding (*Node_addr);
}
//==================================================================================================
static node* Const_Folding (node* Node)
{
    if (!Node) return 0;
    node* New_Node = 0;
    static int level_recursive = 1;
            level_recursive++;

    if (Node -> type == VAR) return Node;
    if (Node -> type == NUM) return Node;
    else if (!Var_Count_Envelope (Node))
    {   
        val_t value = Eval (Node);
        New_Node = Create_node (NUM, value, 0, 0);
        
        Del_tree (Node, &Node);
        return New_Node;

    }
    if (Node -> left)  Node -> left  = Const_Folding (Node -> left);
    if (Node -> right) Node -> right = Const_Folding (Node -> right);

    return Node;
}
//==================================================================================================
#define DEL_TREE(text) Del_tree (text, &(text))

static node* Clear_redundant (node* Node)
{
    node* New_Node = 0;
    static int level_recursive = 0; level_recursive++;
    if (!Node) return Node;

    switch (Node ->type)
    {
        case VAR: 
            return Node;
        case NUM: 
            return Node;
        case OP:
            switch ((int) Node -> val)
            {
                case ADD:
                {   
                    if (Node -> left == 0)    {
                        DEL_TREE(Node -> left);
                        return Node -> right; }

                    if (Node -> right == 0)       {
                        DEL_TREE (Node -> right);
                        return Node -> left;      }
    
                    break;
                }
                
                case MUL:
                {
                    if (Node -> left -> val == 0 || Node -> right -> val == 0) {
                        DEL_TREE (Node);
                        return _NUM(0);                                        }

                    else if (Node -> left -> val == 1) {
                        DEL_TREE (Node -> left);
                        return Node -> right;          }

                    else if (Node -> right -> val == 1) {
                        DEL_TREE (Node -> right);
                        return Node -> left;            }  

                    break;
                }

                case SUB:
                {
                    if (Node -> right -> val == 0) {
                        DEL_TREE (Node -> right);
                        return Node -> left;       }

                    break;
                }

                case DIV:
                {
                    if (Node -> left -> val == 0) {
                        DEL_TREE (Node);
                        return _NUM(0);            }
                        
                    if (Node -> right -> val == 0)                           {
                    fprintf (stderr, "ERORR: You can't multiply by zero\n"); }

                    if (Node -> right -> val == 1) {
                    DEL_TREE (Node -> right);
                    return Node -> left;           }

                    break;
                }

                case POW:
                {
                    if (Node -> left-> val== 1)  {
                        DEL_TREE (Node -> right);
                        return _NUM(1);          }

                    if (Node -> right ->val == 1) {
                        DEL_TREE (Node -> right);
                        return Node -> left;      }
                
                    break;
                }

                case LOG:
                {
                    if (Node -> left -> val <= 0 && Node ->left -> val == 1)                                      {
                        fprintf (stderr, "ERROR: The sublogarithmic base cannot be equal to 1 or less than 0\n"); }
                    if (Node -> right -> val == 1) {
                        DEL_TREE(Node);
                        return _NUM(0);            }
                    
                    break;
                }

                case LN:
                {
                    if (Node ->left -> val != exp(1))
                        fprintf (stderr, "ERROR: The base of a natural logarithm is not equal to exp\n");
                    if (Node -> right -> val == 1) {
                        DEL_TREE (Node);
                        return _NUM(0);            }
                        
                    break;
                }
            
                case COS:
                {
                    if (Node -> left ->val == 0)    {
                        DEL_TREE (Node -> left);
                        return _NUM(0);             }
                    if (Node -> left -> val == 1)   {
                        DEL_TREE (Node -> left);
                        return _NUM(1);             }

                break;
                }

                case SIN:
                {
                    if (Node -> left ->val == 0)    {
                        DEL_TREE (Node -> left);
                        return _NUM(1);             }
                    if (Node -> left -> val == 1)   {
                        DEL_TREE (Node -> left);
                        return _NUM(0);             }
                        
                break;
                }

                case TAN:
                {
                    if (Node -> left ->val == 0)    {
                        DEL_TREE (Node -> left);
                        return _NUM(0);             }
                    if (Node -> left -> val == 1)   
                        fprintf (stderr, "ERROR: argument tan(1) is invalid\n");
                                     
                break;
                }

                case EXP:
                {
                    if (Node -> left ->val == 1)       {
                        DEL_TREE (Node -> left); 
                        return _NUM(0);          }

                break;
                }

                default: DBG(printf ("ERROR IN %S %d\n", __FILE__, __LINE__););
            }

        default: DBG(fprintf (Log_File, "ERROR IN %s %d\n", __FILE__, __LINE__););
    }

    if (Node -> left)  Node -> left  =  Clear_redundant (Node ->left);
    if (Node -> right) Node -> right =  Clear_redundant (Node ->right);

    return Node;
}
#undef DEL_TREE
//==================================================================================================
