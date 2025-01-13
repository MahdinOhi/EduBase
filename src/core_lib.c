#include "core_lib.h"

void delete_key_from_node(CoreNode *node, int key)
{
    int i;
    for (i = 0; i < node->num_keys && node->keys[i] != key; i++)
        ;
    if (i < node->num_keys)
    {
        for (int j = i; j < node->num_keys - 1; j++)
        {
            node->keys[j] = node->keys[j + 1];
        }
        node->num_keys--;
    }
}