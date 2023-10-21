// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st)
{
	long syscall_result = syscall(__NR_fstat, fd, st);

	if (syscall_result < 0) {
		errno = -syscall_result;
		return -1;
	}

	return syscall_result;
}
