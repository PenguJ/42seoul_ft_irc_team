#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

# define PROC_PORT (6667)
# define MAX_LEN_OF_BUF (1024)

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

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
    int sock = -1;
    SOCKADDR_IN addr;
    char buf[MAX_LEN_OF_BUF] = {0, };
    const char* msg = "CAP LS\r\nPASS 1234\r\n:localhost.com USER jeojeon jeojeon 127.0.0.1 :jeojeon\r\n";
    ssize_t recv_len;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_quit("socket()");
    
    init_sockaddr_in(&addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PROC_PORT);

    if (connect(sock, (SOCKADDR*)&addr, sizeof(addr)) < 0)
        err_quit("connect()");
    
    if (send(sock, msg, strlen(msg), 0) < 0)
        err_quit("send()");

    if ((recv_len = recv(sock, buf, MAX_LEN_OF_BUF, 0)) < 0)
        err_quit("recv()");
    
    buf[recv_len] = '\0';
    printf("received data: %s\n", buf);

    close(sock);

    return (EXIT_SUCCESS);
}
