// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd)
{
	long syscall_result = syscall(__NR_close, fd);

	if (syscall_result < 0) {
		errno = -syscall_result;
		return -1;
	}

	// The return value is 0 in case of success.
	return 0;
}
