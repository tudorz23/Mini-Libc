// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>

int stat(const char *restrict path, struct stat *restrict buf)
{
	int syscall_result = syscall(__NR_stat, path, buf);

	if (syscall_result < 0) {
		switch (syscall_result) {
			case -ENOENT:
				errno = ENOENT;
				break;
			case -EACCES:
				errno = EACCES;
				break;
			case -ENAMETOOLONG:
				errno = ENAMETOOLONG;
				break;
			case -ENOTDIR:
				errno = ENOTDIR;
				break;
			case -ELOOP:
				errno = ELOOP;
				break;
			default:
				errno = EIO;
				break;
		}
		return -1;
	}

	return syscall_result;
}
