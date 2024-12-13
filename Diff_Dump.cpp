#include "Diff_Dump.h"
#include "Diff_Init.h"

extern FILE* Log_File;
extern FILE* Graph_File;
extern FILE* Graph_File_Utf8;

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
int Dump_tree (node* node_)
{
    if (!node_) return 1;

    Graph_File      = Create_file ("Dot.txt");
    Graph_File_Utf8 = Create_file ("Dot_UTF-8.txt");

    static size_t number_pic = 1;
    
    char* name_cmd = (char*) calloc (64, sizeof (char));
    char* name_pic = (char*) calloc (16, sizeof (char));

    snprintf (name_cmd, 64, "dot Dot_UTF-8.txt -Tpng -o Diff_tree/tree_%zu.png", number_pic);
    snprintf (name_pic, 16, "tree_%zu.png", number_pic);

    Dump_graph_init (node_);

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
void Dump_graph_init (node* node_)
{
    fprintf (Graph_File, "digraph\n" 
    "{\n"
    "\trankdir = TB;\n\n");
    
    Dump_graph_recursive (node_, 1);

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
