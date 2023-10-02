#include <sstream>
#include "../includes/MessageHandler.hpp"

const string MessageHandler::ENDL = "\r\n";
const string MessageHandler::COL = ":";
const string MessageHandler::SPACE = " ";
const string MessageHandler::AST = "*";
const string MessageHandler::HASH = "#";
const string MessageHandler::EXCL = "!";
const string MessageHandler::AT = "@";
const string MessageHandler::RPL_WELCOME = "001";
const string MessageHandler::RPL_UMODEIS = "221";
const string MessageHandler::RPL_NOTOPIC = "331";
const string MessageHandler::RPL_TOPIC = "332";
const string MessageHandler::ERR_UNKNOWNERROR = "400";
const string MessageHandler::ERR_NOSUCHNICK = "401";
const string MessageHandler::ERR_NOSUCHNICK_MSG = " :No such nick/channel";
const string MessageHandler::ERR_NOSUCHSERVER = "402";
const string MessageHandler::ERR_NOSUCHCHANNEL = "403";
const string MessageHandler::ERR_NOSUCHCHANNEL_MSG = " :No such channel";
const string MessageHandler::ERR_CANNOTSENDTOCHAN = "404";
const string MessageHandler::ERR_CANNOTSENDTOCHAN_MSG = " :Cannot send to channel";
const string MessageHandler::ERR_TOOMANYCHANNELS = "405";
const string MessageHandler::ERR_NOORIGIN = "409";
const string MessageHandler::ERR_NOORIGIN_MSG = " :No origin specified";
const string MessageHandler::ERR_NORECIPIENT = "411";
const string MessageHandler::ERR_NORECIPIENT_MSG = " :No recipient given";
const string MessageHandler::ERR_NOTEXTTOSEND = "412";
const string MessageHandler::ERR_NOTEXTTOSEND_MSG = " :No text to send";

const string MessageHandler::ERR_UNKNOWNCOMMAND = "421";
const string MessageHandler::ERR_UNKNOWNCOMMAND_MSG = " :Unknown command";

const string MessageHandler::ERR_NONICKNAMEGIVEN = "431";
const string MessageHandler::ERR_NONICKNAMEGIVEN_MSG = " :No nickname given";
const string MessageHandler::ERR_ERRONEUSNICKNAME = "432";
const string MessageHandler::ERR_ERRONEUSNICKNAME_MSG = " :Erroneous nickname";
const string MessageHandler::ERR_NICKNAMEINUSE = "433";
const string MessageHandler::ERR_NICKNAMEINUSE_MSG = " :Nickname is already in use";
const string MessageHandler::ERR_UNAVAILRESOURCE = "437";
const string MessageHandler::ERR_UNAVAILRESOURCE_MSG = " :Channel is temporarily unavailable";

const string MessageHandler::ERR_USERNOTINCHANNEL = "441";
const string MessageHandler::ERR_USERNOTINCHANNEL_MSG = " :They aren't on that channel";
const string MessageHandler::ERR_NOTONCHANNEL = "442";
const string MessageHandler::ERR_NOTONCHANNEL_MSG = " :You're not on that channel";
const string MessageHandler::ERR_USERONCHANNEL = "443";
const string MessageHandler::ERR_NOTREGISTERED = "451";
const string MessageHandler::ERR_NOTREGISTERED_MSG = ":You have not registered";
const string MessageHandler::ERR_NEEDMOREPARAMS = "461";
const string MessageHandler::ERR_NEEDMOREPARAMS_MSG = " :Not enough parameters";
const string MessageHandler::ERR_ALREADYREGISTERED = "462";
const string MessageHandler::ERR_ALREADYREGISTERED_MSG = " :You may not reregister";
const string MessageHandler::ERR_PASSWDMISMATCH = "464";
const string MessageHandler::ERR_PASSWDMISMATCH_MSG = " :Password incorrect";

const string MessageHandler::ERR_CHANNELISFULL = "471";
const string MessageHandler::ERR_CHANNELISFULL_MSG = " :Cannot join channel (+l)";
const string MessageHandler::ERR_INVITEONLYCHAN = "473";
const string MessageHandler::ERR_INVITEONLYCHAN_MSG = " :Cannot join channel (+i)";
const string MessageHandler::ERR_BADCHANNELKEY = "475";
const string MessageHandler::ERR_BADCHANNELKEY_MSG = " :Cannot join channel (+k)"; 
const string MessageHandler::ERR_ERRONEUSCHANNELNAME = "479";
const string MessageHandler::ERR_ERRONEUSCHANNELNAME_MSG = " :Channel name contains illegal characters";
const string MessageHandler::ERR_CHANOPRIVSNEEDED = "482";
const string MessageHandler::ERR_CHANOPRIVSNEEDED_MSG = " :You're not channel operator";

//BY jeojeon
const string MessageHandler::ERR_TOOMANYTARGETS = "407";
const string MessageHandler::ERR_TOOMANYTARGETS_MSG = " :Duplicate recipients. No message delivered";


//STANDARD: (순수)가상함수는 주석과 함께 명시적으로 정의한다. 양식은 다음과 같다.
//				/*virtual*/void Bar::Baz() {...}
//				/*pure virtual*/void Bar::Baz() {}
//			변수명 앞에 접두사를 사용한다.
//				m은 멤버, p는 관리 필요한 포인터, cp는 편안한 포인터, r은 참조형

//****************************************************************************/
//Constructor overload & OCCF ************************************************/
//STANDARD: 기입 순서는 다음과 같다.
//			오버로딩 생성자->기본 생성자->소멸자->대입연산자->복사 생성자
//			대입연산자 주석 '있음'은 대게 멤버변수 동적할당 '없음'을 의미한다.
//			혹은 얕은 복사를 의미한다. 이 경우, 명시적으로 표시한다.
//			기본생성자를 사용하지 않는 경우, 오버로딩 후 주석을 통해 명시적으로 표시한다.
    //PUBLIC:
MessageHandler::MessageHandler(int FD, string &BUFF, Database * const pDB, vector<pollfd>* pPFDS)
    : _FD(FD)
    , _BUFF(BUFF)
    , _pDB(pDB)
    , _pPFDS(pPFDS)
{   }

MessageHandler::~MessageHandler()
{	}

    //PRIVATE:
MessageHandler::MessageHandler()
    : _FD(0)
    , _pDB(NULL)
{
    cerr<<"error: never works"<<endl;
}

MessageHandler& MessageHandler::operator=(const MessageHandler& rRhs)
{
    cerr<<"error: never works"<<endl;
    if (this == &rRhs)
    {
        return (*this);
    }
    /*
    if || for (mPtrVAR || mRefVAR)
    {
        //delete mPtrVar || mRefVAR
    }
    */

    return (*this);
}

MessageHandler::MessageHandler(const MessageHandler& rCopy)
    : _FD(0)
    , _pDB(NULL)
{
    cerr<<"error: never works"<<endl;
    (void)rCopy;
}



//****************************************************************************/
//Exception ******************************************************************/
    //PUBLIC:

    //PRIVATE:



//****************************************************************************/
//Operator overload **********************************************************/
    //PUBLIC:

    //PRIVATE:



//****************************************************************************/
//Getter & Setter ************************************************************/
//STANDARD:	게터와 세터는 '최소한' 쌍을 이룬다.
//			자료형에 따라 그 이상일 수 있다.
//			그러나 둘 중 하나가 없는 경우, 명시적으로 표시한다.
//			예를 들어, const가 아님에도 setter가 없다면, 클래스 외부에서 변경이 없음을 안다.
    //PUBLIC:

    //PRIVATE:

    

//****************************************************************************/
//Behavior *******************************************************************/
    //PUBLIC:
void MessageHandler::run()
{
    cout<<"in MessageHandler::FD["<<_FD<<"]: "<<_BUFF<<endl;

    while (_BUFF.size())
    {
        // parse command
            // get a command line
        const size_t endOfPresentCMD = _BUFF.find("\r\n");
        string presentCMD;

        if (endOfPresentCMD == _BUFF.npos)
        {
            return ;
        }

        presentCMD = _BUFF.substr(0, endOfPresentCMD);
        _BUFF.erase(0, endOfPresentCMD + 2);


            // parse string to s_Command
        s_Command command;
        vector<string> TMP;

        if (presentCMD[0] == ':')
        {
            const size_t endOfPrefix = presentCMD.find(' ');

            if (endOfPrefix == presentCMD.npos)
            {
                return ;
            }

            command.prefix = presentCMD.substr(1, endOfPrefix);
            presentCMD.erase(0, endOfPrefix + 1);
        }
        TMP = split(presentCMD, ':');
        if (TMP.size() != 1)
            command.suffix = TMP[1];
        TMP = split(TMP[0], ' ');
        command.command = TMP[0];
        for (size_t i = 0; i < command.command.size(); ++i)
        {
            command.command[i] = toupper(command.command[i]);
        }
        TMP.erase(TMP.begin());
        command.parameters = TMP;
{//TEST CODE
    // cout<<"[prefix]: "<<command.prefix<<endl;
    cout<<"[command]: "<<command.command<<endl;
    // cout<<"[params]"<<endl;
    // for (size_t i = 0; i < command.parameters.size(); ++i)
    //     cout<<"    ("<<i<<"): "<<command.parameters[i]<<endl;
    // cout<<"[suffix]: "<<command.suffix<<endl<<endl;
}
    User *user = _pDB->searchUser(_FD); // 유저가 존재하는지, 유저 정보변경등에 사용
    bool disconnect = 0; // while문 break되야 하는지 판단하는 플래그














        if (command.command == "CAP")
        {
            CAP(command, user);
        }
        else if (user != NULL) // CAP이 된 상태 
        {
            if (command.command == "PRIVMSG")
            {
                PRIVMSG(command, user);
            }
            else if (command.command == "PING")
            {
                PING(command, user);
            }
            // else if (command.command == "NOTICE")
            // {
            //     NOTICE(command, user);
            // }
            else if (command.command == "JOIN")
            {
                JOIN(command, user);
            }
            else if (command.command == "PART")
            {

            }
            else if (command.command == "TOPIC")
            {
                TOPIC(command, user);
            }
            else if (command.command == "MODE")
            {
                MODE(command, user);
            }
            else if (command.command == "INVITE")
            {

            }
            else if (command.command == "KICK")
            {

            }
            else if (command.command == "PASS")
            {
                PASS(command, user);
            }
            else if (command.command == "NICK")
            {
                NICK(command, user);
            }
            else if (command.command == "USER")
            {
                USER(command, user);
            }
            else if (command.command == "QUIT")
            {
                QUIT(command, user);
            }
            else if (command.command == "KILL")
            {

            }
            else
            {

            }
            if (disconnect == 1)
            {
                // 연결 종료 
            }
        }
    }
}


    //PRIVATE:
vector<string> MessageHandler::split(const string& STR, char DL)
{
    const size_t FIRST_CAPACITY = 5;
    istringstream ISS(STR);
    string BUFF;
    vector<string> RET;
 
    RET.reserve(FIRST_CAPACITY);

    while (getline(ISS, BUFF, DL))
    {
        RET.push_back(BUFF);
    }
 
    return (RET);
}

void MessageHandler::multicast(vector<string> NICKs, string STR)
{
    for (size_t i = 0; i < NICKs.size(); ++i)
    {
        send(_pDB->searchUser(NICKs[i])->getFD(), STR.c_str(), STR.size(), 0);
    }
}


void MessageHandler::CAP(s_Command CMD, User *user)
{
            // _FD에 해당하는 유저가 없는지 확인
            (void)CMD;
            if (user == NULL)
            {
                string tmp = "default";
                // _FD를 제외하고 기본값만을 가진 user를 만든다.
                _pDB->addUserAtPairVec(_FD,tmp, tmp, tmp, tmp, tmp, 0,0,0,0,0,0);
            }
}


void MessageHandler::NICK(s_Command CMD, User *user)
{
    string msg;

    if (user->getBoolAuthority() == 0)
    {
        msg = COL + Server::Host + SPACE + ERR_NOTREGISTERED + SPACE + AST + SPACE + CMD.command + ERR_NOTREGISTERED_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);
        return ;
    }

    if (CMD.parameters.size() < 1)
    {
        msg = COL + Server::Host + SPACE + ERR_NEEDMOREPARAMS + SPACE + CMD.command + ERR_NEEDMOREPARAMS_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);                //send message , ERR_NEEDMOREPARAMS (461)
    }
    else 
    {
        string tmpNickname = CMD.parameters[0];
        string originNickname = user->getNickname();
        if (tmpNickname.length() == 0) // ERR_NONICKNAMEGIVEN 
        {
            msg = COL + Server::Host + SPACE + ERR_NONICKNAMEGIVEN + ERR_NONICKNAMEGIVEN_MSG + ENDL;
            send(_FD, msg.c_str(), msg.size(), 0);
        }
        else if (tmpNickname.compare("default") == 0 || tmpNickname.length() > 9) // 닉네임 길이 제한   
        {
            msg = COL + Server::Host + SPACE + ERR_ERRONEUSNICKNAME + SPACE + tmpNickname + ERR_ERRONEUSNICKNAME_MSG + ENDL;
            send(_FD, msg.c_str(), msg.size(), 0);

            cout << "nickbad " << endl;
        }
        else if (_pDB->searchUser(tmpNickname) != 0) // 중복 닉이 있다면
        {
            msg = COL + Server::Host + SPACE + ERR_NICKNAMEINUSE + SPACE + AST + SPACE + tmpNickname + ERR_NICKNAMEINUSE_MSG + ENDL;
            send(_FD, msg.c_str(), msg.size(), 0);
        }
        else // 정상 작동 
        {
            msg = COL + originNickname + SPACE + CMD.command + SPACE + COL + tmpNickname + ENDL;
            user->setNickname(tmpNickname);
            send(_FD, msg.c_str(), msg.size(), 0);


            cout << "nickgood" << endl;
        }
    } 
}


void MessageHandler::USER(s_Command CMD, User *user)
{
    string msg;
    if (user->getBoolAuthority() == 0)
    {
        msg = COL + Server::Host + SPACE + ERR_NOTREGISTERED + SPACE + AST + SPACE + CMD.command + ERR_NOTREGISTERED_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);
        return ;
    }
    
    if (CMD.parameters.size() != 3)
    {
        msg = COL + Server::Host + SPACE + ERR_NEEDMOREPARAMS + SPACE + CMD.command + ERR_NEEDMOREPARAMS_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);                //send message , ERR_NEEDMOREPARAMS (461)
    }
    else
    {
        string tmpUsername = CMD.parameters[0];
        if (user->getUsername().compare("default") != 0) // 이미 auth 된 유저이면서 초기설정을 이미 한 경우
        {
            msg = COL + Server::Host + SPACE + ERR_ALREADYREGISTERED + SPACE + user->getNickname() + SPACE + CMD.command + ERR_ALREADYREGISTERED_MSG + ENDL;
            send(_FD, msg.c_str(), msg.size(), 0);
        }
        else if (tmpUsername.length() == 0)
        {
            msg = COL + Server::Host + SPACE + ERR_NEEDMOREPARAMS + SPACE + CMD.command + ERR_NEEDMOREPARAMS_MSG + ENDL;
            send(_FD, msg.c_str(), msg.size(), 0); 
        } 
        else
        {
            user->setUsername(tmpUsername);
            if (CMD.suffix.length())
                user->setRealname(CMD.suffix);
            string welcome = " :Welcome to ft_irc! ";
            msg = COL + Server::Host + SPACE + RPL_WELCOME + SPACE + user->getNickname() + welcome + tmpUsername + ENDL;
            send(_FD, msg.c_str(), msg.size(), 0); 
            cout << welcome << endl;
        }
    }
}


void MessageHandler::PASS(s_Command CMD, User *user)
{
    string msg;

    if (user->getBoolAuthority())
        return ;
    if (CMD.parameters.size() < 1) // 인자 부족
    {
        msg = COL + Server::Host + SPACE + ERR_NEEDMOREPARAMS + SPACE + CMD.command + ERR_NEEDMOREPARAMS_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);
        int fd = _FD;
        _pDB->clearUserAtDatabase(fd);
    }
    else if (Server::ServPWD.compare(CMD.parameters[0]) != 0) // 비밀번호 다를때 
    {
        msg = COL + Server::Host + SPACE + ERR_PASSWDMISMATCH + SPACE + CMD.command + ERR_PASSWDMISMATCH_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);
        int fd = _FD;
        _pDB->clearUserAtDatabase(fd);
    }
    else // 비밀번호 맞을떄
    {
        bool auth = 1;
        cout<< "good" << endl;
        user->setBoolAuthority(auth);
    } 
}


void MessageHandler::MODE(s_Command CMD, User *user)
{
    if (!(user->getBoolAuthority()))
        return; 

    string msg;

    if (CMD.parameters.size() < 1)
    {
        msg = COL + Server::Host + SPACE + ERR_NEEDMOREPARAMS + SPACE + CMD.command + ERR_NEEDMOREPARAMS_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);
    }
    else
    {
        string target = CMD.parameters[0];
        if (target[0] == '#') //channel
        {
            // 채널 있는지 -> 채널 어드민인지 순서대로 확인 필 
        }
        else if (target[0] != '#') //user 
        {
            if (_pDB->searchUser(target) == 0)
            {
                msg = COL + Server::Host + SPACE + ERR_NOSUCHNICK + SPACE + target + ERR_NOSUCHNICK_MSG + ENDL;
                send(_FD, msg.c_str(), msg.size(), 0);
            }
            // Usermode 는 ft_irc에서 요구 X이지만 혹시 request 됐을경우 default인 RPL_UMODEIS (221)의 +i 를 넣어줌 
            else 
            {
                string inv_mode = "+i";
                msg = COL + Server::Host + SPACE + RPL_UMODEIS + SPACE + target + SPACE + COL + inv_mode + ENDL;
                send(_FD, msg.c_str(), msg.size(), 0);
                
                cout << "MODE USER OK " << endl;
            }
        }
    }
}


void MessageHandler::JOIN(s_Command CMD, User *user)
{
    string msg;
    if (user->getBoolAuthority() == 0)
    {
        msg = COL + Server::Host + SPACE + ERR_NOTREGISTERED + SPACE + AST + SPACE + CMD.command + ERR_NOTREGISTERED_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);
        return ;
    }
    if (CMD.parameters.size() < 1)
    {
        msg = COL + Server::Host + SPACE + ERR_NEEDMOREPARAMS + SPACE + CMD.command + ERR_NEEDMOREPARAMS_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);                    
        return ;
    }
    else
    {
        vector<string>channels = split(CMD.parameters[0],',');
        vector<string>keylist;

        if (CMD.parameters.size() > 1) // 키 까지 주어졌을경우
        {
            vector<string>keylist = split(CMD.parameters[1],','); // JOIN test1,test2,test3 123 처럼 들어오면 클라이언트에서 123,x,x로 바꿔줘서 들어오기 때문에 두 벡터의 size는 같을것임
            while (channels.size() > keylist.size()) // 혹시 모를 index out of range 방지 
                keylist.push_back("x");
        }
        for (size_t i = 0; i < channels.size(); ++i)
        {
            int FD = _FD;
            string channel_name = channels[i];
            string user_nick = user->getNickname();
            string user_real = user->getRealname();
            string msg; 
            if (!channel_name.empty())
            {
                if (channels[i][0] == '#') // '#' 제거 
                {
                    channel_name = channel_name.substr(1);
                }
                Channel *CHANNEL = _pDB->searchChannel(channel_name);

                if (CHANNEL == NULL) // 채널이 없는 경우 
                {   
                    string topic_tmp = ""; // 기본값 "" 라고 명시 되어있음

                    ChannelMode CM;
                    CM.bO = 0;
                    CM.bP = 0;
                    CM.bS = 0;
                    CM.bI = 0;
                    CM.bT = 0;
                    CM.bN = 0;
                    CM.bM = 0;
                    CM.bL = 0;
                    CM.bB = 0;
                    CM.bK = 0;
                    CM.userLimit = -1;
                    CM.channelkey = "";
                    _pDB->createChannelAtDatabase(user, channel_name, topic_tmp, CM);
                    user->setCurrentChannel(channel_name);
                    msg = COL + user_nick + SPACE + CMD.command + SPACE + HASH + channel_name + AST + SPACE + COL + user_real + ENDL;
                    send(_FD, msg.c_str(), msg.size(), 0);  
                }
                else // 
                {
                    if (_pDB->isUserAtChannel(channel_name, user_nick) != 0) // 채널 명단에 이미 있는 경우
                    {
                        user->setCurrentChannel(channel_name); // tcp 통신없음.. 아마 클라이언트단에서 서버스위칭 해주는거같음 
                    }
                    else
                    {
                        if (CHANNEL->getChannelMode().channelkey != "") // 비밀번호가 있는 채널일 경우 (op이 /mode #<channel> +k <key> 했을때)
                        {   
                            if (CMD.parameters.size() == 1 || (CMD.parameters.size() > 1 && CHANNEL->getChannelMode().channelkey != keylist[i])) // key 인자가 없거나 있는데 틀렸을경우
                            {
                                msg = COL + Server::Host + SPACE + ERR_BADCHANNELKEY + SPACE + user_nick + SPACE + HASH + channel_name + SPACE + ERR_BADCHANNELKEY + ENDL;
                                send(_FD, msg.c_str(), msg.size(), 0);                         
                            }
                            if ((CMD.parameters.size() > 1 && CHANNEL->getChannelMode().channelkey == keylist[i])) // key를 맞췄을 경우
                            {
                                if (CHANNEL->getChannelMode().bI == 1) // 비밀번호 맞는데 invite only 일경우 
                                {
                                    msg = COL + Server::Host + SPACE + ERR_INVITEONLYCHAN + SPACE + user_nick + SPACE + HASH + channel_name + SPACE + ERR_INVITEONLYCHAN_MSG + ENDL;
                                    send(_FD, msg.c_str(), msg.size(), 0); 
                                }
                                else if (CHANNEL->getChannelMode().userLimit != -1 && static_cast<int>(_pDB->getUsersAtChannel(channel_name).size()) >= CHANNEL->getChannelMode().userLimit) // 유저 리밋이 걸려있을경우 자리가 없을때
                                {   
                                    msg = COL + Server::Host + SPACE + ERR_CHANNELISFULL + SPACE + user_nick + SPACE + HASH + channel_name + SPACE + ERR_CHANNELISFULL_MSG + ENDL;
                                    send(_FD, msg.c_str(), msg.size(), 0);                                     
                                }
                                else
                                {
                                    _pDB->joinChannel(FD,channel_name);
                                    user->setCurrentChannel(channel_name);
                                    msg = COL + user_nick + SPACE + CMD.command + SPACE + HASH + channel_name + AST + SPACE + COL + user_real + ENDL;
                                    send(_FD, msg.c_str(), msg.size(), 0);  
                                    // join -> 353 -> 366 은 /names 이기 때문에 구현 x 
                                }
                            }
                        }
                        else if (CHANNEL->getChannelMode().bI == 1) // invite only라서 못들어갈때
                        {
                            msg = COL + Server::Host + SPACE + ERR_INVITEONLYCHAN + SPACE + user_nick + SPACE + HASH + channel_name + SPACE + ERR_INVITEONLYCHAN_MSG + ENDL;
                            send(_FD, msg.c_str(), msg.size(), 0); 
                        }
                        else
                        {
                            if (CHANNEL->getChannelMode().userLimit != -1 && static_cast<int>(_pDB->getUsersAtChannel(channel_name).size()) >= CHANNEL->getChannelMode().userLimit) // 유저 리밋이 걸려있을경우 자리가 없을 때
                            {   
                                msg = COL + Server::Host + SPACE + ERR_CHANNELISFULL + SPACE + user_nick + SPACE + HASH + channel_name + SPACE + ERR_CHANNELISFULL_MSG + ENDL;
                                send(_FD, msg.c_str(), msg.size(), 0);                                     
                            }
                            else
                            {
                                _pDB->joinChannel(FD,channel_name);
                                user->setCurrentChannel(channel_name);
                                msg = COL + user_nick + SPACE + CMD.command + SPACE + HASH + channel_name + AST + SPACE + COL + user_real + ENDL;
                                send(_FD, msg.c_str(), msg.size(), 0);  
                                // join -> 353 -> 366
                            }
                        }
                    }
                }
            }
        }
    }
}


void MessageHandler::TOPIC(s_Command CMD, User *user)
{
    string msg;
    if (user->getBoolAuthority() == 0)
    {
        msg = COL + Server::Host + SPACE + ERR_NOTREGISTERED + SPACE + AST + SPACE + CMD.command + ERR_NOTREGISTERED_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);
        return ;
    }

    if (CMD.parameters.size() < 1)
    {
        msg = COL + Server::Host + SPACE + ERR_NEEDMOREPARAMS + SPACE + CMD.command + ERR_NEEDMOREPARAMS_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);
        return ;              
    }

    string nickname = user->getNickname();
    string channelname = CMD.parameters[0]; //클라이언트에서 자동으로 해쉬 붙혀줌
    if (channelname[0] == '#') // '#' 제거 
    {
        channelname = channelname.substr(1);
    }  
    int auth = _pDB->isUserAtChannel(channelname, nickname);
    Channel* channel = _pDB->searchChannel(channelname);


    //DEBUG
    cout << "param cnt" << CMD.parameters.size() << endl;
    if (channel != NULL)
        cout << "channel topic" <<  channel->getTopic() << endl;
    cout << CMD.suffix.empty() << endl;

    if (channel == NULL) //채널이 없을경우
    {
        msg = COL + Server::Host + SPACE + ERR_NOSUCHCHANNEL + SPACE + channelname + ERR_NOSUCHCHANNEL_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0); 
    }
    else if (auth == 0) // 자신이 속한 채널이 아닌데 조회하려고 할 경우
    {
        msg = COL + Server::Host + SPACE + ERR_NOTONCHANNEL + SPACE + channelname + ERR_NOTONCHANNEL_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0); 
        cout << "no auth?" << endl;
    }
    else if (CMD.parameters.size() == 1  && CMD.suffix.empty()) // channel의 topic 조회
    {
        if (channel->getChannelMode().bT && auth == 1) // 채널 mode +t이면서 권한 없을 시 
        {
            msg = COL + Server::Host + SPACE + ERR_CHANOPRIVSNEEDED  + SPACE + channelname + ERR_CHANOPRIVSNEEDED_MSG + ENDL;
            send(_FD, msg.c_str(), msg.size(), 0);  
        }
        else 
        {
            if (channel->getTopic() == "") // 토픽이 없을경우
            {   
                string RPL_TOPIC_MSG = " :No topic is set";
                msg = COL + Server::Host + SPACE + RPL_NOTOPIC + SPACE + nickname + SPACE + channelname + RPL_TOPIC_MSG + ENDL;
                send(_FD, msg.c_str(), msg.size(), 0);  
            }
            else // 토픽이 있을경우
            {
                msg = COL + Server::Host + SPACE + RPL_TOPIC + SPACE + nickname + SPACE + channelname + SPACE + COL + channel->getTopic() + ENDL; 
                send(_FD, msg.c_str(), msg.size(), 0);  
            }
        }
    }
    else if (CMD.parameters.size() == 1 && !(CMD.suffix.empty())) // channel의 topic 변경
    {
        cout << "HERE" << endl;
        if (channel->getChannelMode().bT && auth == 1) // 채널 mode +t이면서 권한 없을 시 
        {
            msg = COL + Server::Host + SPACE + ERR_CHANOPRIVSNEEDED  + SPACE + channelname + ERR_CHANOPRIVSNEEDED_MSG + ENDL;
            send(_FD, msg.c_str(), msg.size(), 0);  
        }
        else
        {
            vector<string>suf_split = split(CMD.suffix,' ');
            if (suf_split.size() > 1) // 클라이언트에서 서버이름에 #을 붙히면 suffix 그대로 오고, 안붙히면 suffix는 서버이름+topic으로 오기때문에 구분 
            {
                channel->setTopic(suf_split[1]);
                cout << suf_split[1] << "is topic!" << endl;
            }
            else
            {
                channel->setTopic(suf_split[0]);
                cout << suf_split[0] << "is topic!" << endl;
            }
            msg = COL + Server::Host + SPACE + RPL_TOPIC + SPACE + nickname + SPACE + channelname + SPACE + COL + channel->getTopic() + ENDL;  // tcpflow상으로 설정하고 끝이긴함.
            cout << msg << endl;
            send(_FD, msg.c_str(), msg.size(), 0);
        }
    }
}


void MessageHandler::PING(s_Command CMD, User *user)
{
    string msg;

    if (user->getBoolAuthority() == 0)
    {
        msg = COL + Server::Host + SPACE + ERR_NOTREGISTERED + SPACE + AST + SPACE + CMD.command + ERR_NOTREGISTERED_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);
        return ;
    }

    if (CMD.parameters.size() < 1)
    {
        msg = COL + Server::Host + SPACE + ERR_NEEDMOREPARAMS + SPACE + CMD.command + ERR_NEEDMOREPARAMS_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);                    
    }
    else if (CMD.parameters[0].length() == 0)
    {
        msg = COL + Server::Host + SPACE + ERR_NOORIGIN + SPACE + user->getUsername() + ERR_NOORIGIN_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);   
    }
    else
    {
        string PONG = "PONG";
        msg = COL + Server::Host + SPACE + PONG + SPACE + Server::Host + CMD.parameters[0] + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);   

        cout << "PONG SENTED!!" << endl;                   
    }
}


void MessageHandler::PRIVMSG(s_Command CMD, User* user)
{
    const size_t FIRST_CAPACITY = 5;
    vector<string> receiver;
    string msg;

    receiver.reserve(FIRST_CAPACITY);
{   //check error before try send to receiver & parse receiver
    if (user->getBoolAuthority() == 0)
    {
        msg = COL + Server::Host + SPACE + ERR_NOTREGISTERED + SPACE + AST + SPACE + CMD.command + ERR_NOTREGISTERED_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);

        return ;
    }

    //ERR_NORECIPIENT to sender
    if (CMD.parameters.size() == 0)
    {
        msg = COL + Server::Host + SPACE + ERR_NORECIPIENT + SPACE + user->getNickname() + ERR_NORECIPIENT_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);

        return ;
    }

    //ERR_NOTEXTTOSEND to sender
    if (CMD.suffix.size() == 0)
    {
        msg = COL + Server::Host + SPACE + ERR_NOTEXTTOSEND + SPACE + user->getNickname() + ERR_NOTEXTTOSEND_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);

        return ;
    }

    receiver = split(CMD.parameters[0], ',');

    for (size_t i = 0; i < receiver.size(); ++i)
    {
        for (size_t j = 0; j < receiver.size(); ++j)
        {
            //ERR_TOOMANYTARGETS to sender
            if (i != j && receiver[i] == receiver[j])
            {
                msg = COL + Server::Host + SPACE + ERR_TOOMANYTARGETS + SPACE + user->getNickname() + SPACE + receiver[i] + ERR_TOOMANYTARGETS_MSG + ENDL;
                send(_FD, msg.c_str(), msg.size(), 0);

                return ;
            }
        }
    }
}
{   // send msg with checking err send to user
    const int FIRST_CAPACITY = 15;
    string PRIVMSG = "PRIVMSG";

    for (size_t i = 0; i < receiver.size(); ++i)
    {
        if (receiver[i][0] == '&' || receiver[i][0] == '#') // to channel
        {
            Channel* pChannel = NULL;
            vector<string> chanReceivers;

            chanReceivers.resize(FIRST_CAPACITY);

            receiver[i].erase(0, 1);
            pChannel = _pDB->searchChannel(receiver[i]);
            
            // ERR_CANNOTSENDTOCHAN
            if (pChannel == NULL || _pDB->searchUser(_FD) == NULL)
            {
                msg = COL + Server::Host + SPACE + ERR_CANNOTSENDTOCHAN + SPACE + user->getNickname() + SPACE + HASH + receiver[i] + ERR_CANNOTSENDTOCHAN_MSG + ENDL;
                send(_FD, msg.c_str(), msg.size(), 0);

                msg.clear();

                continue ;
            }

            msg = COL + user->getNickname() + EXCL + user->getUsername() + AT + Server::Host + SPACE + PRIVMSG + SPACE + HASH + receiver[i] + SPACE + COL + CMD.suffix + ENDL;

            chanReceivers = _pDB->getUsersAtChannel(receiver[i]);
            vector<string>::iterator iter = chanReceivers.begin();

            for (; iter != chanReceivers.end(); ++iter)
            {
                if (*iter == _pDB->searchUser(_FD)->getNickname())
                {
                    chanReceivers.erase(iter);

                    break ;
                }
            }

            multicast(chanReceivers, msg);

            msg.clear();
        }
        else // to user
        {
            User* pUser = NULL;

            pUser = _pDB->searchUser(receiver[i]);

            //ERR_NOSUCHNICK
            if (pUser == NULL)
            {
                msg = COL + Server::Host + SPACE + ERR_NOSUCHNICK + SPACE + user->getNickname() + SPACE + receiver[i] + ERR_NOSUCHNICK_MSG + ENDL;
                send(_FD, msg.c_str(), msg.size(), 0);

                msg.clear();

                continue ;
            }

            msg = COL + user->getNickname() + EXCL + user->getUsername() + AT + Server::Host + SPACE + PRIVMSG + SPACE + receiver[i] + SPACE + COL + CMD.suffix + ENDL;
            send(pUser->getFD(), msg.c_str(), msg.size(), 0);

            msg.clear();
        }
    }    
}
}

void MessageHandler::QUIT(s_Command CMD, User* user)
{
    string msg;
    string QUIT = "QUIT";
    string reason = "Client Quit";
{ // check auth
    if (user->getBoolAuthority() == 0)
    {
        msg = COL + Server::Host + SPACE + ERR_NOTREGISTERED + SPACE + AST + SPACE + CMD.command + ERR_NOTREGISTERED_MSG + ENDL;
        send(_FD, msg.c_str(), msg.size(), 0);

        return ;
    }
}
{ // make msg to sending users(requirer & the users of in-channel with requirer)
    if (CMD.suffix.size())
    {
        reason = CMD.suffix;
    }

    msg = COL + user->getNickname() + EXCL + user->getUsername() + AT + Server::Host + SPACE + QUIT + SPACE + COL + reason + ENDL;
}
{ // send to requirer
    send(_FD, msg.c_str(), msg.size(), 0);
}
{ // find channels the quit-requirer is being & send
    const int FIRST_CAPACITY_OF_CHAN = 5;
    const int FIRST_CAPACITY_OF_RECVS = 15;
    vector<string> quitUserChannels;
    vector<string> chanReceivers;

    quitUserChannels.reserve(FIRST_CAPACITY_OF_CHAN);
    chanReceivers.reserve(FIRST_CAPACITY_OF_RECVS);

    quitUserChannels = _pDB->getChannelsWithUser(user->getNickname());

    for (size_t i = 0; i < quitUserChannels.size(); ++i)
    {
        chanReceivers = _pDB->getUsersAtChannel(quitUserChannels[i]);
        vector<string>::iterator iter = chanReceivers.begin();

        for (; iter != chanReceivers.end(); ++iter)
        {
            if (*iter == _pDB->searchUser(_FD)->getNickname())
            {
                chanReceivers.erase(iter);

                break ;
            }
        }

        multicast(chanReceivers, msg);
    }
}
{ // do removing user process at the server
    vector<pollfd>::iterator iter = (*_pPFDS).begin();

    cout<<"[-] fd: "<<_FD<<": disconnected!(QUIT)"<<endl;
std::cout<<"OUT OF (QUIT)1"<<std::endl;
    _pDB->clearUserAtDatabase(_FD);
std::cout<<"OUT OF (QUIT)2"<<std::endl;
    for (; iter != (*_pPFDS).end(); ++iter)
    {
        if ((*iter).fd == _FD)
        {
            (*_pPFDS).erase(iter);
            if (iter == (*_pPFDS).end())
                break ;
        }
    }
std::cout<<"OUT OF (QUIT)3"<<std::endl;
    //remove at _PDFS && "[-] fd msg"
}
}
//****************************************************************************/
//GLOBAL FUNCTION ************************************************************/