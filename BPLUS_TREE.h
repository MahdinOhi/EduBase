#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Constants
#define MAX_KEYS 3              // Maximum keys per node (order - 1). Modify as needed.
#define MIN_KEYS (MAX_KEYS / 2) // Minimum keys in a non-root node.

// Forward declaration for recursive structures
typedef struct BPlusTreeNode BPlusTreeNode;

// Node structure
struct BPlusTreeNode
{
    int keys[MAX_KEYS];                    // Keys stored in the node
    BPlusTreeNode *children[MAX_KEYS + 1]; // Pointers to child nodes
    bool is_leaf;                          // Flag for leaf node
    int num_keys;                          // Current number of keys
    BPlusTreeNode *next;                   // Pointer to the next leaf node (for leaf nodes)
};

typedef struct
{
    BPlusTreeNode *root; // Pointer to the root of the tree
    int order;           // Order of the B+ tree
} BPlusTree;

// Function prototypes
BPlusTree *create_b_plus_tree(int order);
void destroy_b_plus_tree(BPlusTree *tree);
void insert(BPlusTree *tree, int key);
void delete_key(BPlusTree *tree, int key);
bool search(BPlusTree *tree, int key);
void print_tree(BPlusTree *tree);

// Internal functions (not exposed to the user)
BPlusTreeNode *create_node(bool is_leaf);
void split_child(BPlusTreeNode *parent, int index, BPlusTreeNode *child);
void insert_non_full(BPlusTreeNode *node, int key);
void delete_from_node(BPlusTreeNode *node, int key);
void merge_nodes(BPlusTreeNode *parent, int index);
void borrow_from_sibling(BPlusTreeNode *parent, int index);
void print_node(BPlusTreeNode *node, int level);

// Function Implementations

BPlusTree *create_b_plus_tree(int order)
{
    BPlusTree *tree = (BPlusTree *)malloc(sizeof(BPlusTree));
    tree->order = order;
    tree->root = create_node(true);
    return tree;
}

void destroy_b_plus_tree(BPlusTree *tree)
{
    if (tree)
    {
        // Recursive deletion of nodes
        free(tree);
    }
}

BPlusTreeNode *create_node(bool is_leaf)
{
    BPlusTreeNode *node = (BPlusTreeNode *)malloc(sizeof(BPlusTreeNode));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->next = NULL;
    for (int i = 0; i <= MAX_KEYS; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

void split_child(BPlusTreeNode *parent, int index, BPlusTreeNode *child)
{
    BPlusTreeNode *new_node = create_node(child->is_leaf);
    new_node->num_keys = MIN_KEYS;

    for (int i = 0; i < MIN_KEYS; i++)
    {
        new_node->keys[i] = child->keys[i + MIN_KEYS + 1];
    }

    if (!child->is_leaf)
    {
        for (int i = 0; i <= MIN_KEYS; i++)
        {
            new_node->children[i] = child->children[i + MIN_KEYS + 1];
        }
    }

    child->num_keys = MIN_KEYS;

    for (int i = parent->num_keys; i > index; i--)
    {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = new_node;

    for (int i = parent->num_keys - 1; i >= index; i--)
    {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = child->keys[MIN_KEYS];
    parent->num_keys++;
}

void insert_non_full(BPlusTreeNode *node, int key)
{
    int i = node->num_keys - 1;

    if (node->is_leaf)
    {
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    }
    else
    {
        while (i >= 0 && key < node->keys[i])
        {
            i--;
        }
        i++;

        if (node->children[i]->num_keys == MAX_KEYS)
        {
            split_child(node, i, node->children[i]);

            if (key > node->keys[i])
            {
                i++;
            }
        }
        insert_non_full(node->children[i], key);
    }
}

void insert(BPlusTree *tree, int key)
{
    BPlusTreeNode *root = tree->root;

    if (root->num_keys == MAX_KEYS)
    {
        BPlusTreeNode *new_root = create_node(false);
        new_root->children[0] = root;
        split_child(new_root, 0, root);
        tree->root = new_root;
        insert_non_full(new_root, key);
    }
    else
    {
        insert_non_full(root, key);
    }
}

bool search(BPlusTree *tree, int key)
{
    BPlusTreeNode *current = tree->root;

    while (current)
    {
        int i = 0;
        while (i < current->num_keys && key > current->keys[i])
        {
            i++;
        }

        if (i < current->num_keys && key == current->keys[i])
        {
            return true;
        }

        if (current->is_leaf)
        {
            return false;
        }

        current = current->children[i];
    }

    return false;
}

void delete_key(BPlusTree *tree, int key)
{
    // Placeholder for deletion logic
    printf("Delete functionality is not implemented yet.\n");
}

void print_node(BPlusTreeNode *node, int level)
{
    if (node)
    {
        printf("Level %d [", level);
        for (int i = 0; i < node->num_keys; i++)
        {
            printf("%d ", node->keys[i]);
        }
        printf("]\n");

        if (!node->is_leaf)
        {
            for (int i = 0; i <= node->num_keys; i++)
            {
                print_node(node->children[i], level + 1);
            }
        }
    }
}

void print_tree(BPlusTree *tree)
{
    if (tree->root)
    {
        print_node(tree->root, 0);
    }
}

#endif
