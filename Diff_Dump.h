#pragma once

#include "Diff_Common.h"

#define PRINT( ... )                                                             \
{                                                                                \
    int n  = fprintf (stderr, "%s: %d:", __FILE__ , __LINE__);                   \
        n += fprintf (stderr, "%*s", 20 + level_recursive*3, "");                \
        n += fprintf (stderr, __VA_ARGS__);                                      \
        n += fprintf (stderr, "%*s", 100 - n, "");                               \
             fprintf (stderr, "buffer: \'%.25s\'   addr:%p\n", buffer, buffer);  \
}  

#define MOVE_PTR buffer = Skip_space (buffer + 1);


//node* Read_equation (char* buffer, node* node_diff);
int Dump_tree (node* node_);
void Dump_graph_init (node* node_);
void Dump_graph_recursive (node* node_, size_t rank);
void Draw_tree (node* node_diff);
char* Skip_space (const char* ptr);