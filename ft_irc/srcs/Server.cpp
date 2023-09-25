#include "../includes/Server.hpp"

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
Server::Server(const u_int16_t &port, const std::string &PWD)
	: _servSock(-1)
	, _port(port)
	, _PWD(PWD)
{
	const u_int8_t FIRST_SERVER_CAPACITY= 255;

	_PFDS.reserve(FIRST_SERVER_CAPACITY);
}

Server::~Server()
{
	close(_servSock);
	_PFDS.clear();
	std::vector<pollfd>().swap(_PFDS);
}

	//PRIVATE:
Server::Server()
	: _port(0)
{
	std::cerr<<"error: never works"<<std::endl;
}

Server& Server::operator=(const Server& rRhs)
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

Server::Server(const Server& rCopy)
	: _port(0)
{
	(void)rCopy;
	std::cerr<<"error: never works"<<std::endl;
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
void Server::execute()
{
{	// Open server - Create server socket & Push Server socket to pollfds
{
	_servSock = socket(AF_INET, SOCK_STREAM, 0);
	if (_servSock < 0)
	{
		throw std::runtime_error("error: socket()");
	}
}
{
	int optval = 1;

	if (setsockopt(_servSock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
	{
		throw std::runtime_error("error: setsockopt()");
	}
}
{
	if (fcntl(_servSock, F_SETFL, O_NONBLOCK))
	{
		throw std::runtime_error("error: fcntl()");
	}
}
{
	SOCKADDR_IN servSockADDR;

	memset(&servSockADDR, 0, sizeof(SOCKADDR_IN));
	servSockADDR.sin_family = AF_INET;
	servSockADDR.sin_addr.s_addr = INADDR_ANY;
	servSockADDR.sin_port = htons(_port);
	if (bind(_servSock, (SOCKADDR*)&servSockADDR, sizeof(servSockADDR)) < 0)
	{
		throw std::runtime_error("error: bind()");
	}
}
{
	const int BACKLOG = 100;

	if (listen(_servSock, BACKLOG) < 0)
	{
		throw std::runtime_error("error: listen()");
	}
}
	pollfd serv = {_servSock, POLLIN, 0};

	_PFDS.push_back(serv);
	std::cout<<"[SERVER IS LISTENING...]"<<std::endl;
}
{	// Run IRC-server Process
	int eventFD = -1;
	std::vector<pollfd>::iterator iter = _PFDS.begin();

	while (Server::bRunning)
	{
		eventFD = poll(_PFDS.begin().base(), _PFDS.size(), -1);

		if (eventFD <= 0)
		{
			throw std::runtime_error("error: poll()");
		}
		for (iter = _PFDS.begin(); iter != _PFDS.end(); ++iter)
		{
			if (iter->revents == 0)
			{
				continue ;
			}
			else if (iter->revents & POLLIN)
			{
				if (iter->fd == _servSock)      // accept client
				{
					int ClntFD = -1;

				}
				else                            // response handling
				{
                    const char cBufLEN = 1024;
					// interpret IRC CMD_MSG


				}
			}
			else if (iter->revents & POLLHUP)   // disconnect client
			{
				// disconnect process
				// careful FD, vector, map, memory
			}
		}

		// timeout ping-pong
	}
}
}

	//PRIVATE:



//****************************************************************************/
//GLOBAL FUNCTION ************************************************************/