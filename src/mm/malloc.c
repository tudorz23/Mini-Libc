// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
	if (size <= 0) {
		return NULL;
	}

	mem_list_init();

	int try = mem_list_add(NULL, size);
	if (try == -1) {
		return NULL;
	}

	return &mem_list_head;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
	return NULL;
}

void free(void *ptr)
{
	/* TODO: Implement free(). */
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	return NULL;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
	return NULL;
}
