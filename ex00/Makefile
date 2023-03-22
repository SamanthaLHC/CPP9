NAME = btc

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g3 -std=c++98

SRC = ./BitcoinExchange.cpp main.cpp

OBJ = $(SRC:%.cpp=%.o)

all: $(NAME)

${NAME}: ${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -o ${NAME}

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re : fclean
	make all

grind: ${NAME}
		valgrind ./$(NAME) "je teste valgrind"

test: $(NAME)
	./$(NAME) "123 pouet pouet"

.PHONY: clean fclean re grind test