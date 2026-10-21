#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

ssize_t read_full(int fd, void *buf, size_t count) {
    size_t bytes_read = 0;
    while(bytes_read < count) {
        ssize_t res = read(fd, (char *)buf + bytes_read, count - bytes_read);
        if(res < 0) {
            if(errno == EINTR) continue;
            return -1;
        }
        else if(res == 0) break;
        bytes_read += res;
    }
    return bytes_read;
}

ssize_t write_all(int fd, void *buf, size_t count) {
    size_t bytes_written = 0;
    while(bytes_written < count) {
        ssize_t res = write(fd, (char *)buf + bytes_written, count - bytes_written);
        if(res < 0) {
            if(errno == EINTR) continue;
            return -1;
        }
        else if(res == 0) break;
        bytes_written += res;
    }
    return bytes_written;
}

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
    while(1) {
        struct sockaddr_in client = {0};
        socklen_t client_len = sizeof(client);
        int ac = accept(fd, (struct sockaddr *)&client, &client_len); 
        if(ac < 0) {
            perror("accept");
            continue;
        }
        printf("got a client\n");
        char buf[1024];
        while(1) {
            ssize_t byte_count = read(ac, buf, sizeof(buf) - 1);
            if(byte_count < 0) {
                perror("read");
                break;
            }
            else if(byte_count == 0) {
                printf("client disconnected\n");
                break;
            }
            ssize_t count_byte = write(ac, buf, byte_count);
            buf[byte_count] = '\0';
            printf("client says %s\n", buf);
            if(count_byte < 0) {
                perror("write");
                break;
            }
        }
        close(ac);
    }
    close(fd);
    return 0;
}