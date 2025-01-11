#include "core_lib.h"

Core *create_core_lib(void)
{
    // Allocate memory for the B+ tree structure
    Core *tree = (Core *)malloc(sizeof(Core));
    if (!tree)
    {
        fprintf(stderr, "Memory allocation failed for Core.\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the root node
    tree->root = (CoreNode *)malloc(sizeof(CoreNode));
    if (!tree->root)
    {
        fprintf(stderr, "Memory allocation failed for CoreNode.\n");
        free(tree);
        exit(EXIT_FAILURE);
    }

    // Initialize the root node
    tree->root->is_leaf = true;
    tree->root->num_keys = 0;
    memset(tree->root->keys, 0, sizeof(tree->root->keys));
    memset(tree->root->children, 0, sizeof(tree->root->children));
    tree->root->next = NULL;

    return tree;
}
