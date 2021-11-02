#include <stdio.h>
#include "memallocator.h"
#define Yes 1
#define No 0
#define MEM_PTR(block) (void*)((descriptor*)block + 1)
#define descriptor_PTR(mem_ptr) (descriptor*)mem_ptr - 1


struct descriptor {
	struct descriptor* next;
	struct descriptor* prev;
	int block_size;
	char is_free;
};

typedef struct descriptor header;

header* head = NULL;
int full_size = 0;


int meminit(void* pMemory, int size) {
	if (head != NULL || size < sizeof(descriptor) || pMemory == NULL) {
		return 1;
	}


	head = (descriptor*)pMemory;

	head->block_size = size - sizeof(descriptor);
	head->next = NULL;
	head->prev = NULL;
	head->is_free = Yes;

	full_size = size;

	return 0;
}



char create_block(descriptor* block, int size) {
	if (head == NULL) {
		return No;
	}
	if (block == NULL) {
		return No;
	}
	if (block->is_free == No) {
		return No;
	}

	if (block->block_size - size > sizeof(descriptor)) {
		descriptor* new_block = (descriptor*)((char*)MEM_PTR(block) + size);

		new_block->block_size = block->block_size - size - sizeof(descriptor);
		new_block->is_free = Yes;
		new_block->next = block->next;
		new_block->prev = block;

		if (block->next != NULL)
			block->next->prev = new_block;

		block->next = new_block;
	}

	block->block_size = size;
	block->is_free = No;

	return Yes;
}



void memdone() {
	int size = 0;

	if (head == NULL)
		return;

	descriptor* block = head;

	while (block != NULL) {
		if (block->is_free == Yes)
			size += block->block_size;

		block = block->next;
	}

	size += sizeof(descriptor);

	if (size < full_size)
		fprintf(stderr, "Memory leak: \n\texpected %d\n\tcurrent %d\n", full_size, size);
}

descriptor* find_first_fit(int size) {
	if (head == NULL)
		return NULL;

	descriptor* block_ptr = head;

	while (block_ptr != NULL) {
		if (block_ptr->is_free == Yes)
			if (block_ptr->block_size >= size)
				break;

		block_ptr = block_ptr->next;
	}

	return block_ptr;
}

void* memalloc(int size) {
	if (head == NULL)
		return NULL;

	descriptor* found_block;
	found_block = find_first_fit(size);

	if (found_block == NULL)
		return NULL;

	if (!create_block(found_block, size))
		return NULL;

	return MEM_PTR(found_block);
}



void memfree(void* p) {
	if (p == NULL)
		return;

	descriptor* free_block = descriptor_PTR(p);

	if (free_block == NULL || free_block->is_free == Yes)
		return;

	descriptor* buffer_block = free_block;
	buffer_block->is_free = Yes;

	if (free_block->prev != NULL) {
		if (free_block->prev->is_free == Yes) {
			int new_size = 0;

			if (free_block->next != NULL)
				new_size = (char*)free_block->next - (char*)(free_block->prev + 1);
			else
				new_size = (char*)(head + 1) + full_size - (char*)(free_block->prev + 1);

			free_block->prev->next = free_block->next;


			if (free_block->next != NULL)
				free_block->next->prev = free_block->prev;

			free_block->prev->block_size = new_size;
			buffer_block = free_block->prev;
		}
	}

	if (buffer_block->next != NULL) {
		if (buffer_block->next->is_free == Yes) {
			int new_size = 0;

			if (buffer_block->next->next != NULL)
				new_size = (char*)buffer_block->next->next - (char*)(buffer_block + 1);
			else
				new_size = (char*)(head + 1) + full_size - (char*)(buffer_block + 1);

			if (buffer_block->next->next != NULL)
				buffer_block->next->next->prev = buffer_block;

			buffer_block->next = buffer_block->next->next;
			buffer_block->block_size = new_size;
		}
	}

	if (buffer_block->next != NULL) {
		if (((char*)(buffer_block + 1) + buffer_block->block_size) != (char*)buffer_block->next) {
			void* leaked_ptr = (void*)((char*)(buffer_block + 1) + buffer_block->block_size);
			int size = (char*)buffer_block->next - (char*)leaked_ptr;

			buffer_block->block_size += size;
		}
	}
	else
		if (((char*)head + full_size) != ((char*)(buffer_block + 1) + buffer_block->block_size)) {
			void* leaked_ptr = (void*)((char*)(buffer_block + 1) + buffer_block->block_size);
			int size = (char*)head + full_size - (char*)leaked_ptr;

			buffer_block->block_size += size;
		}
}

int memgetminimumsize() {
	return sizeof(descriptor);
}

int memgetblocksize() {
	return sizeof(descriptor);
}