#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#pragma warning(disable : 4996)



tree_t* createNode(int value) {
    tree_t* nodeToAdd = (tree_t*)malloc(sizeof(tree_t));
    if (nodeToAdd) {
        nodeToAdd->one = NULL;
        nodeToAdd->two = NULL;
        nodeToAdd->three = NULL;
        nodeToAdd->four = NULL;
        nodeToAdd->parent = NULL;
        nodeToAdd->key[0] = value;
        nodeToAdd->size = 1;
        return nodeToAdd;
    }

    return NULL;
}

tree_t* createNode2(int value, tree_t* one, tree_t* two, tree_t* three, tree_t* four, tree_t* parent) {
    tree_t* nodeToAdd = (tree_t*)malloc(sizeof(tree_t));
    if (nodeToAdd) {
        nodeToAdd->one = one;
        nodeToAdd->two = two;
        nodeToAdd->three = three;
        nodeToAdd->four = four;
        nodeToAdd->parent = parent;
        nodeToAdd->key[0] = value;
        nodeToAdd->size = 1;
        return nodeToAdd;
    }

    return NULL;
}

char find(int value, int* key, int size) {
    for (int i = 0; i < size; ++i) {
        if (key[i] == value) {
            return 1;
        }
    }

    return 0;
}

void swap(int* x, int* y) {
    int r = (*x);
    (*x) = (*y);
    (*y) = r;
}

void sort2(int* x, int* y) {
    if (*x > *y) {
        swap(x, y);
    }
}

void sort3(int* x, int* y, int* z) {
    if (*x > *y) {
        swap(x, y);
    }

    if (*x > *z) {
        swap(x, z);
    }

    if (*y > *z) {
        swap(y, z);
    }
}

void sortKeys(int size, int* key) {
    if (size == 1) {
        return;
    }

    if (size == 2) {
        sort2(&key[0], &key[1]);
    }

    if (size == 3) {
        sort3(&key[0], &key[1], &key[2]);
    }
}

void addKeyToNode(int value, tree_t* treeNode) {
    if (treeNode == NULL) {
        return;
    }

    treeNode->key[treeNode->size] = value;
    treeNode->size++;
    sortKeys(treeNode->size, treeNode->key);
}

void removeKeyFromNode(int value, tree_t* treeNode) {
    if (treeNode == NULL) {
        return;
    }

    if (treeNode->size >= 1 && treeNode->key[0] == value) {
        treeNode->key[0] = treeNode->key[1];
        treeNode->key[1] = treeNode->key[2];
        treeNode->size--;
    }
    else if (treeNode->size == 2 && treeNode->key[1] == value) {
        treeNode->key[1] = treeNode->key[2];
        treeNode->size--;
    }
}

void become_Node2(int value, int* key, tree_t* treeNode, tree_t* one, tree_t* two) {
    key[0] = value;
    treeNode->one = one;
    treeNode->two = two;
    treeNode->three = NULL;
    treeNode->four = NULL;
    treeNode->parent = NULL;
    treeNode->size = 1;
}

char isLeaf(tree_t* tree) {
    if (tree == NULL) {
        return 0;
    }

    if ((tree->one == NULL) && (tree->two == NULL) && (tree->three == NULL)) {
        return 1;
    }

    return 0;
}

tree_t* addNode(tree_t* tree, int value) {
    if (tree == NULL) {
        return createNode(value);
    }

    if (search(tree, value)) {
        return split(tree);
    }

    if (isLeaf(tree)) {
        addKeyToNode(value, tree);
    }
    else if (value <= tree->key[0]) {
        addNode(tree->one, value);
    }
    else if ((tree->size == 1) || ((tree->size == 2) && value <= tree->key[1])) {
        addNode(tree->two, value);
    }
    else {
        addNode(tree->three, value);
    }

    return split(tree);
}

tree_t* findMin(tree_t* tree) {
    if (tree == NULL) {
        return tree;
    }

    if ((tree->one) == NULL) {
        return tree;
    }
    else {
        return findMin(tree->one);
    }
}

tree_t* removeNode(tree_t* tree, int value) {
    if (tree == NULL) {
        return NULL;
    }

    tree_t* item = search(tree, value);

    if (item == NULL) {
        return tree;
    }

    tree_t* min = NULL;
    if (item->key[0] == value) {
        min = findMin(item->two);
    }
    else {
        min = findMin(item->three);
    }

    if (min != NULL) {
        int* z = (value == item->key[0] ? &(item->key[0]) : &(item->key[1]));
        swap(z, &min->key[0]);
        item = min;
    }

    removeKeyFromNode(value, item);
    return fix(item);
}

tree_t* split(tree_t* item) {
    if (item == NULL) {
        return NULL;
    }

    if (item->size < 3) {
        return item;
    }

    tree_t* x = createNode2(item->key[0], item->one, item->two, NULL, NULL, item->parent);
    tree_t* y = createNode2(item->key[2], item->three, item->four, NULL, NULL, item->parent);

    if (x->one) {
        x->one->parent = x;
    }

    if (x->two) {
        x->two->parent = x;
    }

    if (y->one) {
        y->one->parent = y;
    }

    if (y->two) {
        y->two->parent = y;
    }

    if (item->parent != NULL) {
        addKeyToNode(item->key[1], item->parent);

        if (item->parent->one == item) {
            item->parent->one = NULL;
        }
        else if (item->parent->two == item) {
            item->parent->two = NULL;
        }
        else if (item->parent->three == item) {
            item->parent->three = NULL;
        }

        if (item->parent->one == NULL) {
            item->parent->four = item->parent->three;
            item->parent->three = item->parent->two;
            item->parent->two = y;
            item->parent->one = x;
        }
        else if (item->parent->two == NULL) {
            item->parent->four = item->parent->three;
            item->parent->three = y;
            item->parent->two = x;
        }
        else {
            item->parent->four = y;
            item->parent->three = x;
        }

        tree_t* tmp = item->parent;
        free(item);
        return tmp;
    }
    else {
        x->parent = item;
        y->parent = item;
        become_Node2(item->key[1], item->key, item, x, y);
        return item;
    }
}

tree_t* search(tree_t* tree, int value) {
    if (tree == NULL) {
        return NULL;
    }

    if (find(value, tree->key, tree->size)) {
        return tree;
    }
    else if (value < tree->key[0]) {
        return search(tree->one, value);
    }
    else if ((tree->size == 2) && (value < tree->key[1]) || (tree->size == 1)) {
        return search(tree->two, value);
    }
    else if (tree->size == 2) {
        return search(tree->three, value);
    }
}

tree_t* fix(tree_t* leaf) {
    if (leaf == NULL) {
        return NULL;
    }

    if (leaf->size == 0 && leaf->parent == NULL) {
        free(leaf);
        return NULL;
    }

    if (leaf->size != 0) {
        if (leaf->parent) {
            return fix(leaf->parent);
        }
        else {
            return leaf;
        }
    }

    tree_t* parent = leaf->parent;
    if (parent->one->size == 2 || parent->two->size == 2 || parent->size == 2) {
        leaf = redistribute(leaf);
    }
    else if (parent->size == 2 && parent->three->size == 2) {
        leaf = redistribute(leaf);
    }
    else {
        leaf = merge(leaf);
    }

    return fix(leaf);
}

tree_t* merge(tree_t* leaf) {
    if (leaf == NULL) {
        return NULL;
    }

    tree_t* parent = leaf->parent;

    if (parent->one == leaf) {
        addKeyToNode(parent->key[0], parent->two);
        parent->two->three = parent->two->two;
        parent->two->two = parent->two->one;

        if (leaf->one != NULL) {
            parent->two->one = leaf->one;
        }
        else if (leaf->two != NULL) {
            parent->two->one = leaf->two;
        }

        if (parent->two->one != NULL) {
            parent->two->one->parent = parent->two;
        }

        removeKeyFromNode(parent->key[0], parent);
        free(parent->one);
        parent->one = NULL;
    }
    else if (parent->two == leaf) {
        addKeyToNode(parent->key[0], parent->one);

        if (leaf->one != NULL) {
            parent->one->three = leaf->one;
        }
        else if (leaf->two != NULL) {
            parent->one->three = leaf->two;
        }

        if (parent->one->three != NULL) {
            parent->one->three->parent = parent->one;
        }

        removeKeyFromNode(parent->key[0], parent);
        free(parent->two);
        parent->two = NULL;
    }

    if (parent->parent == NULL) {
        tree_t* tmp = NULL;
        if (parent->one != NULL) {
            tmp = parent->one;
        }
        else {
            tmp = parent->two;
        }

        tmp->parent = NULL;
        free(parent);
        return tmp;
    }
    return parent;
}

tree_t* redistribute(tree_t* leaf) {
    if (leaf == NULL) {
        return NULL;
    }

    tree_t* parent = leaf->parent;
    tree_t* first = parent->one;
    tree_t* second = parent->two;
    tree_t* third = parent->three;


    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
        if (first == leaf) {
            parent->one = parent->two;
            parent->two = parent->three;
            parent->three = NULL;
            addKeyToNode(parent->key[0], parent->one);
            parent->one->three = parent->one->two;
            parent->one->two = parent->one->one;

            if (leaf->one != NULL) {
                parent->one->one = leaf->one;
            }
            else if (leaf->two != NULL) {
                parent->one->one = leaf->two;
            }

            if (parent->one->one != NULL) {
                parent->one->one->parent = parent->one;
            }

            removeKeyFromNode(parent->key[0], parent);
        }
        else if (second == leaf) {
            addKeyToNode(parent->key[0], first);
            removeKeyFromNode(parent->key[0], parent);
            if (leaf->one != NULL) {
                first->three = leaf->one;
            }
            else if (leaf->two != NULL) {
                first->three = leaf->two;
            }

            if (first->three != NULL) {
                first->three->parent = first;
            }

            parent->two = parent->three;
            parent->three = NULL;

            free(second);
        }
        else if (third == leaf) {
            addKeyToNode(parent->key[1], second);
            parent->three = NULL;
            removeKeyFromNode(parent->key[1], parent);
            if (leaf->one != NULL) {
                second->three = leaf->one;
            }
            else if (leaf->two != NULL) {
                second->three = leaf->two;
            }

            if (second->three != NULL) {
                second->three->parent = second;
            }

            free(third);
        }
    }
    else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
        if (third == leaf) {
            if (leaf->one != NULL) {
                leaf->two = leaf->one;
                leaf->one = NULL;
            }

            addKeyToNode(parent->key[1], leaf);
            if (second->size == 2) {
                parent->key[1] = second->key[1];
                removeKeyFromNode(second->key[1], second);
                leaf->one = second->three;
                second->three = NULL;

                if (leaf->one != NULL) {
                    leaf->one->parent = leaf;
                }

            }
            else if (first->size == 2) {
                parent->key[1] = second->key[0];
                leaf->one = second->two;
                second->two = second->one;
                if (leaf->one != NULL) {
                    leaf->one->parent = leaf;
                }

                second->key[0] = parent->key[0];
                parent->key[0] = first->key[1];
                removeKeyFromNode(first->key[1], first);
                second->one = first->three;
                if (second->one != NULL) {
                    second->one->parent = second;
                }

                first->three = NULL;
            }
        }
        else if (second == leaf) {
            if (third->size == 2) {
                if (leaf->one == NULL) {
                    leaf->one = leaf->two;
                    leaf->two = NULL;
                }

                addKeyToNode(parent->key[1], second);
                parent->key[1] = third->key[0];
                removeKeyFromNode(third->key[0], third);
                second->two = third->one;
                if (second->two != NULL) {
                    second->two->parent = second;
                }

                third->one = third->two;
                third->two = third->three;
                third->three = NULL;
            }
            else if (first->size == 2) {
                if (leaf->two == NULL) {
                    leaf->two = leaf->one;
                    leaf->one = NULL;
                }
                addKeyToNode(parent->key[0], second);
                parent->key[0] = first->key[1];
                removeKeyFromNode(first->key[1], first);
                second->one = first->three;
                if (second->one != NULL) {
                    second->one->parent = second;
                }

                first->three = NULL;
            }
        }
        else if (first == leaf) {
            if (leaf->one == NULL) {
                leaf->one = leaf->two;
                leaf->two = NULL;
            }
            addKeyToNode(parent->key[0], first);
            if (second->size == 2) {
                parent->key[0] = second->key[0];
                removeKeyFromNode(second->key[0], second);
                first->two = second->one;
                if (first->two != NULL) {
                    first->two->parent = first;
                }

                second->one = second->two;
                second->two = second->three;
                second->three = NULL;
            }
            else if (third->size == 2) {
                parent->key[0] = second->key[0];
                second->key[0] = parent->key[1];
                parent->key[1] = third->key[0];
                removeKeyFromNode(third->key[0], third);
                first->two = second->one;
                if (first->two != NULL) {
                    first->two->parent = first;
                }

                second->one = second->two;
                second->two = third->one;
                if (second->two != NULL) {
                    second->two->parent = second;
                }

                third->one = third->two;
                third->two = third->three;
                third->three = NULL;
            }
        }
    }
    else if (parent->size == 1) {
        addKeyToNode(parent->key[0], leaf);

        if (first == leaf && second->size == 2) {
            parent->key[0] = second->key[0];
            removeKeyFromNode(second->key[0], second);

            if (leaf->one == NULL) {
                leaf->one = leaf->two;
            }

            leaf->two = second->one;
            second->one = second->two;
            second->two = second->three;
            second->three = NULL;
            if (leaf->two != NULL) {
                leaf->two->parent = leaf;
            }
        }
        else if (second == leaf && first->size == 2) {
            parent->key[0] = first->key[1];
            removeKeyFromNode(first->key[1], first);

            if (leaf->two == NULL) {
                leaf->two = leaf->one;
            }

            leaf->one = first->three;
            first->three = NULL;

            if (leaf->one != NULL) {
                leaf->one->parent = leaf;
            }
        }
    }
    return parent;
}

void printTree(tree_t* tree) {
    if (tree == NULL) {
        return;
    }

    printTree(tree->one);
    for (int i = 0; i < tree->size; i++) {
        printf("%d ", tree->key[i]);
    }
    printTree(tree->two);
    printTree(tree->three);
}

void destroyTree(tree_t* tree) {
    if (tree == NULL) {
        return;
    }

    destroyTree(tree->one);
    destroyTree(tree->two);
    destroyTree(tree->three);
    free(tree);
}


int main(void) {
    char command;
    tree_t* t = NULL;
    int key = 0;
    while (scanf("%c", &command) >= 1) {
        if (command != 'p' && command != 'q') {
            scanf("%i", &key);
        }

        switch (command) {
        case 'a':
            t = addNode(t, key);
            break;
        case 'r':
            t = removeNode(t, key);
            break;
        case 'f':
            if (search(t, key)) {
                puts("yes");
            }
            else {
                puts("no");
            }

            break;
        case 'p':
            printTree(t);
            putchar('\n');
            break;
        case 'q':
            destroyTree(t);
            return 0;
        }
    }
}