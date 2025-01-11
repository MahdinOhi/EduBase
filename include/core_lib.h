#ifndef CORE_LIB
#define CORE_LIB

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Maximum number of keys in a node
#define MAX_KEYS 3

/// Minimum number of keys in a node
#define MIN_KEYS (MAX_KEYS / 2)

/**
 * @struct CoreNode
 * @brief Represents a node in the B+ Tree.
 *
 * @var CoreNode::is_leaf
 * Indicates whether the node is a leaf.
 *
 * @var CoreNode::num_keys
 * Number of keys currently stored in the node.
 *
 * @var CoreNode::keys
 * Array of keys stored in the node.
 *
 * @var CoreNode::children
 * Array of pointers to the child nodes.
 *
 * @var CoreNode::next
 * Pointer to the next leaf node (used for linked list in leaf nodes).
 */
typedef struct CoreNode
{
    bool is_leaf;                            ///< Indicates if the node is a leaf.
    int num_keys;                            ///< Number of keys in the node.
    int keys[MAX_KEYS];                      ///< Keys stored in the node.
    struct CoreNode *children[MAX_KEYS + 1]; ///< Pointers to child nodes.
    struct CoreNode *next;                   ///< Pointer to the next leaf node.
} CoreNode;

/**
 * @struct Core
 * @brief Represents the B+ Tree structure.
 *
 * @var Core::root
 * Pointer to the root node of the B+ Tree.
 */
typedef struct
{
    CoreNode *root; ///< Root node of the B+ Tree.
} Core;

/**
 * @brief Creates and initializes a new B+ Tree.
 *
 * @return Pointer to the newly created B+ Tree.
 */
Core *create_core_lib(void);

/**
 * @brief Inserts a key into the B+ Tree.
 *
 * @param tree Pointer to the B+ Tree.
 * @param key The key to be inserted.
 */
void insert_core_lib(Core *tree, int key);

/**
 * @brief Searches for a key in the B+ Tree.
 *
 * @param tree Pointer to the B+ Tree.
 * @param key The key to search for.
 * @return Pointer to the node containing the key, or NULL if not found.
 */
CoreNode *search_core_lib(Core *tree, int key);

/**
 * @brief Deletes a key from the B+ Tree.
 *
 * @param tree Pointer to the B+ Tree.
 * @param key The key to be deleted.
 */
void delete_core_lib(Core *tree, int key);

/**
 * @brief Prints the keys in the B+ Tree.
 *
 * @param tree Pointer to the B+ Tree.
 */
void print_core_lib(Core *tree);

#endif // CORE_LIB
