// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>

int ftruncate(int fd, off_t length)
{
	int syscall_result = syscall(__NR_ftruncate, fd, length);

	if (syscall_result < 0) {
		switch (syscall_result) {
			case -EBADF:
				errno = EBADF;
				break;
			case -EACCES:
				errno = EACCES;
				break;
			case -EINVAL:
				errno = EINVAL;
				break;
			case -EFBIG:
				errno = EFBIG;
				break;
			case -EIO:
				errno = EIO;
				break;
			case -EPERM:
				errno = EPERM;
				break;
			case -EINTR:
				errno = EINTR;
				break;
		}
		return -1;
	}

	return syscall_result;
}
