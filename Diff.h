#include "..\Processor\Onegin_for_proc\Onegin_General.h" 

enum type_t     {NUM = 1, VAR, OP};
enum operations {ADD = '+', SUB = '-', MUL = '*', DIV = '/'};

#define _NUM(val) Create_node (NUM, val, NULL, NULL)
#define _X Create_node (VAR, 'x', NULL, NULL)
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

FILE* Create_file (const char* name_of_file);
diff* Diff_init (int argc ,char* argv[]);
node* Read_equation (char* buffer);
node* Create_node (type_t type, double data, node* node_left, node* node_right);
int Dump_tree (node* node_, node* new_node);
void Dump_graph_init (node* node_, node* new_node);
void Dump_graph_recursive (node* node_, size_t rank);
void Draw_tree (node* node_diff);
void Close_File (FILE* file);
char* Skip_space (const char* ptr);
