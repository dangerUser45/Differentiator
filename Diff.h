#pragma once

#include "Diff_Common.h"

#define _NUM(val) Create_node (NUM, val, NULL, NULL)
#define _X Create_node (VAR, 'x', NULL, NULL)

#define _ADD(val1, val2) Create_node (OP, ADD, val1, val2)
#define _SUB(val1, val2) Create_node (OP, SUB, val1, val2)
#define _MUL(val1, val2) Create_node (OP, MUL, val1, val2)
#define _DIV(val1, val2) Create_node (OP, DIV, val1, val2)
#define _COS(val)        Create_node (OP, COS, val, 0)
#define _SIN(val)        Create_node (OP, SIN, val, 0)
#define _POW(val1, val2) Create_node (OP, POW, val1, val2)
#define _LN(val)         Create_node (OP, LN,  val, 0)
#define _LOG(val1, val2) Create_node (OP, LOG, val1, val2)
#define _EXP(val)        Create_node (OP, EXP, val, 0)
#define _TAN(val)        Create_node (OP, TAN, val, 0)

#define _dl Diff (Node -> left)
#define _dr Diff (Node -> right)
#define _cl Create_copy_node (Node -> left)
#define _cr Create_copy_node (Node -> right)

node* Create_node (type_t type, double data, node* node_left, node* node_right);
node* Check_and_Create (char* buffer);
node* Diff (node* Node);
node* Create_copy_node (node* Node);
void Const_Folding (node* Node);
