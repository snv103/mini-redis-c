#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {
        perror("socket");
        exit(1);
    }
    printf("socket created\n");
    int set_val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &set_val, sizeof(set_val));
    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_port = htons(1234);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    int bd = bind(fd, (const struct sockaddr *)&address, sizeof(address));
     if(bd < 0) {
        perror("bind");
        exit(1);
    }
    int ls = listen(fd, SOMAXCONN);
    if(ls < 0) {
        perror("listen");
        exit(1);
    }
    printf("the server is listening to port 1234\n");
    struct sockaddr_in client = {0};
    socklen_t client_len = sizeof(client);
    int ac = accept(fd, (struct sockaddr *)&client, &client_len); 
     if(ac < 0) {
        perror("accept");
        exit(1);
    }
    printf("got a client\n");
    char buf[1024];
    ssize_t byte_count = read(ac, buf, sizeof(buf) - 1);
    if(byte_count < 0) {
        perror("read");
        exit(1);
    }
    buf[byte_count] = '\0';
    printf("client says %s\n", buf);
    close(fd);
    close(ac);
    return 0;
}