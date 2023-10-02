//#pragma once
#ifndef DATABASE_HPP
# define DATABASE_HPP

using namespace std;

# include <unistd.h>
# include <iostream>
# include <vector>
# include "Channel.hpp"
# include "User.hpp"

typedef pair<int, User*>            UserPair;
typedef pair<string, Channel*>      ChannelPair;

typedef vector<UserPair*>            UserPairVector;
typedef vector<ChannelPair*>         ChannelPairVector;

typedef struct ChannelUserNode
{
    UserPair*       _pUserPair;
    ChannelPair*    _pChannelPair;
    bool            _bOP;
}	s_ChannelUserNode;

typedef vector<s_ChannelUserNode* > ChannelUserTable;

//STANDARD: 어떤 상수가 constexpr의 특징을 가지고 있고, 다른 클래스에서 그 값이 사용되는 경우에만
//				멤버변수를 public으로 선언할 수 있다.
//			반드시! 상속 여부를 체크한 뒤 클래스를 작성한다. (exception 상속은 제외)
//			이를 위해 최초 양식에는 주석이 없다.
// 			상속일 시, 메소드와 변수 모두 'protected:'를 명시적으로 나타낸다.(인터페이스인 경우 예외)
// 			상속일 시, 소멸자는 가상함수이다.
// 			상속일 시, 상위 클래스의 'protected:'멤버변수와 메소드를 주석으로 표현한다.
// 			이때 네임스페이스와 함께 명시한다.
// 			상속을 하거나, 받으면 해당 클래스를 들여쓰기로 한 줄씩 명시한다.
// is do inherit? (NO): is abstracted? (NO): is interface? (NO)
// is be inherited? (NO)

enum eIsUserAtChannel
{
    NO_USER,
    IS_USER_NOT_OP,
    IS_USER_OP
};

class Database
{
public:
    //Constructor overload & OCCF
    Database();
    ~Database();
    //Exception
    //Operator overload
    //Getter & Setter
    //Behavior
    void clearDatabase(); // DB clear before exit server
    void addUserAtPairVec(int FD, \
                            string realname, \
                            string nickname, \
                            string username, \
                            string PWD, \
                            string host, \
                            bool bI, \
                            bool bS, \
                            bool bW, \
                            bool bO, \
                            bool bAUTH, \
                            bool bPWD); // when user accepted at server, but not a channel
    void clearUserAtDatabase(int FD); // when user quit at server
    void createChannelAtDatabase(User* pMaker, \
                                    string name, \
                                    string topic, \
                                    s_ChannelMode mode); // when some user create a channel
    void clearChannelAtDatabase(string& name); // when last user leave a channel
    void joinChannel(int FD, string chanName); // when some user join channel already exist
    void leaveChannel(int& FD, string& chanName); // when some user leave channel already exist

    eIsUserAtChannel isUserAtChannel(string& chanName, string& userNick);
    User* searchUser(string& nickname);
    User* searchUser(const int &fd);
    Channel* searchChannel(string& chanName);
    vector<string>getUsersAtChannel(string &chanName);
    vector<string> getChannelsWithUser(string userName);

//TESTCODE
void printAllChannalPair();
void printAllUserPair();
void printAllTable();



private:
    //Constructor overload & OCCF
    Database& operator=(const Database& rRhs);
    Database(const Database& rCopy);
    //Exception
    //Operator overload
    //Getter & Setter
    //Behavior

private:
    UserPairVector      _users;
    ChannelPairVector   _channels;
    ChannelUserTable    _channelUserTable;
};

//GLOBAL FUNCTION for class Database{}

#endif
