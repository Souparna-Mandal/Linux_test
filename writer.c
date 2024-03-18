#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd = open("/dev/shmem", O_RDWR);
    if (fd < 0) {
        perror("Failed to open /dev/shmem");
        return 1;
    }

    char *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("Failed to mmap");
        close(fd);
        return 1;
    }

    // Write a message to the shared memory
    strcpy(addr, "Hello from Writer!");

    // Cleanup
    munmap(addr, 4096);
    close(fd);

    printf("Message written to shared memory.\n");

    return 0;
}