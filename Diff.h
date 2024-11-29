#pragma once

#include "..\Processor\Onegin_for_proc\Onegin_General.h" 

enum type_t     {NUM = 1, VAR, OP};
enum operations {ADD = '+', SUB = '-', MUL = '*', DIV = '/', COS = 'c', SIN = 's', POW = '^'};

#define _NUM(val) Create_node (NUM, val, NULL, NULL)
#define _X Create_node (VAR, 'x', NULL, NULL)

#define _ADD(val1, val2) Create_node (OP, ADD, val1, val2)
#define _SUB(val1, val2) Create_node (OP, SUB, val1, val2)
#define _MUL(val1, val2) Create_node (OP, MUL, val1, val2)
#define _DIV(val1, val2) Create_node (OP, DIV, val1, val2)
#define _COS(val)        Create_node (OP, COS, val, 0)
#define _SIN(val)        Create_node (OP, SIN, val, 0)
#define _POW(val1, val2) Create_node (OP, POW, val1, val2)

#define TYPE "lg"
#define SCALE 50
#define LENGTH 256

typedef double val_t;

struct node
{
    type_t type;
    double val;
    node* right;
    node* left;
};

struct diff 
{
ONEGIN* onegin;

};

#define DEBUG 1

#if  (DEBUG == 1) 
    #define DBG( ... ) __VA_ARGS__
#else 
    #define DBG( ... )
#endif

#define PRINT( ... )                                                             \
{                                                                                \
    int n  = fprintf (stderr, "%s: %d:", __FILE__ , __LINE__);                   \
        n += fprintf (stderr, "%*s", 20 + level_recursive*3, "");                \
        n += fprintf (stderr, __VA_ARGS__);                                      \
        n += fprintf (stderr, "%*s", 100 - n, "");                               \
             fprintf (stderr, "buffer: \'%.25s\'   addr:%p\n", buffer, buffer);  \
}                                       
#define MOVE_PTR buffer = Skip_space (buffer + 1);


FILE* Create_file (const char* name_of_file);
diff* Diff_init (int argc ,char* argv[]);
node* Read_equation (char* buffer, node* node_diff);
node* Create_node (type_t type, double data, node* node_left, node* node_right);
int Dump_tree (node* node_, node* new_node);
void Dump_graph_init (node* node_, node* new_node);
void Dump_graph_recursive (node* node_, size_t rank);
void Draw_tree (node* node_diff);
void Close_File (FILE* file);
char* Skip_space (const char* ptr);
node* Check_and_Create (char* buffer);
