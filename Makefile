NAME = ircserv
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
INCLUDESDIR = ./includes/
SRCSDIR = ./srcs/
SRCS = $(addprefix $(SRCSDIR), \
			main.cpp \
			Channel.cpp \
			Database.cpp \
			MessageHandler.cpp \
			Server.cpp \
			User.cpp \
			)
OBJS = $(SRCS:.cpp=.o)
RM = rm -f

all : $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean :
	make clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
