#ifndef BPLUS_TREE_H
#define BPLUS_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 3
#define MIN_KEYS (MAX_KEYS / 2)

typedef struct Student
{
    unsigned int student_id : 16;       // 16 bits for student_id (ID range fits within 0-65535)
    unsigned int semester : 4;          // 4 bits for semester (max 16 semesters)
    unsigned int credits_completed : 8; // 8 bits for credits_completed (max 255 credits)
    unsigned int marital_status : 1;    // 1 bit for marital_status (0 for unmarried, 1 for married)
    unsigned int blood_group : 3;       // 3 bits for blood_group (supports 8 possible blood groups)


    // Non-bitfield variables
    char name[250];            
    char password[100];       
    char username[100];       
    char email[80];            
    char phone_number[11];      
    char department[20];        
    char date_of_birth[11];     
    char date_of_admission[11];
    char advisor[50];           
    char unique_id[20];        
    char address[100];
    float CGPA;
} Student;

typedef struct BPlusNode
{
    int num_keys;
    int is_leaf;
    Student *keys[MAX_KEYS + 1];
    struct BPlusNode *children[MAX_KEYS + 2];
} BPlusNode;

typedef struct BPlusTree
{
    BPlusNode *root;
} BPlusTree;

BPlusTree *create_bplus_tree();
void insert(BPlusTree *tree, Student *record);
Student *search(BPlusTree *tree, int student_id);
void delete(BPlusTree *tree, int student_id);
void free_tree(BPlusNode *node);
void save_tree(BPlusNode *node, FILE *file);
void load_tree(BPlusTree *tree, FILE *file);

#endif