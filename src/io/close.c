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
		switch (fd_result) {
			case -EBADF:
				errno = EBADF;
				break;
			case -EINTR:
				errno = EINTR;
				break;
			case -ENOSPC:
				errno = ENOSPC;
				break;
			default:
				errno = EIO;
				break;
		}
		return -1;
	}

	return fd_result;
}
