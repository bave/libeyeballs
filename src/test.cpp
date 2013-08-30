
#include <stdio.h>
#include <unistd.h>

#include "eyeballs.hpp"

//#include <iostream>

void
usage()
{
    std::cout << "Usage: test [server] [port]" << std::endl;
    return;
}

int
main(int argc, char** argv)
{
    if (argc != 3) {
        usage();
        exit(EXIT_FAILURE);
    }

    eyeballs_debug = true;

    class eyeballs eye;

    eye.set_timeout(0, 0);
    // sec:0, usec:0 -> sys/connect default timeout 
    // class eyeballs default is sec:0, usec:0

    int fd = eye.stream_create(argv[1], argv[2]);
    //int fd = eye.stream_create(std::string(argv[1]), std::string(argv[2]));
    if (fd == -1) {
        printf("cannt connect\n");
        exit(EXIT_FAILURE);
    } else if (fd == 0) {
        printf("timeout\n");
        exit(EXIT_FAILURE);
    }

    printf("returned_fd :%d", fd);
    if (eye.isfd4()) {
        printf(" (IPv4)\n");
    } else if (eye.isfd6()) {
        printf(" (IPv6)\n");
    } else {
        printf("(hoge)\n");
    }
    printf("- returned number is -1, connection error.\n");
    printf("- returned number is 0, connection timeout.\n");
    printf("- returned number is number, connected socket fd.\n");

    ssize_t size;
    const char* msg = "HEAD / HTTP/1.0\n\n";
    size = send(fd, msg, strlen(msg), 0);
    if (size < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    } 

    char buf[BUFSIZ];
    memset(buf, 0, sizeof(buf));
    size = recv(fd, buf, sizeof(buf), 0);
    if (size < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    } else if (size == 0) {
        printf("closed by peer host.\n");
        close(fd);
        exit(EXIT_SUCCESS);
    }
    printf("\n%s\n", buf);
    close(fd);

    return 0;
}
