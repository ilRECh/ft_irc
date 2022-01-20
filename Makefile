NAME		= ircserv

CXX			= clang++
CPPFLAGS	= -Wall -Wextra -Werror -g $(addprefix -I, $(INCLUDES)) -std=c++98 -pedantic
SRC=./srcs/
CMDS=./srcs/cmds/
INCLUDES= ./include ./include/cmds/

FILES		= main \
			$(addprefix $(SRC), Channel Server User Password Utility Replies TimeStamp) \
			$(addprefix $(CMDS), ACommand\
									PASS\
									)

FILES_CPP	= $(addsuffix .cpp,	$(FILES))
FILES_HPP	= $(wildcard **/**.hpp)
FILES_OBJ	= $(addsuffix .o,	$(FILES))

.PHONY		: all client clean fclean re

all			: $(NAME)

$(FILES_OBJ): $(FILES_HPP)

$(NAME)		: $(FILES_OBJ)
	$(CXX) $(CPPFLAGS) $^ -o $@

client		:
	$(CXX) $(CPPFLAGS) client.cpp -o client

# %.o		: %.cpp $(FILES_HPP)
# 	$(CXX) $(CPPFLAGS) $< -c -o $@

clean		:
	$(RM) $(FILES_OBJ)

fclean		: clean
	$(RM) $(NAME)

re			: fclean all
