#include "eyeballs.hpp"

bool eyeballs_debug;

eyeballs::eyeballs() {
    fd4 = -1;
    fd6 = -1;
    in4 = false;
    in6 = false;
    memset(&la4, 0, sizeof(la4));
    memset(&la6, 0, sizeof(la6));
    memset(&timeout, 0, sizeof(timeout));
    linger.l_onoff = 1;
    linger.l_linger = 0;
}

eyeballs::~eyeballs() {
}

// if cloud not open fd4, return -1.
int
eyeballs::get_fd4()
{
    return fd4;
}

// if cloud not open fd6, return -1.
int
eyeballs::get_fd6()
{
    return fd6;
}

int
eyeballs::stream_create(const char* host, const char* port)
{
    return stream_create(std::string(host), std::string(port));
}

int
eyeballs::stream_create(const std::string& host, const std::string& port)
{

    int on  = 1;
    int off = 0;
    int error;

    struct addrinfo *res;
    struct addrinfo *res0;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_ALL|AI_ADDRCONFIG;

    error = getaddrinfo(host.c_str(), port.c_str(), &hints, &res0);
    if (error) {
        if (eyeballs_debug) {
            fprintf(stderr, "%s(%d):getaddrinfo: %s\n", __FILE__, __LINE__, gai_strerror(error));
        }
        return -1;
    }

    for (res = res0; res; res = res->ai_next) {
        if (in4 && in6) break; 
        _cpy_addrinfo(res);
    }
    free(res0);

    signal(SIGPIPE, SIG_IGN);
    if (in4) {
        fd4 = socket(la4.family, la4.socktype, la4.protocol);
        if (fd4 == -1) {
            EYEBALLS_PERROR("socket");
            return -1;
        }
        if (setsockopt(fd4, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) < 0) {
            EYEBALLS_PERROR("setsockopt");
            close(fd4);
            return -1;
        }
        error = ioctl(fd4, FIONBIO, &on);
        if (error == -1) {
            EYEBALLS_PERROR("ioctl");
            close(fd4);
            return -1;
        }
    }

    if (in6) {
        fd6 = socket(la6.family, la6.socktype, la6.protocol);
        if (fd6 == -1) {
            EYEBALLS_PERROR("socket");
            return -1;
        }
        if (setsockopt(fd6, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) < 0) {
            EYEBALLS_PERROR("setsockopt");
            close(fd6);
            return -1;
        }
        error = ioctl(fd6, FIONBIO, &on);
        if (error == -1) {
            EYEBALLS_PERROR("ioctl");
            close(fd6);
            return -1;
        }
    }

    int max;
    fd_set r_fds;
    fd_set w_fds;
    fd_set e_fds;
    FD_ZERO(&r_fds);
    FD_ZERO(&w_fds);
    FD_ZERO(&e_fds);

    if (fd4 > fd6) {
        max = fd4;
    } else {
        max = fd6;
    }

    if (in6) {
        FD_SET(fd6, &r_fds);
        FD_SET(fd6, &w_fds);
        FD_SET(fd6, &e_fds);
        connect(fd6, (struct sockaddr*)&(la6.addr), la6.addrlen);
    }
    if (in4) {
        FD_SET(fd4, &r_fds);
        FD_SET(fd4, &w_fds);
        FD_SET(fd4, &e_fds);
        connect(fd4, (struct sockaddr*)&(la4.addr), la4.addrlen);
    }


    if (timeout.tv_sec == 0 && timeout.tv_usec == 0) {
        error = select(max+1, &r_fds, &w_fds, &e_fds, NULL);
    } else {
        error = select(max+1, &r_fds, &w_fds, &e_fds, &timeout);
    }


    if (error == -1) {

        // error
        EYEBALLS_PERROR("select");
        close(fd4);
        close(fd6);
        return -1;

    } else if (error == 0) {

        // timeout is return 0
        close(fd4);
        close(fd6);
        return 0;

    } else {

        /*
        socklen_t len = sizeof(error);
        if (getsockopt(fd4, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
            printf("getsockopt error");
        }
        if (getsockopt(fd6 SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
            printf("getsockopt error");
        }
        */

        if (FD_ISSET(fd6, &e_fds)) {
            close(fd6);
            fd6 = -1;
        } else if(FD_ISSET(fd4, &e_fds)) {
            close(fd4);
            fd4 = -1;
        }

        if (in6 && fd6 != -1) {
            if (FD_ISSET(fd6, &r_fds) || FD_ISSET(fd6, &w_fds)) {
                if (in4) {
                    if (setsockopt(fd4, SOL_SOCKET, SO_LINGER, (struct linger*)&linger, sizeof(linger)) < 0) {
                        EYEBALLS_PERROR("setsockopt");
                        close(fd4);
                        close(fd6);
                        return -1;
                    } 
                }
                error = ioctl(fd6, FIONBIO, &off);
                if (error == -1) {
                    EYEBALLS_PERROR("ioctl");
                    close(fd4);
                    close(fd6);
                    return -1;
                }
                close(fd4);
                return fd6;
            }
        }

        if (in4 && fd4 != -1) {
            if (FD_ISSET(fd4, &r_fds) || FD_ISSET(fd4, &w_fds)) {
                if (in6) {
                    if (setsockopt(fd6, SOL_SOCKET, SO_LINGER, (struct linger*)&linger, sizeof(linger)) < 0) {
                        EYEBALLS_PERROR("setsockopt");
                        close(fd4);
                        close(fd6);
                        return -1;
                    }
                }
                error = ioctl(fd4, FIONBIO, &off);
                if (error == -1) {
                    EYEBALLS_PERROR("ioctl");
                    close(fd4);
                    close(fd6);
                    return -1;
                }
                close(fd6);
                return fd4;
            }
        }

    }

    return -1;
}

bool eyeballs::_cpy_addrinfo(struct addrinfo* ai)
{
    if (ai->ai_family == AF_INET) {

        if (in4) { return false; }
        if (la4.family) { return false; }
        la4.flags = ai->ai_flags;
        la4.family = ai->ai_family;
        la4.socktype = ai->ai_socktype;
        la4.protocol = ai->ai_protocol;
        la4.addrlen = ai->ai_addrlen;
        memcpy(&(la4.addr), ai->ai_addr, ai->ai_addrlen);
        if (ai->ai_canonname) {
            memcpy(&(la4.canonname), ai->ai_canonname, strlen(ai->ai_canonname));
        }
        in4 = true;
        return true;

    } else if (ai->ai_family == AF_INET6) {

        if (in6) { return false; }
        if (la6.family) { return false; }
        la6.flags = ai->ai_flags;
        la6.family = ai->ai_family;
        la6.socktype = ai->ai_socktype;
        la6.protocol = ai->ai_protocol;
        la6.addrlen = ai->ai_addrlen;
        memcpy(&(la6.addr), ai->ai_addr, ai->ai_addrlen);
        if (ai->ai_canonname) {
            memcpy(&(la6.canonname), ai->ai_canonname, strlen(ai->ai_canonname));
        }
        in6 = true;
        return true;

    } else {

        return false;

    }

    return false;
}

void
eyeballs::set_timeout(int sec, int usec)
{
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    return;
}

