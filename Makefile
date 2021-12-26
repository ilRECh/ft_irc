NAME		= ft_irc

CXX			= clang++
CPPFLAGS	= -Wall -Werror -Wextra -pthread -g $(addprefix -I, $(INCLUDES))
SRC=./srcs/
INCLUDES=./include ./include/cmds/

FILES		= main \
			$(addprefix $(SRC), Server Director User ExceptionUni Password)
		
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
