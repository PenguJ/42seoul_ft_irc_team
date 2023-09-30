#include "../includes/User.hpp"

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
User::User(int FD, std::string realname, std::string nickname, std::string username, std::string currentchannel, \
        std::string host, bool bI, bool bS, bool bW, bool bO, bool bAUTH, bool bPWD)
    : _FD(FD)
    , _realname(realname)
    , _nickname(nickname)
    , _username(username)
    , _currentchannel(currentchannel)
    , _host(host)
    , _bAUTH(bAUTH)
    , _bPWD(bPWD)
{   
    _mode.bI = bI;
    _mode.bS = bS;
    _mode.bW = bW;
    _mode.bO = bO;
}

User::~User()
{	}

    //PRIVATE:
User::User()
{
    std::cerr<<"error: never works"<<std::endl;
}

User& User::operator=(const User& rRhs)
{
    std::cerr<<"error: never works"<<std::endl;
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

User::User(const User& rCopy)
{
    std::cerr<<"error: never works"<<std::endl;
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
int User::getFD() const
{
    return (_FD);
}

const std::string User::getRealname() const
{
    return (_realname);
}

void User::setRealname(std::string& realname)
{
    _realname = realname;
}

const std::string User::getNickname() const
{
    return (_nickname);
}

void User::setNickname(std::string& nickname)
{
    _nickname = nickname;
}

const std::string User::getUsername() const
{
    return (_username);
}

void User::setUsername(std::string& username)
{
    _username = username;
}

const std::string User::getCurrentChannel() const
{
    return (_currentchannel);
}

void User::setCurrentChannel(std::string& channel)
{
    _currentchannel = channel;
}

const std::string User::getHost() const
{
    return (_host);
}

void User::setHost(std::string& host)
{
    _host = host;
}

s_UserMode User::getUserMode() const
{
    return (_mode);
}

void User::setUserMode(s_UserMode& mode)
{
    _mode = mode;
}

bool User::getBoolAuthority() const
{
    return (_bAUTH);
}

void User::setBoolAuthority(bool& bAUTH)
{
    _bAUTH = bAUTH;
}

bool User::getBoolPassword() const
{
    return (_bPWD);
}

void User::setBoolPassword(bool& bPWD)
{
    _bPWD = bPWD;
}


    //PRIVATE:

    

//****************************************************************************/
//Behavior *******************************************************************/
    //PUBLIC:

    //PRIVATE:



//****************************************************************************/
//GLOBAL FUNCTION ************************************************************/
