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
            //DBG(fprintf (stderr, "\nI just go to Const Folding, level recursive = %d,  Node = %p, Node -> value = <%c>\n", level_recursive, Node, Node -> val);)
            level_recursive++;

    if (Node -> type == VAR) { //DBG(printf ("I got myself in case: VAR, will return Node = %p\n", Node);)
        return Node;}
    if (Node -> type == NUM) { //DBG(printf ("I got myself in case: NUM, will return Node = %p\n", Node);)
         return Node;}
    else if (!Var_Count_Envelope (Node))
    {   
                //DBG(printf ("I in case: OP, number of var = %zu\n", Var_Count_Envelope (Node));)
                //DBG(fprintf (stderr, "I will do valuate\n");)
        val_t value = Eval (Node);
                //DBG(fprintf (stderr, "I valuating value = %lg, will create new_node\n", value);)
        New_Node = Create_node (NUM, value, 0, 0);
        // DBG(printf ("New_Node = %p", New_Node);)
                //DBG(fprintf (stderr, "I create node: New_Node =  %p, New_node -> value = %d, will delete old tree\n", New_Node, New_Node -> val);)
        
        Del_tree (Node, &Node);
                //DBG(fprintf (stderr, "I del tree: Node =  %p will return New_Node  = %p\n", Node, New_Node);)
        return New_Node;

    }
            //DBG(fprintf (stderr, "I will check on Node ->left\n");)
    if (Node -> left)  Node -> left  = Const_Folding (Node -> left);
            //DBG(fprintf (stderr, "I will check on Node -> right\n");)
    if (Node -> right) Node -> right = Const_Folding (Node -> right);
            // DBG(printf ("I will return New_Node = %p\n", New_Node);)

    return Node;
}
//==================================================================================================
#define DEL_TREE(text) Del_tree (text, &(text))

static node* Clear_redundant (node* Node)
{
    node* New_Node = 0;
    static int level_recursive = 0; level_recursive++;
   // DBG(printf ("I just in Clear_redundant (), levelvrecursive = %d, Node = %p, Node -> val = %d\n", level_recursive, Node, Node -> val);)
    if (!Node) return Node;

    switch (Node ->type)
    {
        case VAR: 
            //DBG(printf ("I in VAR, Node = %p, Node val = %lg\n", Node, Node ->val);)
            return Node;
        case NUM: 
            //DBG(printf ("I in NUM, Node = %p, Node val = %lg\n", Node, Node -> val);)
            return Node;
        case OP:
            switch ((int) Node -> val)
            {
                //DBG(printf ("I in OP: Node = %p, Node -> val = %d\n", Node, Node -> val);)
                case ADD:
                {   //DBG(printf ("I in ADD: Node = %p, Node -> val = %d\n", Node, Node -> val);)

                    if (Node -> left == 0)    {
                        DEL_TREE(Node -> left);
                        return Node -> right; }

                    if (Node -> right == 0)       {
                        DEL_TREE (Node -> right);
                        return Node -> left;      }
                            //DBG(printf("I in do six por case: ADD, will break ");)

                    break;
                }
                
                case MUL:
                {
                    //DBG(printf ("I in MUL: here");)
                    if (Node -> left -> val == 0 || Node -> right -> val == 0) {
                       // printf ("\t\t\t1Im here\t\t\t");
                        DEL_TREE (Node);
                        return _NUM(0);                                        }

                    else if (Node -> left -> val == 1) {
                        //printf ("\t\t\t2Im here\t\t\t");
                        DEL_TREE (Node -> left);
                        return Node -> right;          }

                    else if (Node -> right -> val == 1) {
                        //printf ("\t\t\t3Im here\t\t\t");
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
                break;

                case LN:
                break;
            
                case COS:
                break;

                case SIN:
                break;

                case TAN:
                break;

                case EXP:
                break;

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
