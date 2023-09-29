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
    
        /* request command */
    void PRIVMSG(int FD, s_Command CMD, Database * const pDB);
    void PING(int FD, s_Command CMD, Database * const pDB);
    void NOTICE(int FD, s_Command CMD, Database * const pDB);
    void JOIN(int FD, s_Command CMD, Database * const pDB);
    void NAMES(int FD, s_Command CMD, Database * const pDB);
    void PART(int FD, s_Command CMD, Database * const pDB);
    void TOPIC(int FD, s_Command CMD, Database * const pDB);
    void OPER(int FD, s_Command CMD, Database * const pDB);
    void MODE(int FD, s_Command CMD, Database * const pDB);
    void INVITE(int FD, s_Command CMD, Database * const pDB);
    void KICK(int FD, s_Command CMD, Database * const pDB);
    void PASS(int FD, s_Command CMD, Database * const pDB);
    void NICK(int FD, s_Command CMD, Database * const pDB);
    void USER(int FD, s_Command CMD, Database * const pDB);
    void CAP(int FD, s_Command CMD, Database * const pDB);
    void QUIT(int FD, s_Command CMD, Database * const pDB);
    void KILL(int FD, s_Command CMD, Database * const pDB);

        /* response command */

private:
    const int           _FD;
    std::string         _BUFF;
    Database * const    _pDB;
};

//GLOBAL FUNCTION for class MessageHandler{}



/*
< ! > all commands list
	> PRIVMSG
	> PING
	> NOTICE
	> JOIN
    > NAMES(for JOIN)
	> PART
	> TOPIC
	> OPER
	> INVITE
	> KICK
	> PASS
	> NICK
	> USER
	> MODE(user, channel)
	> CAP
	> QUIT
	> KILL

    < ~ > is it need? may be..
    > MOTD (안 해도 될지도..? 일단 생략하고 생각)
        <Establishing a server to client connection>
        Upon connecting to an IRC server, a client is sent the MOTD (if present) as well as the current user/server count (as per the LUSER command).  The server is also required to give an unambiguous message to the client which states its name and version as well as any other introductory messages which may be deemed appropriate.

        After dealing with this, the server must then send out the new user's nickname and other information as supplied by itself (USER command) and as the server could discover (from DNS/authentication servers). The server must send this information out with NICK first followed by USER.



< ! > 구현될 reply
    < ~ > 응답에 있지만, 구현하지 않아도 될 것 같은 커맨드 메모는 'X' 표시, 모르는 건 '?'(진행 중)

//공유됨 (커맨드에 있는 replies)
    > +RPL_AWAY                                //?
	> +RPL_TOPIC
	> +RPL_YOUREOPER

    > +ERR_TOOMANYTARGETS / only 2812 dup
	> +ERR_NEEDMOREPARAMS
	> +ERR_BADCHANMASK                         //?
	> +ERR_NOSUCHCHANNEL
	> +ERR_UNAVAILRESOURCE / only 2812 exist   //?
	> +ERR_NOTONCHANNEL
	> +ERR_CHANOPRIVSNEEDED
	> +ERR_NOOPERHOST     / only 2812 dup      //?
	> +ERR_PASSWDMISMATCH / only 2812 dup
	> +ERR_NOSUCHNICK
    > +ERR_ALREADYREGISTRED / only 1459 dup


//비공유 (커맨드에 있는 replies)
    > +RPL_NAMREPLY
    > +RPL_ENDOFNAMES
	> +RPL_NOTOPIC
	> +RPL_INVITING

	> +ERR_NORECIPIENT
	> +ERR_NOTEXTTOSEND
	> +ERR_CANNOTSENDTOCHAN
	> +ERR_NOTOPLEVEL              //?
	> +ERR_WILDTOPLEVEL            //?
	> +ERR_NOORIGIN
	> +ERR_NOSUCHSERVER
	> +ERR_BANNEDFROMCHAN          //X
	> +ERR_INVITEONLYCHAN
	> +ERR_BADCHANNELKEY
	> +ERR_CHANNELISFULL
	> +ERR_TOOMANYCHANNELS         //?
    > +ERR_TOOMANYMATCHES          //?
	> +ERR_NOCHANMODES   /2812     //?
	> +ERR_USERONCHANNEL
	> +ERR_USERNOTINCHANNEL /2812  //?
	> +ERR_NONICKNAMEGIVEN
	> +ERR_ERRONEUSNICKNAME
	> +ERR_NICKNAMEINUSE
	> +ERR_NICKCOLLISION           //?
	> +ERR_RESTRICTED      /2812   //?
	> +RPL_UMODEIS
    > +RPL_CHANNELMODEIS /1459
    > +RPL_BANLIST       /1459     //X
    > +RPL_ENDOFBANLIST  /1459     //X
    > +ERR_CHANNELMODEIS    /1459  //?
    > +ERR_KEYSET           /1459  //?
    > +ERR_UNKNOWNMODE      /1459
	> +ERR_USERSDONTMATCH
	> +ERR_UMODEUNKNOWNFLAG        //?
	> +ERR_NOPRIVILEGES
	> +ERR_CANTKILLSERVER          //?


// (커맨드에 없는 replies. 연결 시에 등.. 중복 여부 아직 모름 아마 아닐 듯)
    > RPL_WELCOME  /2812, but need
    > RPL_YOURHOST /2812, but need
    > RPL_CREATED  /2812, but need
    > RPL_MYINFO   /2812, but need

    > ERR_NOTREGISTERED


// (RFC에 RPL_...으로 명시되어있지 않더라도 request에 대해 클라이언트에게 무언가 주는 게 있으면 커스텀으로 구현해야 함)


< ! > 1459랑 2812랑 좀 다름(표시 됨)



==============================================================================

***  PRIVMSG  ***
  1459 = <receiver>{,<receiver>} <text to be sent>
  2812 = <msgtarget> <text to be sent>

	> +RPL_AWAY

	> +ERR_NORECIPIENT
	> +ERR_NOTEXTTOSEND
	> +ERR_CANNOTSENDTOCHAN
	> +ERR_NOTOPLEVEL            //?
	> +ERR_WILDTOPLEVEL          //?
	> +ERR_TOOMANYTARGETS
    > +ERR_NOSUCHNICK    /1459



***  PING  ***
  = <server1> [<server2>]

	> +ERR_NOORIGIN              //?
	> +ERR_NOSUCHSERVER



***  NOTICE  ***
  1459 = <nickname> <text>
  2812 = <msgtarget> <text>

    PRIVMSG와 유사하다.
    차이라면, NOTICE에 대한 응답으로 자동 회신을 보내서는 안된다는 것이다. 이 규칙은 서버에도 적용된다.
    알림을 받은 경우 클라이언트에 오류 응답을 다시 보내서도 안된다!
    이 규칙의 목적은, 수신된 항목에 대한 응답으로 클라이언트가 자동으로 무언가를 보내는 간의 루프를 방지하는 것이다.
    이는 일반적으로 다른 자동 장치와 루프에 빠지지 않도록 항상 응답하는 것으로 보이는 자동 장치(ai, 혹은 자신의 작업을 제어하는 다른 대화형 프로그램을 사용하는 클라이언트)에 의해 사용된다.
    Q. 그러면 numeric replies가 없나..?



***  JOIN  ***
  1459 = <channel>{, <channel>} [<key>{, <key>}]
  2812 = (<channel> * ("," <channel> ) [<key> * ("," <key>)]) / "0"

	> +RPL_TOPIC

	> +ERR_NEEDMOREPARAMS
	> +ERR_BANNEDFROMCHAN        //X
	> +ERR_INVITEONLYCHAN
	> +ERR_BADCHANNELKEY         //?
	> +ERR_CHANNELISFULL
	> +ERR_BADCHANMASK           //?
	> +ERR_NOSUCHCHANNEL
	> +ERR_TOOMANYCHANNELS
	> +ERR_TOOMANYTARGETS    /2812
	> +ERR_UNAVAILRESOURCE   /2812



***  NAMES  ***
  1459 = [<channel>{,<channel>}]
  2812 = [<channel> * ("," <channel>) [<target>]]

    > +RPL_NAMREPLY
    > +RPL_ENDOFNAMES

    > +ERR_TOOMANYMATCHES
    > +ERR_NOSUCHSERVER



***  PART  ***
  1459 = <channel>{, <channel>}
  2812 = <channel> * ("," <channel>) [<part message>]

	> +ERR_NEEDMOREPARAMS
	> +ERR_NOSUCHCHANNEL
	> +ERR_NOTONCHANNEL



***  TOPIC  ***
  = <channel> [<topic>]

	> +RPL_NOTOPIC
	> +RPL_TOPIC

	> +ERR_NEEDMOREPARAMS
	> +ERR_NOTONCHANNEL
	> +ERR_CHANOPRIVSNEEDED
	> +ERR_NOCHANMODES   /2812



***  OPER  ***
  = <user> <password>

	> +RPL_YOUREOPER

	> +ERR_NEEDMOREPARAMS
	> +ERR_NOOPERHOST 
	> +ERR_PASSWDMISMATCH



***  INVITE  ***
  = <nickname> <channel>

	> +RPL_INVITING
	> +RPL_AWAY

	> +ERR_NEEDMOREPARAMS
	> +ERR_NOSUCHNICK
	> +ERR_NOTONCHANNEL
	> +ERR_USERONCHANNEL
	> +ERR_CHANOPRIVSNEEDED



***  KICK  ***
  1459 = <channel> <user> [<comment>]
  2812 = <channel> * ("," <channel>) <user> * ("," <user>) [<comment>]

	> +ERR_NEEDMOREPARAMS
	> +ERR_NOSUCHCHANNEL
	> +ERR_BADCHANMASK
	> +ERR_CHANOPRIVSNEEDED
	> +ERR_USERNOTINCHANNEL /2812
	> +ERR_NOTONCHANNEL



***  PASS  ***
  = <password>

	> +ERR_NEEDMOREPARAMS
	> +ERR_ALREADYREGISTRED



***  NICK  ***
  1459 = <nickname> [<hopcount>]
  2812 = <nickname>

	> +ERR_NONICKNAMEGIVEN
	> +ERR_ERRONEUSNICKNAME
	> +ERR_NICKNAMEINUSE
	> +ERR_NICKCOLLISION
	> +ERR_UNAVAILRESOURCE /2812
	> +ERR_RESTRICTED      /2812



***  USER  ***
  1459 = <username> <hostname> <servername> <realname>
  2812 = <user> <mode> <unused> <realname>

    USER 명령은 연결 시작 시 새 사용자의 사용자 이름, 호스트 이름 및 실제 이름을 지정하는 데 사용됩니다.
    <mode>는 numeric이어야 하고, 서버에 레지스트할 때 자동적으로 설정될 수도 있습니다. <mode>는 그리고 오직 2개 비트만 의미를 가지는 비트마스트입니다. 만약 2번 비트가 세팅되면 w, 3번 비트가 세팅되면 i입니다.
    <realname>에는 공백문자가 포함될 수 있습니다! 따라서 접미사로 와야하고, ':'으로 구분해주어야 한다.

	> +RPL_YOUREOPER        /2812

	> +ERR_NEEDMOREPARAMS
    > +ERR_ALREADYREGISTRED /1459
	> +ERR_NOOPERHOST       /2812
	> +ERR_PASSWDMISMATCH   /2812



***  MODE  ***
  1459 = channel modes = <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
  1459 = user mode = <nickname> {[+|-]|i|w|s|o}
  2812 = channel modes = <channel> * (("-"/"+") * <modes> * <modeparams>)
  2812 = user mode = <nickname> * (("+"/"-") * ("i"/"w"/"o"/"O"/"r"))

	> +RPL_UMODEIS
    > +RPL_CHANNELMODEIS /1459
    > +RPL_BANLIST       /1459
    > +RPL_ENDOFBANLIST  /1459

	> +ERR_NEEDMOREPARAMS
    > +ERR_CHANNELMODEIS    /1459
    > +ERR_CHANOPRIVSNEEDED /1459
    > +ERR_NOTONCHANNEL     /1459
    > +ERR_KEYSET           /1459
    > +ERR_UNKNOWNMODE      /1459
    > +ERR_NOSUCHCHANNEL    /1459
	> +ERR_USERSDONTMATCH
	> +ERR_UMODEUNKNOWNFLAG



***  CAP  ***




***  QUIT  ***
  = [<quit message>]
	(None Replies)



***  KILL  ***
  = <nickname> <comment>

	> +ERR_NOPRIVILEGES
	> +ERR_NEEDMOREPARAMS
	> +ERR_NOSUCHNICK
	> +ERR_CANTKILLSERVER
*/

#endif
