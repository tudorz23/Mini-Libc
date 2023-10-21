#include <unistd.h>
#include <internal/syscall.h>
#include <time.h>
#include <errno.h>

int nanosleep(const struct timespec *requested_time, struct timespec *remaining)
{
    long syscall_result = syscall(__NR_nanosleep, requested_time, remaining);

    if (syscall_result < 0) {
        errno = -syscall_result;
        return -1;
    }

    return 0;
}
