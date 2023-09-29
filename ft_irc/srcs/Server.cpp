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
Server::Server()
    : _servSock(-1)
    , _pDB(NULL)
{
    const u_int8_t FIRST_SERVER_CAPACITY= 255;

    _PFDS.reserve(FIRST_SERVER_CAPACITY);
}

Server::~Server()
{   }

    //PRIVATE:
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
{	/* Open server: 
        server socket & Push Server socket to pollfds & allocate Database */
{
    _servSock = socket(AF_INET, SOCK_STREAM, 0);
    if (_servSock < 0)
    {
        throw std::runtime_error("error: socket()");
    }
}
{
    int optVAL = 1;

    if (setsockopt(_servSock, SOL_SOCKET, SO_REUSEADDR, &optVAL, sizeof(optVAL)))
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
    servSockADDR.sin_port = htons(Port);
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
{
    _pDB = new Database;
}
{	// Run IRC-server Process
    while (Server::bRunning)
    {
        int eventFD = -1;
        std::vector<pollfd>::iterator iter = _PFDS.begin();

        eventFD = poll(_PFDS.begin().base(), _PFDS.size(), -1);
        if (eventFD < 0)
        {
            break ;
        }

        for (iter = _PFDS.begin(); iter != _PFDS.end(); ++iter)
        {
            const bool NO_EVENT = (iter->revents != POLLIN);
            const bool SERV_POLLIN = (iter->revents & POLLIN) && \
                                    (iter->fd == _servSock);
            const bool CLNT_POLLIN = (iter->revents & POLLIN) && \
                                    (iter->fd != _servSock);

// std::cout<<"for loop(servSock: "<<_servSock<<")"<<std::endl;
            if (NO_EVENT)
            {
// std::cout<<"NO_EVENT   "<<iter->fd<<"  ev: "<<iter->events<<"  re: "<<iter->revents<<std::endl;
                continue ;
            }
            else if (SERV_POLLIN)
            {
// std::cout<<"event SERV_POLLIN   "<<iter->fd<<"  ev: "<<iter->events<<"  re: "<<iter->revents<<std::endl;
                SOCKADDR_IN ADDR;
                socklen_t AddrLEN = sizeof(ADDR);
                int clntFD = accept(_servSock, (SOCKADDR*)&ADDR, &AddrLEN);
                // ERR CHECK
                std::cout<<"[+] fd: "<<clntFD<<": accepted!"<<std::endl;

                pollfd clnt = {clntFD, POLLIN, 0};

                _PFDS.push_back(clnt);
                
                goto ESCAPE_EVENT_SEARCHING_LOOP;
            }
            else if (CLNT_POLLIN)
            {
// std::cout<<"event CLNT_POLLIN   "<<iter->fd<<"  ev: "<<iter->events<<"  re: "<<iter->revents<<std::endl;
                char cBUFF[MAX_MSG_LEN] = {0, };
                std::string BUFF;
                ssize_t retVAL = 1;

                retVAL = recv(iter->fd, cBUFF, MAX_MSG_LEN, 0);
                switch (retVAL)
                {
                case -1:
                /* if exist ErrCode about bad condition of server, then send */
                    goto ESCAPE_EVENT_SEARCHING_LOOP;
                case 0:
                    std::cout<<"[-] fd: "<<iter->fd<<": disconnected!"<<std::endl;
                    _pDB->clearUserAtDatabase(iter->fd);
                    close(iter->fd);
                    _PFDS.erase(iter);
                    

                    goto ESCAPE_EVENT_SEARCHING_LOOP;
                default:
                    BUFF = cBUFF;

                    MessageHandler msgHandler(iter->fd, BUFF, _pDB);

                    msgHandler.run();

                    goto ESCAPE_EVENT_SEARCHING_LOOP;
                }
            }
        } ESCAPE_EVENT_SEARCHING_LOOP:;
    }
}
{   // Close Server
    _pDB->clearDatabase();
    delete _pDB;
    for (size_t i = 0; i < _PFDS.size(); ++i)
    {
        close (_PFDS[i].fd);
    }
    close(_servSock);
    _PFDS.clear();
    std::vector<pollfd>().swap(_PFDS);
}
}

void::Server::processExitError()
{
    if (_servSock == -1)
        return ;
    if (_pDB)
    {
        _pDB->clearDatabase();
        delete _pDB;
    }
    for (size_t i = 0; i < _PFDS.size(); ++i)
    {
        close (_PFDS[i].fd);
    }
    close(_servSock);
    _PFDS.clear();
    std::vector<pollfd>().swap(_PFDS);
}

    //PRIVATE:



//****************************************************************************/
//GLOBAL FUNCTION ************************************************************/