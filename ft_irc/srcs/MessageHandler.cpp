#include <sstream>
#include "../includes/MessageHandler.hpp"

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
MessageHandler::MessageHandler(int FD, std::string &BUFF, Database * const pDB)
    : _FD(FD)
    , _BUFF(BUFF)
    , _pDB(pDB)
{   }

MessageHandler::~MessageHandler()
{	}

    //PRIVATE:
MessageHandler::MessageHandler()
    : _FD(0)
    , _pDB(NULL)
{
    std::cerr<<"error: never works"<<std::endl;
}

MessageHandler& MessageHandler::operator=(const MessageHandler& rRhs)
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

MessageHandler::MessageHandler(const MessageHandler& rCopy)
    : _FD(0)
    , _pDB(NULL)
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

    //PRIVATE:

    

//****************************************************************************/
//Behavior *******************************************************************/
    //PUBLIC:
void MessageHandler::run()
{
    std::cout<<"FD["<<_FD<<"]: "<<_BUFF<<"\n"<<std::endl;

    while (_BUFF.size())
    {
        // parse command
            // get a command line
        const size_t endOfPresentCMD = _BUFF.find("\r\n");
        std::string presentCMD;

        if (endOfPresentCMD == _BUFF.npos)
        {
            return ;
        }

        presentCMD = _BUFF.substr(0, endOfPresentCMD);
        _BUFF.erase(0, endOfPresentCMD + 2);


            // parse std::string to s_Command
        s_Command command;
        std::vector<std::string> TMP;

        if (presentCMD[0] == ':')
        {
            const size_t endOfPrefix = presentCMD.find(' ');

            if (endOfPrefix == presentCMD.npos)
            {
                return ;
            }

            command.prefix = presentCMD.substr(1, endOfPrefix);
            presentCMD.erase(0, endOfPrefix);
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
    std::cout<<"[prefix]: "<<command.prefix<<std::endl;
    std::cout<<"[command]: "<<command.command<<std::endl;
    std::cout<<"[params]"<<std::endl;
    for (size_t i = 0; i < command.parameters.size(); ++i)
        std::cout<<"    ("<<i<<"): "<<command.parameters[i]<<std::endl;
    std::cout<<"[suffix]: "<<command.suffix<<std::endl<<std::endl;
}



        // execute command
        if (command.command == "PRIVMSG")
        {
std::cout<<">>PRIVMSG"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "PING")
        {
std::cout<<">>PING"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "NOTICE")
        {
std::cout<<">>NOTICE"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "JOIN")
        {
std::cout<<">>JOIN"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "PART")
        {
std::cout<<">>PART"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "TOPIC")
        {
std::cout<<">>TOPIC"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "OPER")
        {
std::cout<<">>OPER"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "MODE")
        {
std::cout<<">>MODE"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "INVITE")
        {
std::cout<<">>INVITE"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "KICK")
        {
std::cout<<">>KICK"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "PASS")
        {
std::cout<<">>PASS"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "NICK")
        {
std::cout<<">>NICK"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "USER")
        {
std::cout<<">>USER"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "CAP")
        {
std::cout<<">>CAP"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "QUIT")
        {
std::cout<<">>QUIT"<<std::endl<<std::endl<<std::endl;
        }
        else if (command.command == "KILL")
        {
std::cout<<">>KILL"<<std::endl<<std::endl<<std::endl;
        }
        else
        {
std::cout<<">>NO COMMAND"<<std::endl;
        }
    }
}


    //PRIVATE:
std::vector<std::string> MessageHandler::split(const std::string& STR, char DL)
{
    const size_t FIRST_CAPACITY = 5;
    std::istringstream ISS(STR);
    std::string BUFF;
    std::vector<std::string> RET;
 
    RET.reserve(FIRST_CAPACITY);

    while (getline(ISS, BUFF, DL))
    {
        RET.push_back(BUFF);
    }
 
    return (RET);
}


//****************************************************************************/
//GLOBAL FUNCTION ************************************************************/