#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {
        perror("socket");
        exit(1);
    }
    printf("socket created");
    return 0;
}