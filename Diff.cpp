#define TX_COMPILED
#include "..\SuperLibs\TXLib.h"

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "..\Processor\Onegin_for_proc\Onegin_processing.h"
#include "..\Processor\Onegin_for_proc\Onegin_General.h"
#include "Recursive_descent.h"

extern FILE* Log_File;
extern FILE* Graph_File;
extern FILE* Graph_File_Utf8;

//==================================================================================================
int main (int argc, char* argv[])
{
    diff* diff_data = Diff_init (argc, argv);
    diff_data ->onegin->buffer_addr;

    node* result =  GetGrammatic(diff_data ->onegin->buffer_addr);  
    Dump_tree (result, result);

    txDisableAutoPause ();  
}
//==================================================================================================
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

            /*else if (isalpha (*buffer) && isalpha (*(buffer + 1))) 
                Create_node (VAR, *buffer, 0, 0);

            else
                Create_node (OP, *buffer, 0, 0);*/
        }
             

                                         
    
}
//==================================================================================================
node* Check_and_Create (char* buffer)
{
    node* new_node = 0;
    if (*buffer == '(') 
        return  new_node = Create_node (OP, 0, 0, 0);
    return 0;
}
//==================================================================================================
char* Skip_space (const char* ptr) 
{
    while (1)
        if (*ptr == ' ' || *ptr == '\t' || *ptr == '\r' || *ptr == '\n' )
            ++ptr;
        else break;
    
    return (char*) ptr;
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
void Close_File (FILE* file)
{
    if (file) fclose (file); 
    return;
}
//==================================================================================================
int Dump_tree (node* node_, node* new_node)
{
    if (!node_) return 1;
    assert (new_node);

    Graph_File      = Create_file ("Dot.txt");
    Graph_File_Utf8 = Create_file ("Dot_UTF-8.txt");

    static size_t number_pic = 1;
    
    char* name_cmd = (char*) calloc (64, sizeof (char));
    char* name_pic = (char*) calloc (16, sizeof (char));

    snprintf (name_cmd, 64, "dot Dot_UTF-8.txt -Tsvg -o Diff_tree/tree_%zu.svg", number_pic);
    snprintf (name_pic, 16, "tree_%zu.svg", number_pic);

    Dump_graph_init (node_, new_node);

    Close_File (Graph_File);
    Close_File (Graph_File_Utf8);

    system ("D:\\Приложения\\iconv\\gettext-iconv\\bin\\iconv.exe -f CP1251 -t UTF-8 Dot.txt > Dot_UTF-8.txt");
    system (name_cmd);

    fprintf (Log_File ,"\n<img src = \"Diff_tree/%s\" width = %d%%>\n\n\n\n\n\n\n\n\n\n", name_pic, SCALE);
    fflush (Graph_File);
    ++number_pic;
    
    free (name_cmd);
    free (name_pic);

    return 0;
}
//==================================================================================================
void Dump_graph_init (node* node_, node* new_node)
{
    fprintf (Graph_File, "digraph\n" 
    "{\n"
    "\trankdir = TB;\n\n");
    
    Dump_graph_recursive (node_, 1);

    /*fprintf(Graph_File, "\n"   
        "\tnode_%p [ color = \"#d48608\", fillcolor = \"#ffa615\"];\n", new_node);*/
    fprintf (Graph_File, "}");

}
//==================================================================================================

void Dump_graph_recursive (node* node_diff, size_t rank)
{
    if (!node_diff) return;
    Draw_tree (node_diff);

    fprintf (Graph_File, ""
        "\t{\n"                                                        
            "\t\tnode[ color = \"#581845\", shape = \"circle\", style = \"filled\" ,fillcolor=\"#fe5656\"];\n"
            "\t\tedge[ color = \"white\"]\n"
            "\t\t\"%zu\" ->  \"%zu\";\n", rank, rank + 1);
    
    fprintf (Graph_File,  "\t}\n\n"
        "\t{ rank = %zu; \"%zu\"; \"node_%p\" }\n", rank, rank, node_diff);

    if (node_diff -> left != NULL)
    {
        Draw_tree (node_diff -> left);
        fprintf (Graph_File, ""   //!!!
        "\tnode_%p  -> node_%p [color = \"#ff0000\", fontsize = 16];\n", node_diff, node_diff -> left);
    }

    else {
        fprintf(Graph_File, "\n"
        "\t{\n"
            "\t\tnode [ color = \"#007cff\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#a2f0f8\"];\n"
            "\t\tedge [ color = \"#007cff\", fontsize = 16];\n\n"

            "\t\tnode_l_null_%p [shape = \"ellipse\", label = \" null\" ];\n", node_diff);
        
        fprintf(Graph_File, ""
            "\t\tnode_%p  -> node_l_null_%p;\n", node_diff, node_diff);
        fprintf(Graph_File, ""
            "\t}\n");
        }  

    if (node_diff -> right != NULL)
    {
        Draw_tree (node_diff -> right);
        fprintf(Graph_File, "\n" //!!!
        "\tnode_%p  -> node_%p[color = \"#ff0000\", fontsize = 16];\n", node_diff, node_diff -> right);
    }

    else {
        fprintf(Graph_File, "\n"
        "\t{\n"
            "\t\tnode [ color = \"#007cff\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#a2f0f8\"];\n"
            "\t\tedge [ color = \"#007cff\", fontsize = 16];\n\n"

            "\t\tnode_r_null_%p [shape = \"ellipse\", label = \" null\" ];\n", node_diff);
        
        fprintf(Graph_File, ""
            "\t\tnode_%p  -> node_r_null_%p;\n", node_diff, node_diff);
        fprintf(Graph_File, "" 
            "\t}\n");
          }

    fprintf (Graph_File, ""
    "\t{\n"                                                        
        "\t\tnode[ shape = \"plaintext\", style = \"filled\" ,fillcolor=\"white\"];\n"
        "\t\tedge[ color = \"white\"]\n"
        "\t\t\"%zu\" ->  \"%zu\";\n", rank, rank + 1);

    fprintf (Graph_File, ""
    "\t}\n");

        ++rank;

        Dump_graph_recursive (node_diff -> left, rank);
        Dump_graph_recursive (node_diff -> right, rank);

}
//==================================================================================================
void Draw_tree (node* node_diff)
{
     if (node_diff -> type == NUM){
            fprintf(Graph_File, ""
        "\tnode_%p [ color = \"#18ca1c\", style = \"filled\", fillcolor = \"#a2f8a4\", shape = \"Mrecord\", label = \"{ addr: %p | val = %" TYPE "  | type = %s | { L:\\n addr: %p | R: \\n addr: %p } }\" ];\n", node_diff, node_diff, node_diff -> val, "NUM", node_diff -> left, node_diff -> right);
        }

    else if (node_diff -> type == VAR){
            fprintf(Graph_File, ""
        "\tnode_%p [ color = \"#d408ac\", style = \"filled\", fillcolor = \"#ff5fe0\", shape = \"Mrecord\", label = \"{ addr: %p | val = \'%c\'| type = %s | { L:\\n addr: %p | R: \\n addr: %p } }\" ];\n", node_diff, node_diff, (char)node_diff -> val, "VAR", node_diff -> left, node_diff -> right);
        }

    else if (node_diff -> type == OP){
        fprintf(Graph_File, ""
        "\tnode_%p [ color = \"#ffc500\", style = \"filled\", fillcolor = \"#ecfd74\", shape = \"Mrecord\", label = \"{ addr: %p | val = \'%c\' |  type = %s | { L:\\n addr: %p | R: \\n addr: %p } }\" ];\n", node_diff, node_diff, (char)node_diff -> val, "OP", node_diff -> left, node_diff -> right);
        }
}
//=================================================================================================
