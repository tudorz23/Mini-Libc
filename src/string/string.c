// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	char *dest_start = destination;

	while (*source != '\0') {
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';

	return dest_start;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	if (len == 0) {
		return destination;
	}

	char *dest_start = destination;

	size_t byte_cnt = 0;

	while (*source != '\0') {
		*destination = *source;
		destination++;
		source++;

		byte_cnt++;
		if (byte_cnt == len) {
			return dest_start;
		}
	}

	while (byte_cnt < len) {
		*destination = '\0';
		destination++;
		byte_cnt++;
	}

	return dest_start;
}

char *strcat(char *destination, const char *source)
{
	while (*destination != '\0') {
		destination++;
	}

	while (*source != '\0') {
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	if (len == 0) {
		return destination;
	}

	while (*destination != '\0') {
		destination++;
	}

	size_t byte_cnt = 0;

	while (*source != 0 && byte_cnt < len) {
		*destination = *source;
		destination++;
		source++;
		byte_cnt++;
	}

	*destination = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0') {
		int char_cmp = (int)*str1 - (int)*str2;
		if (char_cmp != 0) {
			return char_cmp;
		}

		str1++;
		str2++;
	}

	// Return the compare result of the latest characters.
	// Works if any of them is NULL too.
	return ((int)*str1 - (int)*str2);
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	if (len == 0) {
		return 0;
	}

	size_t byte_cnt = 0;

	while (*str1 != '\0' && *str2 != '\0') {
		int char_cmp = (int)*str1 - (int)*str2;
		if (char_cmp != 0) {
			return char_cmp;
		}

		byte_cnt++;
		if (byte_cnt == len) {
			return char_cmp;
		}

		str1++;
		str2++;
	}

	return ((int)*str1 - (int)*str2);
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	char c_char = (char)c;

	while (*str != '\0') {
		if (*str == c_char) {
			return (char *)str;
		}

		str++;
	}

	if (c_char == '\0') {
		return (char *)str;
	}

	return NULL;
}

char *strrchr(const char *str, int c)
{
	char c_char = (char)c;

	// Length of the string.
	size_t len = 0;

	// Used to reach the end of str.
	char *iterator = (char *)str;

	while (*iterator != '\0') {
		iterator++;
		len++;
	}
	
	// Check if '\0' is wanted.
	if (c_char == '\0') {
		return iterator;
	}

	// Ignore '\0'.
	iterator--;

	while (len > 0) {
		if (*iterator == c_char) {
			return iterator;
		}

		iterator--;
		len--;
	}

	return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	// "If needle is an empty string, return haystack." (GNU libc manual)
	if (*needle == '\0') {
		return (char *)haystack;
	}

	// Used to reset the needle.
	char *needle_start = (char *)needle;
	char *matching_start_point = NULL;

	while (*haystack != '\0') {
		// If end of needle is reached, a match is found.
		if (*needle == '\0') {
			return matching_start_point;
		}

		if (*haystack != *needle) {
			if (matching_start_point != NULL) {
				needle = needle_start;
				matching_start_point = NULL;
			}
			
			haystack++;
			continue;
		}

		// Surely, *haystack == *needle.
		if (matching_start_point == NULL) {
			matching_start_point = (char *)haystack;
		}

		haystack++;
		needle++;
	}

	if (*needle != '\0') {
		return NULL;
	}

	return matching_start_point;
}

char *strrstr(const char *haystack, const char *needle)
{
	if (*needle == '\0') {
		return (char *)haystack;
	}

	char *needle_start = (char *)needle;
	char *last_matching_start_point = NULL;
	char *curr_matching_start_point = NULL;

	while (*haystack != '\0') {
		// If a new match is found, update last_matching_start_point and reset
		// the needle and the curr_matching_start_point.
		if (*needle == '\0') {
			last_matching_start_point = curr_matching_start_point;
			curr_matching_start_point = NULL;
			needle = needle_start;
			continue;
		}

		if (*haystack != *needle) {
			if (curr_matching_start_point != NULL) {
				needle = needle_start;
				curr_matching_start_point = NULL;
			}

			haystack++;
			continue;
		}

		// Surely, *haystack == *needle.
		if (curr_matching_start_point == NULL) {
			curr_matching_start_point = (char *)haystack;
		}

		haystack++;
		needle++;
	}

	if (*needle == '\0') {
		last_matching_start_point = curr_matching_start_point;
	}

	return last_matching_start_point;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	return -1;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	return source;
}
