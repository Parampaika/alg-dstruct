#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define NONE -1


typedef struct btree_tag {
	int key;
	struct btree_tag* left;
	struct btree_tag* right;
} btree_t;

typedef char boolean;

btree_t* InitBinTree(void) {
	btree_t* resTree = (btree_t*)malloc(sizeof(btree_t));
	if (resTree == NULL) {
		fprintf(stderr, "Allocation memory error!\n");
		return NULL;
	}

	resTree->left = NULL;
	resTree->right = NULL;
	resTree->key = NONE;

	return resTree;
}

void FormSubtrees(btree_t* parent, boolean isLeftSubTree, boolean isRightSubTree) {
	if (parent == NULL) {
		fprintf(stderr, "Null pointer!\n");
		return;
	}
	if (isLeftSubTree)
		parent->left = InitBinTree();
	if (isRightSubTree)
		parent->right = InitBinTree();
}

btree_t* FormExampleBinTree(void) {

	btree_t* root = InitBinTree();
	btree_t* curNode;


	curNode = root;
	FormSubtrees(curNode, TRUE, TRUE);


	curNode = root->left;
	FormSubtrees(curNode, TRUE, TRUE);
	curNode = root->right;
	FormSubtrees(curNode, FALSE, FALSE);

	
	curNode = root->left->left;
	FormSubtrees(curNode, TRUE, FALSE);
	curNode = root->left->right;
	FormSubtrees(curNode, FALSE, TRUE);


	curNode = root->left->left->left;
	FormSubtrees(curNode, TRUE, FALSE);
	curNode = root->left->right->right;
	FormSubtrees(curNode, FALSE, FALSE);

	return root;
}

void PrintTree(btree_t* nodePointer, int level) {
	if (nodePointer) {
		PrintTree(nodePointer->left, level + 1);
		for (int i = 0; i < level; i++)
			printf("    ");
		if (nodePointer->key == NONE)
			printf("*\n");
		else
			printf("%d\n", nodePointer->key);
		PrintTree(nodePointer->right, level + 1);
	}
}

void WriteMinHeightOfLeaves(btree_t* nodePointer) {
	if (nodePointer) {
		if (nodePointer->left != NULL && nodePointer->right != NULL) {
			WriteMinHeightOfLeaves(nodePointer->left);
			WriteMinHeightOfLeaves(nodePointer->right);
			if (nodePointer->left->key > NONE)
				nodePointer->key = nodePointer->left->key + 1;
			if (nodePointer->right->key > NONE)
				nodePointer->key = min(nodePointer->key, nodePointer->right->key + 1);
		}
		else {
			if (nodePointer->left != NULL) {
				WriteMinHeightOfLeaves(nodePointer->left);
				if (nodePointer->left->key > NONE) {
					nodePointer->key = nodePointer->left->key + 1;
					return;
				}
			}
			if (nodePointer->right != NULL) {
				WriteMinHeightOfLeaves(nodePointer->right);
				if (nodePointer->right->key > NONE) {
					nodePointer->key = nodePointer->right->key + 1;
					return;
				}
			}
			else
				nodePointer->key = 0;
		}
	}
}

void DestroyTree(btree_t* tree)
{
	if (tree != NULL)
	{
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		free(tree);
	}
}

int main(void) {
	btree_t* tree = FormExampleBinTree();
	PrintTree(tree, 0);

	printf("\n\n");

	WriteMinHeightOfLeaves(tree);
	PrintTree(tree, 0);

	DestroyTree(tree);
	return 0;
}