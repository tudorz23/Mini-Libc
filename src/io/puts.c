#include <stdio.h>
#include <internal/syscall.h>
#include <internal/io.h>
#include <errno.h>

int puts(const char *str)
{
    char *str_start = (char *)str;
    size_t len = 0;

    while (*str != '\0') {
        len++;
        str++;
    }

    ssize_t write_result = write(1, str_start, len);

    if (write_result > 0) {
        write(1, "\n", 1);
        return 1;
    }

    // On error, return EOF and set error indicator.
    errno = EIO;
    return EOF;
}
