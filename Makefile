NAME=IRC
CC=clang++
FLAGS=-Wall -Werror -Wextra -g

FILES=main
FILES_CPP=$(addsuffix .cpp, $(FILES))
FILES_HPP=$(addsuffix .hpp, $(FILES))
FILES_OBJ=$(addsuffix .o, $(FILES))

PATH_TO_HEADERS=.


all: $(NAME)

$(NAME): $(FILES_OBJ)
	$(CC) $(FLAGS) -I$(PATH_TO_HEADERS) $^ -o $@

%.o: %.cpp $(FILES_HPP)
	$(CC) $(FLAGS) -I$(PATH_TO_HEADERS) $< -c -o $@

clean:
	rm $(FILES_OBJ)

fclean:	
	rm $(FILES_OBJ)
	rm $(NAME)

re:
	rm $(FILES_OBJ)
	rm $(NAME)
	make all