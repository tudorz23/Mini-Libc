// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>

int truncate(const char *path, off_t length)
{
	int syscall_result = syscall(__NR_truncate, path, length);

	if (syscall_result < 0) {
		switch (syscall_result) {
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
			case -ENAMETOOLONG:
				errno = ENAMETOOLONG;
				break;
			case -ENOENT:
				errno = ENOENT;
				break;
			case -ENOTDIR:
				errno = ENOTDIR;
				break;
			case -ELOOP:
				errno = ELOOP;
				break;
			case -EISDIR:
				errno = EISDIR;
				break;
		}
		return -1;
	}

	return syscall_result;
}
