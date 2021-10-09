#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include "Header.h"


void addInfo(List_t* node, char* info) {
	if (!node) {
		printf("Error the pointer was NULL\n");
		exit(1);
	}
	node->word = (char*)malloc(strlen(info) + 1);
	node->len = strlen(info);
	if (!node->word) {
		printf("Error allocating memory\n");
		exit(1);
	}
	strcpy(node->word, info);
	
}

List_t* insertBeforeNode(List_t** node, List_t** nodeInList, List_t* head) {
	if (!node ) {
		printf("Error the pointer was NULL\n");
		exit(1);
	}
	if (!nodeInList) {
		printf("Error the pointer was NULL\n");
		exit(1);
	}
	if (!head) {
		printf("Error the pointer was NULL\n");
		exit(1);
	}
	List_t* tmp;
	tmp = head;
	if (*nodeInList == head) {
		(*node)->next = head;
		head = *(node);
		return head;
	}
	else {
		while (tmp->next != *(nodeInList)) {
			tmp = tmp->next;
		}
		(*node)->next = tmp->next;
		tmp->next = *node;
	}
	return head;
}
List_t* Sort_List(List_t* root, List_t* node) {
	if (!node) {
		printf("Error the pointer was NULL\n");
		exit(1);
	}
	if (!root) {
		printf("Error the pointer was NULL\n");
		exit(1);
	}
	List_t* head;
	head = root;

	while (1) {
		if (node->len < root->len) {
			head = insertBeforeNode(&node, &root, head);
			return head;
		}
		else {
			if (node->len == root->len) {
				while (1) {	
					if (node->len < root->len) {
						head = insertBeforeNode(&node, &root, head);
						return head;
					}
					if (strcmp(node->word, root->word) == -1) {
						head = insertBeforeNode(&node, &root, head);
						return head;
					}
					else {
						if (root->next == NULL) {
							root->next = node;
							return head;
						}
						root = root->next;
					}
				}
			}
			if (root->next == NULL) {
				root->next = node;
				return head;
			}
			root = root->next;
		}
	}
}

List_t* newNode() {
	List_t* nod = (List_t*)malloc(sizeof(List_t));
	if (!nod) {
		printf("Error allocating memory\n");
		exit(1);
	}
	nod->next = NULL;
	return nod;
}

void printList(List_t* root, int N) {
	while (root != NULL) {
		if (root->len >= N) {
			printf("%s ", root->word);
		}
		root = root->next;
	}
}

void printList_oneLen(List_t* root, int N) {
	while (root != NULL) {
		if (root->len == N) {
			printf("%s ", root->word);
		}
		root = root->next;
	}
}

int main(void) {
	char buffer[SIZE];
	setlocale(LC_ALL, "Rus");
	List_t* root = (List_t*)malloc(sizeof(List_t));
	if (!root) {
		printf("Error allocating memory\n");
		exit(1);
	}
	root->next = NULL;
	List_t* newNod;
	int s, N, n;
	FILE* f;
	if ((f = fopen("wordlist.txt", "rb")) == NULL)
		printf("The file was not opened\n");
	else {
		s = fscanf(f, "%s", buffer);
		addInfo(root, buffer);
		s = fscanf(f, "%s", buffer);
		while (s != EOF) {
			newNod = newNode();
			addInfo(newNod, buffer);
			root = Sort_List(root, newNod);
			s = fscanf(f, "%s", buffer);
		}
		printf("Введите минимальное число символов в слове: ");
		scanf("%d", &N);
		printList(root, N);
		printf("\nСлова с какой длинной Вы хотите найти? ");
		scanf("%d", &n);
		printList_oneLen(root, n);
	}
	return 0;
}