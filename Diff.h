#include "..\Processor\Onegin_for_proc\Onegin_General.h"

#define struct union

enum type_t     {NUM = 1, VAR = 2, OP = 3};
enum operations {ADD = 1, SUB, MUL, DIV};

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

#define _NUM(val, ...) Create_node (NUM, val, (node*)NULL, (node*)NULL)
#define _X Create_node (VAR, 1, NULL, NULL)

FILE* Create_file (const char* name_of_file);
diff* Diff_init (int argc ,char* argv[]);
node* Create_node (type_t type, double data, node* node_left, node* node_right);
