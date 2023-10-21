// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>

int ftruncate(int fd, off_t length)
{
	long syscall_result = syscall(__NR_ftruncate, fd, length);

	if (syscall_result < 0) {
		errno = -syscall_result;
		return -1;
	}

	return syscall_result;
}
