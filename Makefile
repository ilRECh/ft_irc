NAME		= IRC

CXX			= clang++
CPPFLAGS	= -Wall -Werror -Wextra -g -I$(PATH_TO_HEADERS)

FILES		= main
FILES_CPP	= $(addsuffix .cpp, $(FILES))
FILES_HPP	= $(addsuffix .hpp, $(FILES))
FILES_OBJ	= $(addsuffix .o, $(FILES))

PATH_TO_HEADERS=.

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
