#include "core_lib.h"

void split_child(CoreNode *parent, int child_index){

    CoreNode *child = parent->children[child_index];
    CoreNode *new_child = create_node(child->is_leaf);

    int mid = child->num_keys / 2;

    //Move half of the keys to new child
    new_child->num_keys = child->num_keys - mid -1;

    for(int i = 0; i< new_child->num_keys; i++){

        new_child->keys[i] = child->keys[mid + 1 + i];
    }

    if(!child->is_leaf){

        for(int i = 0; i < new_child->num_keys; i++){
            
             new_child->children[i] = child->children[mid + 1 + i];
        }
    }

    child->num_keys = mid;

    // Insert the middle key into parent
    for(int i = parent->num_keys; i > child_index; i--){

        parent->children[i+1] = parent->keys[mid];
        parent->children[child_index + 1] = new_child;
        parent->num_keys++;
    }

    //Update next pointer for leaf nodes
    if(child->is_leaf){

        new_child->next = child-> next;
        child->next = new_child;
    }
}

void insert_non_full(CoreNode *node, int key){

    if(node->is_leaf){

        int i = node->num_keys - 1;

        while(i>= 0 && key < node->keys[i]){

            node->keys[i + 1] = node->keys[i];
            i--;
            
        }
        node->keys[i + 1] = key;
        node->num_keys++;

        }else {

            //Find the child recurse
            int i = node->num_keys - 1;

            while(i >= 0 && key < node->keys[i]){

                i--;
            }
            i++;

            //if ful, split the tree
            if(node->children[i]->num_keys == MAX_KEYS){

                split_child(node, i);

                if(key > node->keys[i]){

                    i++;
                }
            }

            insert_non_full(node->children[i], key);
        }
}



void insert_core_lib(Core *tree, int key){


CoreNode *root = tree->root;

//If the tree is not full, then split it
if(root->num_keys == MAX_KEYS){

    CoreNode *new_root = create_node(false);
    new_root->children[0] = root;
    split_child(new_root,0);
    tree->root = new_root;

    // Insert into the appropriate child
    if(key > new_root->keys[0]){

        insert_non_full(new_root->children[1], key);

    }else{

        insert_non_full(new_root->children[0], key);
    }

 }else {

    insert_non_full(root, key);
}
}
    