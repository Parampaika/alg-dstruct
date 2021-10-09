#pragma once
#define SIZE 50
typedef struct List {
	char* word;
	int len;
	struct List* next;
}List_t;
void addInfo(List_t* node, char* info);
List_t* newNod;
List_t* insertBeforeNode(List_t** node, List_t** nodeInList, List_t* head);
List_t* Sort_List(List_t* root, List_t* node);
List_t* newNode();
void printList(List_t* root, int N);
void printList_oneLen(List_t* root, int N);
