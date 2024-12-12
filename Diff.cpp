#include "Diff.h"
#include "Eval.h"

extern FILE* Log_File;

node* Check_and_Create (char* buffer);
size_t Var_Count_Envelope (node* Node);
size_t Var_Count (node* Node, size_t* var_num);

//==================================================================================================
/*
node* Read_equation (char* buffer, node* node_diff)
{
    assert (buffer);
    DBG(static int level_recursive = 0;)

    DBG( PRINT ("Im in Read_equation ():  I'm just getting started. Recursive level: %d", level_recursive);)
    DBG(++level_recursive;)
   
    DBG(if ((level_recursive == 1) && (*buffer != '('))
        {fprintf (Log_File, "<font size = \"5\"><b>You  give me wrong file, f@cking nigga! </b></font>");
        return 0;})

    else 
    {      
        node* new_node = 0;
        node* node_parent = 0;
        val_t value = 0;


        if (*buffer == '(') {
            node_parent = Create_node (OP, 0, 0, 0);
                DBG(PRINT ("I create_node, his addr = %p. Soon will move ptr", new_node);)
            MOVE_PTR;}

            if (*buffer == '(') 
            {
                MOVE_PTR;
                DBG(PRINT ("I moved buffer. Soon will call a Read_equation ()");)
                node* new_node = Read_equation (buffer, node_parent);
                node_parent -> left =  new_node;
                
            } 

            else if (sscanf (buffer, "%" TYPE "", &value) == 1)
            {          
                node* node_diff_val= Create_node (NUM, value, 0, 0);
                        DBG(PRINT ("I create_node, his addr = %p", node_diff_val);)
                buffer = strchr (buffer, ')');
                        DBG(PRINT ("I move to )");)
                        DBG(PRINT ("*buffer = %.20s", buffer);)
                node_diff -> type = NUM;
                return node_diff_val;

            }

            else if (isalpha (*buffer) && isalpha (*(buffer + 1))) 
                Create_node (VAR, *buffer, 0, 0);

            else
                Create_node (OP, *buffer, 0, 0);
        }
             

                                         
    
}*/
//==================================================================================================
node* Check_and_Create (char* buffer)
{
    node* new_node = 0;
    if (*buffer == '(') 
        return  new_node = Create_node (OP, 0, 0, 0);
    return 0;
}
//==================================================================================================
node* Create_node (type_t type, double data, node* node_left, node* node_right)
{
    node* new_node = (node *) calloc (1, sizeof (node));
    if (!new_node) {fprintf (Log_File, "Error!"); assert (new_node);}

    new_node -> type  = type;
    new_node -> val   = data;
    new_node -> left  = node_left;
    new_node -> right = node_right;

    return new_node;
}
//==================================================================================================
node* Diff (node* Node)
{
    if (!Node) return NULL;
    size_t num_left_sub, num_right_sub = 0;
    if (Node -> type == NUM) return _NUM(0);

    else if (Node -> type == VAR) return _NUM(1) ;

    else
        switch ((int)Node -> val)
        {
            case ADD: return Create_node (OP, ADD, _dl, _dr); 

            case SUB: return Create_node (OP, SUB, _dl, _dr); 

            case LOG: 
            {if (!Var_Count_Envelope (Node -> left))
                 return _MUL(_DIV(_DIV(_NUM(1), _cr), _LN(_cl)), _dr);
            else return Diff (_DIV(_LN(_cr), _LN(_cl)));}

            case LN: return _MUL(_DIV(_NUM(1), _cl), _dl);        

            case MUL: return _ADD(_MUL(_dl, _cr), _MUL (_cl, _dr)); 
            
            case DIV: return _DIV( _SUB ( _MUL(_dl, _cr), _MUL (_cl, _dr) ), _MUL(_cr, _cr)); 

            case SIN: return _MUL(_COS(_cl), _dl);

            case COS: return _MUL( _MUL( _NUM(-1), _SIN(_cl)), _dl); 

            case TAN: return _MUL( _DIV(_NUM(1), _POW(_COS(_cl), _NUM(2))), _dl);  

            case EXP: return _MUL( _EXP(_cr), _dr);   
                                                          
            case POW:
            {
                num_left_sub  = Var_Count_Envelope (Node -> left);
                num_right_sub = Var_Count_Envelope (Node -> right);

                if (num_left_sub != NULL && num_right_sub != NULL)
                    return _MUL( _POW( _cl, _cr), _ADD( _MUL( _dr, _LN(_cl)), _MUL( _cr, _DIV( _dl, _cl))));

                else if (num_left_sub != NULL && num_right_sub == NULL)
                    return _MUL( _NUM(Node -> right -> val), _POW(_cl, _SUB(_cr, _NUM(1))));

                else if (num_left_sub == NULL && num_right_sub != NULL) 
                    return _MUL(_MUL( _POW(_cl, _cr), _LN(_cr)), _dr); 

                else 
                    return 0;     
            }

            default: DBG (printf ("Error in: %s, %d\n", __FILE__ ,__LINE__);) return 0;
        }
}
//==================================================================================================
size_t Var_Count_Envelope (node* Node)
{
    size_t* var_num = (size_t*) calloc (1, sizeof (size_t));
    size_t count = Var_Count (Node, var_num);
    free (var_num);

    return count;
}
//==================================================================================================
size_t Var_Count (node* Node, size_t* var_num)
{
    if (!Node) return *var_num;

    if (Node -> type == VAR) (*var_num)++;
    Var_Count (Node -> left, var_num);
    Var_Count (Node -> right, var_num);

    return *var_num;
}
//==================================================================================================

node* Create_copy_node (node* Node)
{
    if (!Node) return Node;
    fprintf (Log_File, "Curr node_addr: %p", Node);
    node* New_Node = Create_node (OP, 0, 0, 0);

    New_Node -> type  = Node -> type;
    New_Node -> val   = Node -> val;
    New_Node -> left  = Node -> left;
    New_Node -> right = Node -> right;

    Create_copy_node (Node -> left);
    Create_copy_node (Node -> right);

    return New_Node;
}
//==================================================================================================
void Const_Folding (node* Node)
{
    if (!Node) return;

    if (Node -> type == VAR) return;
    else if (!Var_Count_Envelope (Node))
    {
        val_t value = Eval (Node);
        node* New_node = Create_node (NUM, value, 0, 0);
        
        //Del_tree (Node);
    }
    
    Const_Folding (Node -> left);
    Const_Folding (Node -> right);
}
//==================================================================================================
