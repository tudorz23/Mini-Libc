// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <sys/types.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence)
{
	long syscall_result = syscall(__NR_lseek, fd, offset, whence);

	if (syscall_result < 0) {
		errno = -syscall_result;
		return -1;
	}

	return syscall_result;
}
