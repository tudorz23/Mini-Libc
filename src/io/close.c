// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd)
{
	/* TODO: Implement close(). */
	long fd_result = syscall(__NR_close, fd);

	if (fd_result < 0) {
		errno = -fd_result;
		return -1;
	}

	return fd_result;
}
