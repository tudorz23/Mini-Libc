// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <sys/types.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence)
{
	off_t syscall_result = syscall(__NR_lseek, fd, offset, whence);

	if (syscall_result < 0) {
		switch (syscall_result) {
			case -EBADF:
				errno = EBADF;
				break;
			case -EINVAL:
				errno = EINVAL;
				break;
			case -ESPIPE:
				errno = ESPIPE;
				break;
		}
		return -1;
	}

	return syscall_result;
}
