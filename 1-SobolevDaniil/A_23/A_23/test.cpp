#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gtest/gtest.h"
#include "A_23.c"

TEST(addInfo, adding_new_data_in_word) {
	List_t* nod = (List_t*)malloc(sizeof(List_t));
	if (!nod) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char buffer[] = { "Do" };
	addInfo(nod, buffer);
	ASSERT_STRCASEEQ(buffer, nod->word);
	free(nod);
}

TEST(insertBeforeNode, checking_that_node_2_is_inserted_in_front_of_the_head) {
	List_t* head_node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	if (!head_node_1 || !node_2) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char buf1[] = { "A" };
	char buf2[] = { "C" };
	head_node_1->word = buf1;
	node_2->word = buf2;
	head_node_1 = insertBeforeNode(&node_2, &head_node_1, head_node_1);
	ASSERT_STRCASEEQ(head_node_1->word, buf2);
	ASSERT_STRCASEEQ(head_node_1->next->word, buf1);
	free(head_node_1->next);
	free(head_node_1);
}

TEST(insertBeforeNode, checking_that_node_2_is_inserted_in_front_of_the_node_1_which_is_not_the_head) {
	List_t* head = (List_t*)malloc(sizeof(List_t));
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	if (!head || !node_1 || !node_2) {
		printf("Error allocating memory\n");
		exit(1);
	}
	head->next = node_1;
	char buf1[] = { "A" };
	char buf2[] = { "B" };
	char buf3[] = { "C" };
	head->word = buf2;
	node_1->word = buf1;
	node_2->word = buf3;
	head = insertBeforeNode(&node_2, &node_1, head);
	ASSERT_STRCASEEQ(head->next->word, buf3);
	ASSERT_STRCASEEQ(head->next->next->word, buf1);
	free(head->next);
	free(head);
}

TEST(Sort_List, checking_that_the_shortest_word_goes_to_the_beginning) {
	List_t* root = (List_t*)malloc(sizeof(List_t));
	List_t* node = (List_t*)malloc(sizeof(List_t));
	if (!root || !node) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char buf1[] = { "do" };
	char buf2[] = { "doo" };
	root->word = buf2;
	node->word = buf1;
	root = Sort_List(root, node);
	ASSERT_STRCASEEQ(root->word, buf1);
	ASSERT_STRCASEEQ(root->next->word, buf2 );
	free(root->next);
	free(root);
}

TEST(Sort_List, check_for_sorting_by_alphabet_with_equal_length) {
	List_t* root = (List_t*)malloc(sizeof(List_t));
	List_t* node = (List_t*)malloc(sizeof(List_t));

	if (!root || !node ) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char buf1[] = { "boo" };
	char buf2[] = { "doo" };

	root->word = buf2;
	node->word = buf1;
	root = Sort_List(root, node);
	ASSERT_STRCASEEQ(root->word, buf1);
	ASSERT_STRCASEEQ(root->next->word, buf2 );
	free(root->next);
	free(root);
}

TEST(Sort_List, check_for_sorting_by_length_node_more_then_root) {
	List_t* root = (List_t*)malloc(sizeof(List_t));
	List_t* node = (List_t*)malloc(sizeof(List_t));

	if (!root || !node) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char buf1[] = { "Aaa" };
	char buf2[] = { "D" };

	root->word = buf2;
	node->word = buf1;
	root = Sort_List(root, node);
	ASSERT_STRCASEEQ(root->word, buf1);
	ASSERT_STRCASEEQ(root->next->word, buf2);
	free(root->next);
	free(root);
}

TEST(Sort_List, check_for_sorting_by_length_and_alphabet) {
	List_t* root = (List_t*)malloc(sizeof(List_t));
	List_t* node = (List_t*)malloc(sizeof(List_t));
	List_t* node1 = (List_t*)malloc(sizeof(List_t));
	if (!root || !node || !node1) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char buf1[] = { "Aaa" };
	char buf2[] = { "ddddd" };
	char buf3[] = { "ccc" };


	root->word = buf1;
	root->next = node;
	node->word = buf2;
	node1->word = buf3;
	
	root = Sort_List(root, node1);
	ASSERT_STRCASEEQ(root->word, buf1);
	ASSERT_STRCASEEQ(root->next->word, buf3);
	ASSERT_STRCASEEQ(root->next->next->word, buf2);
	free(root->next);
	free(root);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
