#include "Diff_Init.h"
#include "LaTeX.h"

extern FILE* Log_File;
FILE* Latex_File;

FILE* Ctor_LaTeX ();
int LaTeX_print (node* Node);
int LaTeX_print_expression (node* Node, node* Node_diff);
void Dtor_LaTeX (FILE* file_ptr);

FILE* Ctor_LaTeX ()
{
    Latex_File = Create_file (NAME_LATEX_FILE);

    if (Latex_File)
    {
        
        return Latex_File;
    }
    else {fprintf (Log_File, "Error in %s, $d: Latex_file = NULL;", __FILE__,  __LINE__); exit (1);}
}
//==================================================================================================
int LaTeX_print (node* Node)
{
    if (!Node) return 0;

    if (Node -> type == OP && (Node -> val == '*' || Node -> val == '-' ))
        fprintf(Latex_File, "(");

    if (Node->left != NULL)    {
        fprintf (Latex_File, "{");
        LaTeX_print (Node ->left);
        fprintf (Latex_File, "}"); }

    switch (Node -> type)
    {
        case OP:
            if ((char)Node -> val == '/'){
                fprintf (Latex_File, "\\over");
                break;}
            if((char)Node -> val == '*' || (char)Node -> val == '-'){
                fprintf (Latex_File, ")%c(", (char)Node -> val);
                break;}
            
            
            else {
                fprintf (Latex_File, "%c", (char)Node -> val);
                break;}
        
        case NUM:
            fprintf (Latex_File, "%" TYPE "", Node ->val);
            break;

        case VAR:
            fprintf (Latex_File, "%c", (char )Node ->val);
            break;

        default: DBG (fprintf (Log_File," Error: %s, %d", __FILE__, __LINE__)); return 0;
    }

    if (Node->right != NULL)       {
        fprintf (Latex_File, "{");
        LaTeX_print (Node ->right);
        fprintf (Latex_File, "}"); } 

    if (Node -> type == OP && (Node -> val == '*' || Node -> val == '-' ))
        fprintf(Latex_File, ")");
    return 0;                                                                                                                                       
}
//==================================================================================================
int LaTeX_print_expression (node* Node, node* Node_diff)
{
    assert (Node); assert (Node_diff);

    Ctor_LaTeX ();
    fprintf (Latex_File, "\\documentclass[a4paper,12pt]{article} %%\n\
    \n\
    \n\
    \n\
    \\usepackage{multirow}\n\
    \\usepackage{booktabs}\n\
    \\usepackage{wrapfig}\n\
    \\usepackage[T2A]{fontenc}\n\
    \\usepackage[utf8]{inputenc}\n\
    \\usepackage[english,russian]{babel}\n\
    \\usepackage{multirow}\n\
    \n\
    \\usepackage{indentfirst}\n\
    \\usepackage[a4paper,top=3.3cm,bottom=2cm,left=1.5cm,right=1.5cm,marginparwidth=0.75cm]{geometry}\n\
    \\usepackage[usenames]{color}\n\
    \\usepackage{colortbl}\n\
    \\usepackage{float}\n\
    \n\
    \\usepackage{graphicx}\n\
    \\usepackage{wrapfig}\n\
    \n\
    \n\
    \\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools} \n\
    \\usepackage{hyperref}\n\
    \n\
    \\begin{document}\n\
    \\begin{titlepage}\n\
    {\\huge\n\
    \\begin{center}\n\
    \\underline{{\\bf Differentiator}}\n\
    \\vspace{1cm}\n\
    \n\
    \\end{center}\n\
    }\n\
    \\vspace{2cm}\n\
    \\begin{center}\n\
    \n\
    \n\
    {\\LARGE Momot Danil\n\
    \\vspace{0.2cm}\n\
    BO1-403}\n\
    \\end{center}\n\
    \\vspace{9.5cm}\n\
    \\begin{center}\n\
        Dolgoprudnuy 2024\n\
    \\end{center}\n\
    \\end{titlepage}\n");
    fprintf (Latex_File, "$({");

    LaTeX_print (Node);
    fprintf (Latex_File, "})' = {");
    LaTeX_print (Node_diff);

    fprintf (Latex_File, "}$\n");
    fprintf (Latex_File ,"\\end{document}\n");

    Dtor_LaTeX (Latex_File);

    unlink ("LaTeX_File.pdf");
    system("pdflatex LaTeX_File.tex");  
    
    return 0;
}
//===================================================================================================
void Dtor_LaTeX (FILE* file_ptr)
{
    if (!file_ptr) return;
    else fclose (file_ptr);
}
//===================================================================================================
