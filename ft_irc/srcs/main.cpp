#include <iostream>
#include <signal.h>
#include <stdexcept>
#include "../includes/Irc.hpp"

bool Server::bRunning = true;

static void HandleSIGINT(int)
{
    Server::bRunning = false;
}

static bool isValidPortNumber(const char* str)
{
    size_t len = strlen(str);

    if (len == 0 || len > 5)
    {
        return (false);
    }
    for (size_t i = 0; i < len; ++i)
    {
        if (!isdigit(str[i]))
        {
            return (false);
        }
    }
    if (str[0] == '0' && len != 1)
    {
        return (false);
    }
    if (len == 5)
    {
        if (str[0] > '6')
        {
            return (false);
        }
        if (str[0] == '6' && str[1] > '5')
        {
            return (false);
        }
        if (strncmp("65", str, 2) == 0 && str[2] > '5')
        {
            return (false);
        }
        if (strncmp("655", str, 3) == 0 && str[3] > '3')
        {
            return (false);
        }
        if (strncmp("6553", str, 4) == 0 && str[4] > '5')
        {
            return (false);
        }
    }

    return (true);
}

static bool isValidPassword(const char* str)
{
    size_t len = strlen(str);

    if (len < 3 || len > 15)
        return (false);
    return (true);
}

int main(int argc, char* argv[])
{
{
    if (argc != 3)
    {
        std::cerr<<"Usage: ./ircserv <port(decimal)> <password>"<<std::endl;

        return (EXIT_FAILURE);
    }
    if (!isValidPortNumber(argv[1]))
    {
        std::cerr<<"error: port number must be between 0 and 65535!"<<std::endl;

        return (EXIT_FAILURE);
    }
    if (!isValidPassword(argv[2]))
    {
        std::cerr<<"error: password must be at least 3 characters and not more than 15 characters"<<std::endl;

        return (EXIT_FAILURE);
    }
}
    const u_int16_t port = (u_int16_t)atoi(argv[1]);
    Server ircserv(port, argv[2]);

    signal(SIGINT, HandleSIGINT);
    // try-catch는 오직 여기서만 사용됩니다.
    // 프로세스상의 assert와 system call의 실패만을 식별 후 종료합니다.
    // 핸들링은 없습니다.
    try
    {
        ircserv.execute();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;

        return (EXIT_FAILURE);
    }
    
    return (EXIT_SUCCESS);
}