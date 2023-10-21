#include <unistd.h>
#include <internal/syscall.h>
#include <time.h>
#include <errno.h>

int nanosleep(const struct timespec *requested_time, struct timespec *remaining)
{
    int syscall_result = syscall(__NR_nanosleep, requested_time, remaining);

    if (syscall_result < 0) {
        if (syscall_result == -EINTR) {
            errno = EINTR;
        } else if (syscall_result == -EINVAL) {
            errno = EINVAL;
        }
        return -1;
    }

    return 0;
}
