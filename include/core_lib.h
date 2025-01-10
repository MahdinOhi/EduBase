#ifndef core_lib
#define core_lib

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 3
#define MIN_KEYS (MAX_KEYS / 2)

typedef struct CoreNode
{
    bool is_leaf;
    int num_keys;
    int keys[MAX_KEYS];
    struct CoreNode *children[MAX_KEYS + 1];
    struct CoreNode *next;
} CoreNode;

// B+ Tree structure
typedef struct
{
    CoreNode *root;
} Core;

Core *create_bplus_tree(void);
void insert_bplus_tree(Core *tree, int key);
CoreNode *search_bplus_tree(Core *tree, int key);
void delete_bplus_tree(Core *tree, int key);
void print_bplus_tree(Core *tree);

#endif