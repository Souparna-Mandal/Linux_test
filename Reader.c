#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    int fd = open("/dev/shmem", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open /dev/shmem");
        return 1;
    }

    char *addr = mmap(NULL, 4096, PROT_READ, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("Failed to mmap");
        close(fd);
        return 1;
    }

    // Read and print the message from shared memory
    printf("Read from shared memory: %s\n", addr);

    // Cleanup
    munmap(addr, 4096);
    close(fd);

    return 0;
}