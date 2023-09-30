//#pragma once
#ifndef MESSAGE_HANDLER_HPP
# define MESSAGE_HANDLER_HPP

# include <iostream>
# include <vector>

# include "../includes/Channel.hpp"
# include "../includes/Database.hpp"
# include "../includes/Server.hpp"
# include "../includes/User.hpp"

//STANDARD: 어떤 상수가 constexpr의 특징을 가지고 있고, 다른 클래스에서 그 값이 사용되는 경우에만
//				멤버변수를 public으로 선언할 수 있다.
//			반드시! 상속 여부를 체크한 뒤 클래스를 작성한다. (std::exception 상속은 제외)
//			이를 위해 최초 양식에는 주석이 없다.
// 			상속일 시, 메소드와 변수 모두 'protected:'를 명시적으로 나타낸다.(인터페이스인 경우 예외)
// 			상속일 시, 소멸자는 가상함수이다.
// 			상속일 시, 상위 클래스의 'protected:'멤버변수와 메소드를 주석으로 표현한다.
// 			이때 네임스페이스와 함께 명시한다.
// 			상속을 하거나, 받으면 해당 클래스를 들여쓰기로 한 줄씩 명시한다.
// is do inherit? (NO): is abstracted? (NO): is interface? (NO)
// is be inherited? (NO)

typedef struct Command
{
    std::string                 prefix;
    std::string                 command;
    std::vector<std::string>    parameters;
    std::string                 suffix;
}   s_Command;

class MessageHandler
{
public:
    //Constructor overload & OCCF
    MessageHandler(int FD, std::string &BUFF, Database * const pDB);
    ~MessageHandler();
    //Exception
    //Operator overload
    //Getter & Setter
    //Behavior
    void run();

private:
    //Constructor overload & OCCF
    MessageHandler();
    MessageHandler(const MessageHandler& rCopy);
    MessageHandler& operator=(const MessageHandler& rRhs);
    //Exception
    //Operator overload
    //Getter & Setter
    //Behavior
    std::vector<std::string> split(const std::string& STR, char DL);

private:
    const int           _FD;
    std::string         _BUFF;
    Database * const    _pDB;
    void PRIVMSG(s_Command CMD, User *user);
    void PING(s_Command CMD, User *user);
    // void NOTICE(s_Command CMD, User *user); //안쓸듯
    void JOIN(s_Command CMD, User *user);
    void NAMES(s_Command CMD, User *user);
    void PART(s_Command CMD, User *user);
    void TOPIC(s_Command CMD, User *user);
    void OPER(s_Command CMD, User *user);
    void MODE(s_Command CMD, User *user);
    void INVITE(s_Command CMD, User *user);
    void KICK(s_Command CMD, User *user);
    void PASS(s_Command CMD, User *user);
    void NICK(s_Command CMD, User *user);
    void USER(s_Command CMD, User *user);
    void CAP(s_Command CMD, User *user);
    void QUIT(s_Command CMD, User *user);
    void KILL(s_Command CMD, User *user);
public:

// SPECIAL CHAR
    static const std::string ENDL;
    static const std::string COL;
    static const std::string SPACE;
    static const std::string AST;
    static const std::string HASH;

// RPL 
    static const std::string RPL_WELCOME;
    static const std::string RPL_UMODEIS;
    static const std::string RPL_NOTOPIC;
    static const std::string RPL_TOPIC;

// ERR
    static const std::string ERR_UNKNOWNERROR;
    static const std::string ERR_NOSUCHNICK;
    static const std::string ERR_NOSUCHNICK_MSG;
    static const std::string ERR_NOSUCHSERVER;
    static const std::string ERR_NOSUCHCHANNEL;
    static const std::string ERR_NOSUCHCHANNEL_MSG;
    static const std::string ERR_CANNOTSENDTOCHAN;
    static const std::string ERR_TOOMANYCHANNELS;
    static const std::string ERR_NOORIGIN;
    static const std::string ERR_NOORIGIN_MSG;
    static const std::string ERR_NORECIPIENT;
    static const std::string ERR_NORECIPIENT_MSG;
    static const std::string ERR_NOTEXTTOSEND;
    static const std::string ERR_NOTEXTTOSEND_MSG;

    static const std::string ERR_UNKNOWNCOMMAND;
    static const std::string ERR_UNKNOWNCOMMAND_MSG;

    static const std::string ERR_NONICKNAMEGIVEN;
    static const std::string ERR_NONICKNAMEGIVEN_MSG;
    static const std::string ERR_ERRONEUSNICKNAME;
    static const std::string ERR_ERRONEUSNICKNAME_MSG;
    static const std::string ERR_NICKNAMEINUSE;
    static const std::string ERR_NICKNAMEINUSE_MSG;
    static const std::string ERR_UNAVAILRESOURCE;
    static const std::string ERR_UNAVAILRESOURCE_MSG;

    static const std::string ERR_USERNOTINCHANNEL;
    static const std::string ERR_USERNOTINCHANNEL_MSG;
    static const std::string ERR_NOTONCHANNEL;
    static const std::string ERR_NOTONCHANNEL_MSG;
    static const std::string ERR_USERONCHANNEL;

    static const std::string ERR_NOTREGISTERED;
    static const std::string ERR_NOTREGISTERED_MSG;
    static const std::string ERR_NEEDMOREPARAMS;
    static const std::string ERR_NEEDMOREPARAMS_MSG;
    static const std::string ERR_ALREADYREGISTERED;
    static const std::string ERR_ALREADYREGISTERED_MSG;
    static const std::string ERR_PASSWDMISMATCH;
    static const std::string ERR_PASSWDMISMATCH_MSG;

    static const std::string ERR_CHANNELISFULL;
    static const std::string ERR_CHANNELISFULL_MSG;
    static const std::string ERR_INVITEONLYCHAN;
    static const std::string ERR_INVITEONLYCHAN_MSG;
    static const std::string ERR_BADCHANNELKEY;
    static const std::string ERR_BADCHANNELKEY_MSG;
    static const std::string ERR_ERRONEUSCHANNELNAME;
    static const std::string ERR_ERRONEUSCHANNELNAME_MSG;
    static const std::string ERR_CHANOPRIVSNEEDED;
    static const std::string ERR_CHANOPRIVSNEEDED_MSG;
};

//GLOBAL FUNCTION for class MessageHandler{}

#endif
