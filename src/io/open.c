// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	/* TODO: Implement open system call. */
	mode_t mode = 0;

	if (flags & O_CREAT) {
		va_list arg_list;
		va_start(arg_list, flags);
		mode = va_arg(arg_list, mode_t);
		va_end(arg_list);
	}

	long fd_result = syscall(__NR_open, filename, flags, mode);
	if (fd_result < 0) {
		errno = -fd_result;
		return -1;
	}

	return fd_result;
}
