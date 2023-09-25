//#pragma once
#ifndef DATABASE_HPP
# define DARABASE_HPP

# include <iostream>
# include <map>
# include <vector>
# include "Channel.hpp"
# include "User.hpp"

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

typedef struct ChannelUserNode
{
	std::map<std::string, Channel*>*    _channel;
	std::map<int, User*>*               _user;
	bool                                _bOP;
}	s_ChannelUserNode;

class Database
{
public:
	//Constructor overload & OCCF
	Database();
	~Database();
	Database& operator=(const Database& rRhs);
	Database(const Database& rCopy);
	//Exception
	//Operator overload
	//Getter & Setter
	//Behavior

private:
	//Constructor overload & OCCF
	//Exception
	//Operator overload
	//Getter & Setter
	//Behavior

private:
    std::map<int, User*>            _users;
    std::map<std::string, Channel*> _channels;
	std::vector<s_ChannelUserNode>  _ChannelUserTable;
};

//GLOBAL FUNCTION for class Database{}

#endif
