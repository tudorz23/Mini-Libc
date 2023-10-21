// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	long syscall_result = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);

	if (syscall_result < 0) {
		errno = -syscall_result;
		return MAP_FAILED;
	}

	return (void *)syscall_result;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	long syscall_result = syscall(__NR_mremap, old_address, old_size, new_size, flags);

	if (syscall_result < 0) {
		errno = -syscall_result;
		return MAP_FAILED;
	}

	return (void *)syscall_result;
}

int munmap(void *addr, size_t length)
{
	long syscall_result = syscall(__NR_munmap, addr, length);

	if (syscall_result < 0) {
		errno = -syscall_result;
		return -1;
	}

	return 0;
}
