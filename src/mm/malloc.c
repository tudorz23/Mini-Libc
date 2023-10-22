// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void *malloc(size_t size)
{
	// size cannot be < 0 , since size_t is unsigned long.
	if (size == 0) {
		return NULL;
	}

	// Need a way to know if the initialization has been previously
	// done or not. Options were a global variable or a static one,
	// I chose a static one.
	static int init_done = 0;
	if (init_done == 0) {
		mem_list_init();
		init_done = 1;
	}

	void *allocated_memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (allocated_memory == MAP_FAILED) {
		return NULL;
	}

	int try = mem_list_add(allocated_memory, size);
	if (try == -1) {
		munmap(allocated_memory, size);
		return NULL;
	}

	return allocated_memory;
}

void *calloc(size_t nmemb, size_t size)
{
	void *allocated_memory = reallocarray(NULL, nmemb, size);
	if (allocated_memory == NULL) {
		return NULL;
	}

	memset(allocated_memory, 0, nmemb * size);

	return allocated_memory;
}

void free(void *ptr)
{
	if (ptr == NULL) {
		return;
	}

	struct mem_list *item = mem_list_find(ptr);
	if (item == NULL) {
		return;
	}

	munmap(item->start, item->len);
	mem_list_del(ptr);
}

void *realloc(void *ptr, size_t size)
{
	if (ptr == NULL && size == 0) {
		return NULL;
	}

	// If ptr is NULL, it behaves like malloc(size).
	if (ptr == NULL) {
		return malloc(size);
	}

	// If size is 0, it behaves like free(ptr).
	if (size == 0) {
		free(ptr);
		return NULL;
	}

	struct mem_list *item = mem_list_find(ptr);
	if (item == NULL) {
		return NULL;
	}

	void *new_allocated_memory = mremap(item->start, item->len, size, MREMAP_MAYMOVE);
	if (new_allocated_memory == MAP_FAILED) {
		return NULL;
	}

	item->start = new_allocated_memory;
	item->len = size;

	return new_allocated_memory;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	// Check for overflow.
	size_t new_size = nmemb * size;
	if (nmemb != 0 && size != 0 && new_size < size) {
		errno = ENOMEM;
		return NULL;
	}

	return realloc(ptr, new_size);
}
