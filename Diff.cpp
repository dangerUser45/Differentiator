#include "Diff.h"

extern FILE* Log_File;

node* Check_and_Create (char* buffer);

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
    if (Node -> type == NUM) return _NUM(0);
    else if (Node -> type == VAR) return _NUM(1) ;

    else
        switch ((int)Node -> val)
        {
            case ADD:                             {
            node* dl = _dl; node* dr = _dr;
            return Create_node (OP, ADD, dl, dr); }

            case SUB:                             {
            node* dl = _dl; node* dr = _dr;
            return Create_node (OP, SUB, dl, dr); }

            case MUL:                                     {
            node* dl = _dl; node* dr = _dr;
            return _ADD(_MUL(_dl, _cl), _MUL (_cr, _dr)); }
        
            case DIV:                                                                                   {
            node* dl = _dl; node* dr = _dr;
            return _DIV( _SUB ( _MUL(_dl, _cl), _MUL (_cr, _dr) ), _MUL(Node -> right, Node -> right)); }

            default: DBG (printf ("Error in: %s, %d", __FILE__ ,__LINE__);
            return 0;);
        }
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
Tex_print (node* Node)
{
    fprintf (Tex_File, "$")
    fprintf (Tex_File, "\frac")


}