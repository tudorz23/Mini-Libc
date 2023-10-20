// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st)
{
	int syscall_result = syscall(__NR_fstat, fd, st);

	if (syscall_result < 0) {
		if (syscall_result == -EBADF) {
			errno = EBADF;
		} 

		return -1;
	}

	return syscall_result;
}
