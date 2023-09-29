//#pragma once
#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>

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

typedef struct ChannelMode
{
    bool        bO; // give/take channel operator privileges        -> ON SUBJECT
    bool        bP; // private channel flag
    bool        bS; // secret channel flag
    bool        bI; // invite-only channel flag                     -> ON SUBJECT
    bool        bT; // topic settable by channel operator only flag -> ON SUBJECT
    bool        bN; // no messages to channel from clients on the outside
    bool        bM; // moderated channel
    bool        bL; // set the user limit to channel                -> ON SUBJECT
    bool        bB; // set a ban mask to keep users out
    bool        bV; // give/take the ability to speak on a moderated channel
    bool        bK; // set a channel key (password)                 -> ON SUBJECT
    int         userLimit; // by mode 'l'
    std::string channelkey; // by mode 'k'
}   s_ChannelMode;

class Channel
{
public:
    //Constructor overload & OCCF
    Channel(std::string& name, std::string &topic, s_ChannelMode &mode);
    ~Channel();
    //Exception
    //Operator overload
    //Getter & Setter
    const std::string getName() const;
    void setName(std::string& name);
    const std::string getTopic() const;
    void setTopic(std::string& topic);
    s_ChannelMode getChannelMode() const;
    void setChannelMode(s_ChannelMode& mode);
    //Behavior

private:
    //Constructor overload & OCCF
    Channel();
    Channel& operator=(const Channel& rRhs);
    Channel(const Channel& rCopy);
    //Exception
    //Operator overload
    //Getter & Setter
    //Behavior

private:
    std::string     _name;
    std::string     _topic;
    s_ChannelMode   _mode;
};

//GLOBAL FUNCTION for class Channel{}

#endif
