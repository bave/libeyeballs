#ifndef __EYEBALLS_HPP__
#define __EYEBALLS_HPP__

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>

#include <netinet/in.h>
#ifdef __linux__
#include <arpa/nameser.h>
#include <linux/socket.h>
#else
#include <nameser.h>
#endif
#include <resolv.h>

#include <err.h>
#include <netdb.h>
#include <signal.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

extern bool eyeballs_debug;

#ifdef DEBUG
#define EYEBALLS_PERROR(func) do {                              \
    if (eyeballs_debug) {                                       \
    char s[BUFSIZ];                                             \
    memset(s, 0, BUFSIZ);                                       \
    snprintf(s, BUFSIZ, "%s(%d):%s", __FILE__, __LINE__, func); \
    perror(s);                                                  \
    }                                                           \
} while (false)
#else
#define EYEBALLS_PERROR(func) do {} while (false)
#endif

class eyeballs{

    struct local_addrinfo {
        int flags;
        int family;
        int socktype;
        int protocol;
        socklen_t addrlen;
        struct sockaddr_storage addr;
        char canonname[BUFSIZ];
    };

public:
    eyeballs() {
        fd4 = -1;
        fd6 = -1;
        in4 = false;
        in6 = false;
        memset(&la4, 0, sizeof(la4));
        memset(&la6, 0, sizeof(la6));
        memset(&timeout, 0, sizeof(timeout));
        linger.l_onoff = 1;
        linger.l_linger = 0;
    };

    virtual ~eyeballs() {
    };

    int get_fd4();
    int get_fd6();
    int stream_create(const char* host, const char* port);
    int stream_create(const std::string& host, const std::string& port);
    void set_timeout(int sec, int usec);
    

private:
    void _get_resolver();
    bool _cpy_addrinfo(struct addrinfo* ai);

    int fd4;
    int fd6;
    struct timeval timeout;

    bool in4;
    bool in6;
    struct local_addrinfo la4;
    struct local_addrinfo la6;
    struct linger linger;
};

#endif
