#include <unistd.h>
#include <internal/syscall.h>
#include <time.h>
#include <errno.h>

unsigned int sleep(unsigned int seconds) {
    struct timespec requested;
    requested.tv_sec = seconds;
    requested.tv_nsec = 0;

    if (nanosleep(&requested, &requested) != 0) {
        return requested.tv_sec;
    }

    return 0;
}
