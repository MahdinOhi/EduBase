#include <stdio.h>
#include <stdbool.h>
#include "core_lib.h"

// Function to search for a key in the B+ tree
CoreNode *search_core_lib(CoreNode *tree, int key)
{
    if (tree == NULL)
    {
        return NULL;
    }

    int i = 0;

    // Traverse keys to find the relevant child or match
    while (i < tree->num_keys && key > tree->keys[i])
    {
        i++;
    }

    // Check if the key matches in a leaf node
    if (i < tree->num_keys && key == tree->keys[i] && tree->is_leaf)
    {
        return tree;
    }

    // If it's a leaf node and the key isn't found
    if (tree->is_leaf)
    {
        return NULL;
    }

    // Recursively search in the appropriate subtree
    return search_core_lib(tree->children[i], key);
}