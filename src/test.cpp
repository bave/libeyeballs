
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

    printf("fd_IPversion4:%d\n", eye.get_fd4());
    printf("fd_IPversion6:%d\n", eye.get_fd6());
    printf("returned_fd  :%d\n", fd);
    printf("* returned number is -1, connection error.\n");
    printf("* returned number is 0, connection timeout.\n");
    printf("* returned number is number, connected socket fd.\n");

    ssize_t size;
    size = send(fd, "HEAD / HTTP/1.1\n\n", strlen("HEAD / HTTP/1.0\n\n"), 0);
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
    sleep(10);

    return 0;
}
