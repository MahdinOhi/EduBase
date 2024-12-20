#include "bplus_tree.h"

// Function prototypes
static BPlusNode *create_node(int is_leaf);
static void split_child(BPlusNode *parent, int index);
static void insert_non_full(BPlusNode *node, Student *record);
static void delete_key(BPlusNode *node, int student_id);
static void merge_nodes(BPlusNode *parent, int index);
static void borrow_from_prev(BPlusNode *parent, int index);
static void borrow_from_next(BPlusNode *parent, int index);
static void fill(BPlusNode *parent, int index);
static void save_node(BPlusNode *node, FILE *file);
static BPlusNode *load_node(FILE *file);

// ------------------------------------------------------------------------------

BPlusTree *create_bplus_tree()
{
    BPlusTree *tree = (BPlusTree *)malloc(sizeof(BPlusTree));
    tree->root = create_node(1);
    return tree;
}

static BPlusNode *create_node(int is_leaf)
{
    BPlusNode *node = (BPlusNode *)malloc(sizeof(BPlusNode));
    node->num_keys = 0;
    node->is_leaf = is_leaf;
    for (int i = 0; i < MAX_KEYS + 2; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

void insert(BPlusTree *tree, Student *record)
{
    BPlusNode *root = tree->root;
    if (root->num_keys == MAX_KEYS)
    {
        BPlusNode *new_root = create_node(0);
        new_root->children[0] = root;
        split_child(new_root, 0);
        tree->root = new_root;
        insert_non_full(new_root, record);
    }
    else
    {
        insert_non_full(root, record);
    }
}

static void insert_non_full(BPlusNode *node, Student *record)
{
    int i = node->num_keys - 1;
    if (node->is_leaf)
    {
        while (i >= 0 && node->keys[i]->student_id > record->student_id)
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = record;
        node->num_keys++;
    }
    else
    {
        while (i >= 0 && node->keys[i]->student_id > record->student_id)
        {
            i--;
        }
        i++;
        if (node->children[i]->num_keys == MAX_KEYS)
        {
            split_child(node, i);
            if (node->keys[i]->student_id < record->student_id)
            {
                i++;
            }
        }
        insert_non_full(node->children[i], record);
    }
}

static void split_child(BPlusNode *parent, int index)
{
    BPlusNode *full_child = parent->children[index];
    BPlusNode *new_child = create_node(full_child->is_leaf);
    new_child->num_keys = MIN_KEYS;

    for (int j = 0; j < MIN_KEYS; j++)
    {
        new_child->keys[j] = full_child->keys[j + MIN_KEYS + 1];
    }
    if (!full_child->is_leaf)
    {
        for (int j = 0; j < MIN_KEYS + 1; j++)
        {
            new_child->children[j] = full_child->children[j + MIN_KEYS + 1];
        }
    }
    full_child->num_keys = MIN_KEYS;

    for (int j = parent->num_keys; j > index; j--)
    {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[index + 1] = new_child;

    for (int j = parent->num_keys - 1; j >= index; j--)
    {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[index] = full_child->keys[MIN_KEYS];
    parent->num_keys++;
}

Student *search(BPlusTree *tree, int student_id)
{
    BPlusNode *current = tree->root;
    while (current != NULL)
    {
        int i = 0;
        while (i < current->num_keys && student_id > current->keys[i]->student_id)
        {
            i++;
        }
        if (i < current->num_keys && student_id == current->keys[i]->student_id)
        {
            return current->keys[i];
        }
        if (current->is_leaf)
        {
            return NULL;
        }
        current = current->children[i];
    }
    return NULL;
}

void delete(BPlusTree *tree, int student_id)
{
    delete_key(tree->root, student_id);
    if (tree->root->num_keys == 0)
    {
        BPlusNode *old_root = tree->root;
        if (old_root->is_leaf)
        {
            free(old_root);
            tree->root = NULL;
        }
        else
        {
            tree->root = old_root->children[0];
            free(old_root);
        }
    }
}

static void delete_key(BPlusNode *node, int student_id)
{
    int idx = 0;
    while (idx < node->num_keys && node->keys[idx]->student_id < student_id)
    {
        idx++;
    }
    if (idx < node->num_keys && node->keys[idx]->student_id == student_id)
    {
        if (node->is_leaf)
        {
            for (int j = idx + 1; j < node->num_keys; j++)
            {
                node->keys[j - 1] = node->keys[j];
            }
            node->num_keys--;
        }
        else
        {
            //! Implementation omitted
        }
    }
    else
    {
        if (node->is_leaf)
        {
            return; // Key not found
        }
        int should_merge = (idx == node->num_keys) ? 1 : 0;
        delete_key(node->children[idx], student_id);
        if (should_merge)
        {
            //! Implementation omitted
        }
    }
}

void free_tree(BPlusNode *node)
{
    if (node != NULL)
    {
        for (int i = 0; i <= node->num_keys; i++)
        {
            free_tree(node->children[i]);
        }
        free(node);
    }
}

void save_tree(BPlusNode *node, FILE *file)
{
    if (node != NULL)
    {
        fwrite(&node->num_keys, sizeof(int), 1, file);
        fwrite(&node->is_leaf, sizeof(int), 1, file);
        for (int i = 0; i < node->num_keys; i++)
        {
            fwrite(node->keys[i], sizeof(Student), 1, file);
        }
        for (int i = 0; i <= node->num_keys; i++)
        {
            save_tree(node->children[i], file);
        }
    }
}

void load_tree(BPlusTree *tree, FILE *file)
{
    tree->root = load_node(file);
}

static BPlusNode *load_node(FILE *file)
{
    BPlusNode *node = (BPlusNode *)malloc(sizeof(BPlusNode));
    fread(&node->num_keys, sizeof(int), 1, file);
    fread(&node->is_leaf, sizeof(int), 1, file);
    for (int i = 0; i < node->num_keys; i++)
    {
        node->keys[i] = (Student *)malloc(sizeof(Student));
        fread(node->keys[i], sizeof(Student), 1, file);
    }
    for (int i = 0; i <= node->num_keys; i++)
    {
        node->children[i] = load_node(file);
    }
    return node;
}
