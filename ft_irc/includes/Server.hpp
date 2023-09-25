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
# include <map>
# include <stdexcept>
# include <vector>
# include "Channel.hpp"
# include "User.hpp"

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
    Server(const u_int16_t &port, const std::string &PWD);
    ~Server();
    //Exception
    //Operator overload
    //Getter & Setter
    //Behavior
    void execute();

private:
    //Constructor overload & OCCF
    Server();
    Server& operator=(const Server& rRhs);
    Server(const Server& rCopy);
    //Exception
    //Operator overload
    //Getter & Setter
    //Behavior

public:
    // server state
    static bool                     bRunning;

    // maximum length of Irc`s features
    static const u_int16_t          MAX_NICK_LEN = 9;
    static const u_int16_t          MAX_MSG_LEN = 512;
    static const u_int16_t          MAX_HOST_LEN = 63;
    static const u_int16_t          MAX_CMD_PARAM = 15;
    static const u_int16_t          MAX_CHANGS_MODE_PARAM_PER_CMD = 3;
    static const u_int16_t          MAX_JOIN_CHAN = 5;

    /* command responses 
        0 - 99 : client-server connections only, never travel between servers.
        200 - 399 : replies generated in the response to commands.
        400 - 599 : error replies. */
    /* 001 - 004 : the server sends replies to a user upon successful registration. */
    static const u_int16_t          RPL_WELCOME = 1;
    static const u_int16_t          RPL_YOURHOST = 2;
    static const u_int16_t          RPL_CREATED = 3;
    static const u_int16_t          RPL_MYINFO = 4;
    /* 005 : Sent by the server to a user to suggest an alternative server.  This is often used when the connection is refused because the server is already full. */
    static const u_int16_t          RPL_BOUNCE = 5;




    // static const u_int16_t          ERR_NOSUCHNICK = 401;
    static const u_int16_t          ERR_NOSUCHSERVER = 402;
    static const u_int16_t          ERR_NOSUCHCHANNEL = 403;
    static const u_int16_t          ERR_CANNOTSENDTOCHAN = 404;
    static const u_int16_t          ERR_TOOMANYCHANNELS = 405;
    static const u_int16_t          ERR_WASNOSUCHNICK = 406;
    static const u_int16_t          ERR_TOOMANYTARGETS = 407;
    static const u_int16_t          ERR_NOSUCHSERVICE = 408;
    static const u_int16_t          ERR_NOORIGIN = 409;
    static const u_int16_t          ERR_NORECIPIENT = 411;
    static const u_int16_t          ERR_NOTEXTTOSEND = 412;
    static const u_int16_t          ERR_NOTOPLEVEL = 413;
    static const u_int16_t          ERR_WILDTOPLEVEL = 414;
    static const u_int16_t          ERR_BADMASK = 415;
    static const u_int16_t          ERR_UNKNOWNCOMMAND = 421;
    static const u_int16_t          ERR_NOMOTD = 422;
    static const u_int16_t          ERR_NOADMININFO = 423;
    static const u_int16_t          ERR_FILEERROR = 424;
    static const u_int16_t          ERR_NONICKNAMEGIVEN = 431;
    static const u_int16_t          ERR_ERRONEUSNICKNAME = 432;
    static const u_int16_t          ERR_NICKNAMEINUSE = 433;
    static const u_int16_t          ERR_NICKCOLLISION = 436;
    static const u_int16_t          ERR_UNAVAILRESOURCE = 437;
    static const u_int16_t          ERR_USERNOTINCHANNEL = 441;
    static const u_int16_t          ERR_NOTONCHANNEL = 442;
    static const u_int16_t          ERR_USERONCHANNEL = 443;
    static const u_int16_t          ERR_NOLOGIN = 444;
    static const u_int16_t          ERR_SUMMONDISABLED = 445;
    static const u_int16_t          ERR_USERSDISABLED = 446;
    static const u_int16_t          ERR_NOTREGISTERED = 451;
    static const u_int16_t          ERR_NEEDMOREPARAMS = 461;
    static const u_int16_t          ERR_ALREADYREGISTRED = 462;
    static const u_int16_t          ERR_NOPERMFORHOST = 463;
    static const u_int16_t          ERR_PASSWDMISMATCH = 464;
    static const u_int16_t          ERR_YOUREBANNEDCREEP = 465;
    static const u_int16_t          ERR_YOUWILLBEBANNED = 466;
    static const u_int16_t          ERR_KEYSET = 467;
    static const u_int16_t          ERR_CHANNELISFULL = 471;
    static const u_int16_t          ERR_UNKNOWNMODE = 472;
    static const u_int16_t          ERR_INVITEONLYCHAN = 473;
    static const u_int16_t          ERR_BANNEDFROMCHAN = 474;
    static const u_int16_t          ERR_BADCHANNELKEY = 475;
    static const u_int16_t          ERR_BADCHANMASK = 476;
    static const u_int16_t          ERR_NOCHANMODES = 477;
    static const u_int16_t          ERR_BANLISTFULL = 478;
    static const u_int16_t          ERR_NOPRIVILEGES = 481;
    static const u_int16_t          ERR_CHANOPRIVSNEEDED = 482;
    static const u_int16_t          ERR_CANTKILLSERVER = 483;
    static const u_int16_t          ERR_RESTRICTED = 484;
    static const u_int16_t          ERR_UNIQOPPRIVSNEEDED = 485;
    static const u_int16_t          ERR_NOOPERHOST = 491;
    static const u_int16_t          ERR_UMODEUNKNOWNFLAG = 501;
    static const u_int16_t          ERR_USERSDONTMATCH = 502;

private:
    int                             _servSock;
    const u_int16_t                 _port;
    const std::string               _PWD;
    std::vector<pollfd>             _PFDS;
};

//GLOBAL FUNCTION for class Server{}

#endif
