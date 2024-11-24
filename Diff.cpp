#include <stdio.h>
#include "..\Processor\Onegin_for_proc\Onegin_processing.h"
#include "..\Processor\Onegin_for_proc\Onegin_General.h"
//#include "..\Akinator\akinator.h"
#include "Diff.h" 

extern FILE* Log_File;
extern FILE* Graph_File;
extern FILE* Graph_File_Utf8;

//==================================================================================================
int main (int argc, char* argv[])
{
    Diff_init (argc, argv);
    //Create_node (OP, DIV, Create_node (OP, ADD,  _NUM(30), _NUM(150)), Create_node (OP, SUB, _NUM(12),_X));
    Create_node (OP, SUB, _NUM(12),_X);
    


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
//==================================================================================================
void Close_File (FILE* file)
{
    if (file) fclose (file); 
    return;
}
//==================================================================================================
int Dump_akin (node* node_, node* new_node)
{
    if (!node_) return 1;
    assert (new_node);

    Graph_File = Create_file ("Dot.txt");
    Graph_File_Utf8 = Create_file ("Dot_UTF-8.txt");

    static size_t number_pic = 1;
    
    
    char* name_cmd = (char*) calloc (64, sizeof (char));
    char* name_pic = (char*) calloc (16, sizeof (char));

    snprintf (name_cmd, 64, "dot Dot_UTF-8.txt -Tsvg -o Picture_tree/tree_%zu.svg", number_pic);
    snprintf (name_pic, 16, "tree_%zu.svg", number_pic);

    Dump_graph_init (node_, new_node);

    Close_File (Graph_File);
    Close_File (Graph_File_Utf8);

    system ("D:\\Приложения\\iconv\\gettext-iconv\\bin\\iconv.exe -f CP1251 -t UTF-8 Dot.txt > Dot_UTF-8.txt");
    system (name_cmd);

    fprintf (Log_File ,"\n<img src = \"Picture_tree/%s\" width = %d%%>\n\n\n\n\n\n\n\n\n\n", name_pic, SCALE);
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
    
    "\trankdir = TB;\n"
        "\tnode [ color = \"#004b00\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#a2f8a4\"];\n"
        "\tedge [ color = \"#004b00\", fontsize = 16];\n\n");

    Dump_graph_recursive (node_, 1);

    fprintf(Graph_File, "\n"   
            "\tnode_%p [ fillcolor = \"#ffa615\"];\n", new_node);

    fprintf (Graph_File, "}");
}
//==================================================================================================
void Dump_graph_recursive (node* node_, size_t rank)
{
    if (!node_) return;                                                                                                                    
    
    fprintf(Graph_File, ""
        "\tnode%p [ shape = \"Mrecord\", label = \"{ data = %" TYPE " \\n addr: %p | { L:\\n addr: %p | R: \\n addr: %p } }\" ];\n", node_, node_ -> val, node_, node_ -> left, node_ -> right);

    fprintf (Graph_File, ""
        "\t{\n"                                                        
            "\t\tnode[ color = \"#58184PE\", shape = \"circle\", style = \"filled\" ,fillcolor=\"#fe5656\"];\n"
            "\t\tedge[ color = \"white\"]\n"
            "\t\t\"%zu\" ->  \"%zu\";\n", rank, rank + 1);
    
    fprintf (Graph_File,  "\t}\n\n"
        "\t{ rank = %zu; \"%zu\"; \"node%p\" }\n", rank, rank, node_);

    if (node_ -> left != NULL)
    {
        fprintf(Graph_File, "\n"
        "\tnode%p[ shape = \"Mrecord\", label = \"{ data = %" TYPE "\\n addr: %p | { L:\\n addr: %p |   R: \\n addr: %p } }\" ];\n", node_ -> left,  node_ -> left -> val, node_ -> left, node_ -> left -> left, node_ -> left -> right);
        fprintf (Graph_File, ""
        "\tnode%p  -> node%p;\n", node_, node_ -> left);
    } 
    
    else {
        fprintf(Graph_File, "\n"
        "\t{\n"
            "\t\tnode [ color = \"#007cff\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#a2f0f8\"];\n"
            "\t\tedge [ color = \"#007cff\", fontsize = 16];\n\n"

            "\t\tnode_l_null_%p[ shape = \"ellipse\", label = \"null\" ];\n", node_);
        fprintf(Graph_File, ""
            "\t\tnode_%p  -> node_l_null_%p;\n", node_, node_);
        fprintf(Graph_File, ""
            "\t}\n");
        }  

    if (node_ -> right != NULL)
    {
        fprintf(Graph_File, "\n"   
            "\tnode_%p [ shape = \"Mrecord\", label = \" { data = %" TYPE "\\n addr: %p | { L:\\n addr: %p | R: \\n addr: %p } }\" ];", node_ -> right, node_ -> right -> val, node_ -> right, node_ -> right -> left, node_ -> right -> right);
        fprintf(Graph_File, "\n"
            "\tnode_%p  -> node_%p;\n", node_, node_ -> right);
    }

    else {
        fprintf(Graph_File, "\n"
        "\t{\n"
            "\t\tnode [ color = \"#007cff\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#a2f0f8\"];\n"
            "\t\tedge [ color = \"#007cff\", fontsize = 16];\n\n"

            "\t\tnode_r_null_%p [shape = \"ellipse\", label = \" null\" ];\n", node_);
        
        fprintf(Graph_File, ""
            "\t\tnode_%p  -> node_r_null_%p;\n", node_, node_);
        fprintf(Graph_File, "" 
            "\t}\n");
          }

        fprintf (Graph_File, ""
        "\t{\n"                                                        
            "\t\tnode[ shape = \"plaintext\", style = \"filled\" ,fillcolor=\"white\"];\n"
            "\t\tedge[ color = \"white\"]\n"
            "\t\t\"%zu\" ->  \"%zu\";\n", rank, rank + 1);

        fprintf (Graph_File, ""
        "\t}\n\n");

        ++rank;

        Dump_graph_recursive (node_ -> left, rank);
        Dump_graph_recursive (node_ -> right, rank);
}
//==================================================================================================
