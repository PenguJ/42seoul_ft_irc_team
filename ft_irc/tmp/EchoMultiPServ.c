#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>

# define PROC_PORT (9999)
# define MAX_BUF_LEN (1024)
# define MAX_CLNT_NUM (1024)

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct pollfd POLLFD;

void init_sockaddr_in(SOCKADDR_IN* st)
{
    bzero(st, sizeof(*st));
}

void err_quit(const char* const err_msg)
{
    perror("error: ");
    perror(err_msg);
    exit (EXIT_FAILURE);
}

int main()
{
    int serv_sock = -1;
    int clnt_sock = -1;
    int optval = 1;
    SOCKADDR_IN addr;
    SOCKADDR_IN clnt_addr;
    POLLFD clnts[MAX_CLNT_NUM];
    size_t poll_max_fd = 0;
    size_t poll_idx = 1;
    char buf[MAX_BUF_LEN] = {0, };
    socklen_t addr_len = 0;

    if ((serv_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_quit("socket()");

    init_sockaddr_in(&addr);
    init_sockaddr_in(&clnt_addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PROC_PORT);

    bzero(clnts, sizeof(clnts));
    for (size_t i = 0; i < MAX_CLNT_NUM; ++i)
        clnts[i].fd = -1;
    clnts[0].fd = serv_sock;
    clnts[0].events = POLLIN;

    optval = 1;
    if (setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
        err_quit("setsockopt()");

    if (fcntl(serv_sock, F_SETFL, O_NONBLOCK))
        err_quit("fcntl()");

    if (bind(serv_sock, (SOCKADDR*)&addr, sizeof(addr)) < 0)
        err_quit("bind()");

    if (listen(serv_sock, 5) < 0)
        err_quit("listen()");

    printf("Waiting for client..\n");

    while (true)
    {
        if (poll(clnts, poll_max_fd + 1, 5000) < 0)
            err_quit("poll()");
        
        if (clnts[0].revents & POLLIN)
        {
            addr_len = sizeof(clnt_addr);
            clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &addr_len);

            for (poll_idx = 1; poll_idx < MAX_CLNT_NUM; ++poll_idx)
            {
                if (clnts[poll_idx].fd < 0)
                {
                    clnts[poll_idx].fd = clnt_sock;
                    clnts[poll_idx].events = POLLIN;
                    break ;
                }
            }

            if (poll_idx == MAX_CLNT_NUM)
                err_quit("too many clients!");
            
            if (poll_idx > poll_max_fd)
                poll_max_fd = poll_idx;
            printf("fd %d connected\n", clnt_sock);
            continue ;
        }
        for (poll_idx = 1; poll_idx <= poll_max_fd; ++poll_idx)
        {
            if (clnts[poll_idx].fd < 0)
                continue ;
            if (clnts[poll_idx].revents & POLLIN)
            {
                bzero(buf, MAX_BUF_LEN);

                if (read(clnts[poll_idx].fd, buf, MAX_BUF_LEN) <= 0)
                {
                    close(clnts[poll_idx].fd);
                    printf("%d: client disconnected\n", clnts[poll_idx].fd);
                    clnts[poll_idx].fd = -1;

                    if (poll_idx == poll_max_fd)
                    {
                        while (clnts[poll_max_fd].fd < 0)
                            --poll_max_fd;
                    }
                }
                else
                    write(clnts[poll_idx].fd, buf, strlen(buf));
            }
        }
    }

    close(serv_sock);

    return (EXIT_SUCCESS);
}
