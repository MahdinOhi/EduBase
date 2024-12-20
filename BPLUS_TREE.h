#ifndef BPLUS_TREE_H
#define BPLUS_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 3              ///< Maximum number of keys in a node
#define MIN_KEYS (MAX_KEYS / 2) ///< Minimum number of keys in a node

/**
 * @brief Struct to represent a student record.
 *
 * This struct defines a student record with bitfields for student_id, semester,
 * credits_completed, marital_status, and blood_group. Other fields store personal
 * and academic information.
 */
typedef struct Student
{
    unsigned int student_id : 16;       ///< 16 bits for student_id (ID range fits within 0-65535)
    unsigned int semester : 4;          ///< 4 bits for semester (max 16 semesters)
    unsigned int credits_completed : 8; ///< 8 bits for credits_completed (max 255 credits)
    unsigned int marital_status : 1;    ///< 1 bit for marital_status (0 for unmarried, 1 for married)
    unsigned int blood_group : 3;       ///< 3 bits for blood_group (supports 8 possible blood groups)

    // Non-bitfield variables
    char name[250];             ///< Name of the student
    char password[100];         ///< Password for the student
    char username[100];         ///< Username for the student
    char email[80];             ///< Email address of the student
    char phone_number[11];      ///< Phone number of the student
    char department[20];        ///< Department the student belongs to
    char date_of_birth[11];     ///< Date of birth in YYYY-MM-DD format
    char date_of_admission[11]; ///< Date of admission in YYYY-MM-DD format
    char advisor[50];           ///< Advisor's name
    char unique_id[20];         ///< Unique identifier for the student
    char address[100];          ///< Address of the student
    float CGPA;                 ///< Cumulative Grade Point Average (CGPA)
} Student;

/**
 * @brief Struct to represent a node in the B+ Tree.
 *
 * A B+ Tree node stores a set of keys and corresponding child pointers.
 */
typedef struct BPlusNode
{
    int num_keys;                             ///< Number of keys in the node
    int is_leaf;                              ///< Flag to indicate if the node is a leaf
    Student *keys[MAX_KEYS + 1];              ///< Array of keys (student records)
    struct BPlusNode *children[MAX_KEYS + 2]; ///< Array of child pointers
} BPlusNode;

/**
 * @brief Struct to represent the B+ Tree.
 *
 * The B+ Tree is represented by its root node.
 */
typedef struct BPlusTree
{
    BPlusNode *root; ///< Pointer to the root node of the tree
} BPlusTree;

/**
 * @brief Creates a new B+ Tree.
 *
 * This function initializes a new B+ Tree and sets its root to a leaf node.
 *
 * @return A pointer to the newly created B+ Tree
 */
BPlusTree *create_bplus_tree();

/**
 * @brief Inserts a student record into the B+ Tree.
 *
 * This function inserts a student record into the tree, performing necessary
 * splits to maintain the tree structure.
 *
 * @param tree Pointer to the B+ Tree
 * @param record Pointer to the student record to be inserted
 */
void insert(BPlusTree *tree, Student *record);

/**
 * @brief Searches for a student record in the B+ Tree.
 *
 * This function searches for a student record based on the student_id.
 *
 * @param tree Pointer to the B+ Tree
 * @param student_id The student ID to search for
 * @return Pointer to the student record if found, NULL otherwise
 */
Student *search(BPlusTree *tree, int student_id);

/**
 * @brief Deletes a student record from the B+ Tree.
 *
 * This function deletes a student record based on the student_id.
 *
 * @param tree Pointer to the B+ Tree
 * @param student_id The student ID to be deleted
 */
void delete(BPlusTree *tree, int student_id);

/**
 * @brief Frees the memory allocated for the B+ Tree.
 *
 * This function recursively frees the memory allocated for all nodes in the B+ Tree.
 *
 * @param node Pointer to the B+ Tree node to be freed
 */
void free_tree(BPlusNode *node);

/**
 * @brief Saves the B+ Tree to a file.
 *
 * This function recursively saves the nodes of the B+ Tree to a file.
 *
 * @param node Pointer to the B+ Tree node to be saved
 * @param file Pointer to the file where the tree will be saved
 */
void save_tree(BPlusNode *node, FILE *file);

/**
 * @brief Loads a B+ Tree from a file.
 *
 * This function loads the B+ Tree from a file and sets the root of the tree.
 *
 * @param tree Pointer to the B+ Tree to be loaded
 * @param file Pointer to the file where the tree is stored
 */
void load_tree(BPlusTree *tree, FILE *file);

#endif
