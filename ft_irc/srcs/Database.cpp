#include "../includes/Database.hpp"

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
Database::Database()
{
    const size_t FIRST_CAPACITY = 50;

    _users.reserve(FIRST_CAPACITY);
    _users.reserve(FIRST_CAPACITY);
    _channelUserTable.reserve(FIRST_CAPACITY);
    _MSGs.reserve(FIRST_CAPACITY);
}

Database::~Database()
{
    _users.clear();
    UserPairVector().swap(_users);

    _channels.clear();
    ChannelPairVector().swap(_channels);

    _channelUserTable.clear();
    ChannelUserTable().swap(_channelUserTable);
}

    //PRIVATE:
Database& Database::operator=(const Database& rRhs)
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

Database::Database(const Database& rCopy)
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
void Database::clearDatabase()
{
    for (size_t i = 0; i < _users.size(); ++i)
    {
        close(_users[i]->first);
        _users[i]->first = -1;
        delete _users[i]->second;
        _users[i]->second = NULL;
        delete _users[i];
    }
    for (size_t i = 0; i < _channels.size(); ++i)
    {
        _channels[i]->first.clear();
        delete _channels[i]->second;
        _channels[i]->second = NULL;
        delete _channels[i];
    }
    for (size_t i = 0; i < _channelUserTable.size(); ++i)
    {
        _channelUserTable[i]->_pUserPair = NULL;
        _channelUserTable[i]->_pChannelPair = NULL;
        _channelUserTable[i]->_bOP = false;
        delete _channelUserTable[i];
    }
}





void Database::addUserAtPairVec(int FD, 
                                string realname, \
                                string nickname, \
                                string username, \
                                string host, \
                                bool bAUTH)
{
    UserPair* tmp = new UserPair;

    tmp->first = FD;
    tmp->second = new User(FD, realname, nickname, username, host, bAUTH);

    _users.push_back(tmp);
}






void Database::clearUserAtDatabase(int FD)
{
{   // remove channel-user info in ChannelUserTable
    vector<s_ChannelUserNode* >::iterator iter = _channelUserTable.begin();

    while (true)
    {
        if (iter == _channelUserTable.end())
        {
            break ;
        }
        else if ((*iter)->_pUserPair->first == FD)
        {
            delete (*iter);
            _channelUserTable.erase(iter);
            continue ;
        }
        else
        {
            ++iter;
        }
    }
}
{   // remove userPair in _users (delete User class)
    UserPairVector::iterator iter = _users.begin();

    while (true)
    {
        if (iter == _users.end())
        {
            break ;
        }
        else if ((*iter)->first == FD)
        {
            close((*iter)->first);
            delete (*iter)->second;
            delete (*iter);
            _users.erase(iter);

            break ;
        }
        else
        {
            ++iter;
        }
    }
}
{ // if Channel is not needed, then remove chanPair in _channels
    ChannelPairVector::iterator iter = _channels.begin();

    while (true)
    {
        if (iter == _channels.end())
        {
            break ;
        }
        else if (getUsersAtChannel((*iter)->first).size() == 0)
        {
            delete (*iter)->second;
            delete (*iter);
            _channels.erase(iter);

            break ;
        }
        else
        {
            ++iter;
        }
    }
}
{ // delete User`s MessageHandler
    delete _MSGs[FD];
    _MSGs[FD] = NULL;
}
}





void Database::createChannelAtDatabase(User* pMaker, \
                                        string name, \
                                        string topic, \
                                        s_ChannelMode mode)
{
    ChannelPair* tmp = new ChannelPair;

    tmp->first = name;
    tmp->second = new Channel(name, topic, mode);
    _channels.push_back(tmp);
    joinChannel(pMaker->getFD(), name, true);
}





void Database::clearChannelAtDatabase(string& name)
{
{   // remove channel-user info in ChannelUserTable
    vector<s_ChannelUserNode* >::iterator iter = _channelUserTable.begin();

    while (true)
    {
        if (iter == _channelUserTable.end())
        {
            break ;
        }
        else if ((*iter)->_pChannelPair->first == name)
        {
            delete (*iter);
            _channelUserTable.erase(iter);
            continue ;
        }
        else
        {
            ++iter;
        }
    }
}
{   // remove channelPair in _channels (delete Channel class)
    ChannelPairVector::iterator iter = _channels.begin();

    while (true)
    {
        if (iter == _channels.end())
        {
            break ;
        }
        else if ((*iter)->first == name)
        {
            delete (*iter)->second;
            delete (*iter);
            _channels.erase(iter);
            break ;
        }
        else
        {
            ++iter;
        }
    }
}
}





void Database::joinChannel(int FD, string chanName, bool is_op)
{
    s_ChannelUserNode* tmp = new s_ChannelUserNode;

    for (size_t i = 0; i < _users.size(); ++i)
    {
        if (_users[i]->first == FD)
        {
            tmp->_pUserPair = _users[i];

            break ;
        }
    }
    for (size_t i = 0; i < _channels.size(); ++i)
    {
        if (_channels[i]->first == chanName)
        {
            tmp->_pChannelPair = _channels[i];

            break ;
        }
    }
    tmp->_bOP = is_op;
    cout << is_op << " is user op!! " << endl << endl;
    _channelUserTable.push_back(tmp);
}





void Database::leaveChannel(int& FD, string& chanName)
{
    vector<s_ChannelUserNode* >::iterator iter = _channelUserTable.begin();

    for (; iter != _channelUserTable.end(); ++iter)
    {
        if ((*iter)->_pUserPair->first == FD && \
            (*iter)->_pChannelPair->first == chanName)
        {
            delete (*iter);
            _channelUserTable.erase(iter);

            break ;
        }
    }
}





eIsUserAtChannel Database::isUserAtChannel(string& chanName, \
                                            string& userNick)
{
    vector<s_ChannelUserNode* >::iterator iter = _channelUserTable.begin();

    for (; iter != _channelUserTable.end(); ++iter)
    {
        if ((*iter)->_pChannelPair->first == chanName && \
            (*iter)->_pUserPair->second->getNickname() == userNick)
        {
            if ((*iter)->_bOP)
            {
                return (IS_USER_OP);
            }
            else
            {
                return (IS_USER_NOT_OP);
            }
        }
    }
    return (NO_USER);
}





User* Database::searchUser(string& nickname)
{
    for (size_t i = 0; i < _users.size(); ++i)
    {
        if (_users[i]->second->getNickname() == nickname)
            return (_users[i]->second);
    }

    return (NULL);
}





User *Database::searchUser(const int &FD)
{
    for (size_t i = 0; i < _users.size(); ++i)
    {
        if (_users[i]->first == FD)
            return (_users[i]->second);
    }
    
    return (NULL);
}





Channel* Database::searchChannel(string& chanName)
{
    for (size_t i = 0; i < _channels.size(); ++i)
    {
        if (_channels[i]->second->getName() == chanName)
            return (_channels[i]->second);
    }

    return (NULL);
}





vector<string> Database::getUsersAtChannel(string &chanName)
{
    vector<string> users;
    for (size_t i = 0; i < _channelUserTable.size(); ++i)
    {
        if (_channelUserTable[i]->_pChannelPair->first == chanName)
        {
            users.push_back(_channelUserTable[i]->_pUserPair->second->getNickname());
        }
    }
    return users;
}





vector<string> Database::getChannelsWithUser(string userName)
{
    const int FIRST_CAPACITY = 5;
    vector<string> channels;

    channels.reserve(FIRST_CAPACITY);

    for (size_t i = 0; i < _channelUserTable.size(); ++i)
    {
        if (_channelUserTable[i]->_pUserPair->second->getNickname() == userName)
        {
            channels.push_back(_channelUserTable[i]->_pChannelPair->first);
        }
    }

    return (channels);
}

    //PRIVATE:

//BY geonlee

vector<int> Database::getFdsAtChannel(string chanName)
{
    vector<int> fds;
    for (size_t i = 0; i < _channelUserTable.size(); ++i)
    {
        if (_channelUserTable[i]->_pChannelPair->first == chanName)
        {
            fds.push_back(_channelUserTable[i]->_pUserPair->second->getFD());
        }
    }
    return fds;
}

void Database::changeUserOPAtDatabase(string chanName, string userNick, bool is_op)
{
    vector<s_ChannelUserNode* >::iterator iter = _channelUserTable.begin();

    for (; iter != _channelUserTable.end(); ++iter)
    {
        if ((*iter)->_pChannelPair->first == chanName && \
            (*iter)->_pUserPair->second->getNickname() == userNick)
        {
            (*iter)->_bOP = is_op;
        }
    }
    return ;
}





void Database::createMessageHandler(int FD, string BUFF, Database * const pDB, vector<pollfd>* pPFDS)
{
    (void)FD;
    (void)BUFF;
    (void)pDB;
    (void)pPFDS;









}





MessageHandler* Database::searchMessageHandler(int FD)
{
    (void)FD;


    return (NULL);
}

//****************************************************************************/
//GLOBAL FUNCTION ************************************************************/


//TESTCODE
void Database::printAllChannalPair()
{
    cout<<"_channels size: "<<_channels.size()<<endl;
    for (size_t i = 0; i < _channels.size(); ++i)
    {
        cout<<"first: "<<_channels[i]->first<<"    "<<"second: "<<_channels[i]->second->getName()<<endl;
    }
    cout<<endl;
}

void Database::printAllUserPair()
{
    cout<<"_users size: "<<_users.size()<<endl;
    for (size_t i = 0; i < _users.size(); ++i)
    {
        cout<<"first: "<<_users[i]->first<<"    "<<"second: "<<_users[i]->second->getNickname()<<endl;
    }
    cout<<endl;
}

void Database::printAllTable()
{
    cout<<"table size: "<<_channelUserTable.size()<<endl;
    for (size_t i = 0; i < _channelUserTable.size(); ++i)
    {
        cout<<"user: "<<_channelUserTable[i]->_pUserPair->first<<_channelUserTable[i]->_pUserPair->second->getNickname()<<endl;
        cout<<"channels: "<<_channelUserTable[i]->_pChannelPair->first<<" "<<_channelUserTable[i]->_pChannelPair->second->getName()<<endl;
    }
    cout<<endl;
}

