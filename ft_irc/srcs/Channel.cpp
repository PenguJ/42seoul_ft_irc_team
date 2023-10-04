#include "../includes/Channel.hpp"

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
Channel::Channel(string& name, string &topic, s_ChannelMode &mode)
    : _name(name)
    , _topic(topic)
    , _mode(mode)
{
	const int FIRST_CAPACITY = 10;

	_invites.reserve(FIRST_CAPACITY);
}

Channel::~Channel()
{	}

	//PRIVATE:
Channel::Channel()
{
	cerr<<"error: never works"<<endl;
}

Channel& Channel::operator=(const Channel& rRhs)
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

Channel::Channel(const Channel& rCopy)
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
const string Channel::getName() const
{
    return (_name);
}

void Channel::setName(string name)
{
    _name = name;
}

const string Channel::getTopic() const
{
    return (_topic);
}

void Channel::setTopic(string topic)
{
    _topic = topic;
}

s_ChannelMode Channel::getChannelMode() const
{
    return (_mode);
}

void Channel::setChannelMode(s_ChannelMode& mode)
{
    _mode = mode;
}

vector<string> Channel::getInvites() const
{
	return (_invites);
}

void Channel::setInvites(vector<string> invites)
{
	_invites = invites;
}


// BY geonlee
void Channel::setBP(bool value) { _mode.bP = value; }
void Channel::setBS(bool value) { _mode.bS = value; }
void Channel::setBI(bool value) { _mode.bI = value; }
void Channel::setBT(bool value) { _mode.bT = value; }
void Channel::setBN(bool value) { _mode.bN = value; }
void Channel::setBM(bool value) { _mode.bM = value; }
void Channel::setBL(bool value) { _mode.bL = value; }
void Channel::setBB(bool value) { _mode.bB = value; }
void Channel::setBV(bool value) { _mode.bV = value; }
void Channel::setBK(bool value) { _mode.bK = value; }
void Channel::setUserLimit(int value) { _mode.userLimit = value; }
void Channel::setChannelKey(const std::string& value) { _mode.channelkey = value; }

	//PRIVATE:

	

//****************************************************************************/
//Behavior *******************************************************************/
	//PUBLIC:

	//PRIVATE:



//****************************************************************************/
//GLOBAL FUNCTION ************************************************************/