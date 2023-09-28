//#pragma once
#ifndef SERVER_HPP
# define SERVER_HPP

// C header
# include <arpa/inet.h>
# include <fcntl.h>
# include <netdb.h>
# include <sys/poll.h>
# include <sys/socket.h>
# include <unistd.h>

// C++ header
# include <cstdlib>
# include <cstring>
# include <iostream>
# include <stdexcept>
# include <vector>
# include "Database.hpp"
# include "MessageHandler.hpp"

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

//STANDARD: 어떤 상수가 constexpr의 특징을 가지고 있고, 다른 클래스에서 그 값이 사용되는 경우에만
//				멤버변수를 public으로 선언할 수 있다.
//			반드시! 상속 여부를 체크한 뒤 클래스를 작성한다. (std::exception 상속은 제외)
//			이를 위해 최초 양식에는 주석이 없다.
//             상속일 시, 메소드와 변수 모두 'protected:'를 명시적으로 나타낸다.(인터페이스인 경우 예외)
//             상속일 시, 소멸자는 가상함수이다.
//             상속일 시, 상위 클래스의 'protected:'멤버변수와 메소드를 주석으로 표현한다.
//             이때 네임스페이스와 함께 명시한다.
//             상속을 하거나, 받으면 해당 클래스를 들여쓰기로 한 줄씩 명시한다.
// is do inherit? (NO): is abstracted? (NO): is interface? (NO)
// is be inherited? (NO)
class Server
{
public:
    //Constructor overload & OCCF
    Server();
    ~Server();
    //Exception
    //Operator overload
    //Getter & Setter
    //Behavior
    void execute();
    void processExitError();

private:
    //Constructor overload & OCCF
    Server& operator=(const Server& rRhs);
    Server(const Server& rCopy);
    //Exception
    //Operator overload
    //Getter & Setter
    //Behavior

public:
    // maximum length of Irc`s features
    static const u_int16_t          MAX_NICK_LEN = 9;
    static const u_int16_t          MAX_MSG_LEN = 512;
    static const u_int16_t          MAX_HOST_LEN = 63;
    static const u_int16_t          MAX_CMD_PARAM = 15;
    static const u_int16_t          MAX_CHANGS_MODE_PARAM_PER_CMD = 3;
    static const u_int16_t          MAX_JOIN_CHAN = 5;

    // server state
    static bool                     bRunning;
    static std::string              ServPWD;
    static u_int16_t                Port;
    static std::string              PortSTR;
    static std::string              Host;

private:
    int                             _servSock;
    std::vector<pollfd>             _PFDS;
    Database*                       _pDB;
};

//GLOBAL FUNCTION for class Server{}


#endif
