#include <stdio.h>
#include <sys/time.h>

int main(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);

    printf("%lu, %lu\n", time.tv_sec, time.tv_usec);
    return (0);
}