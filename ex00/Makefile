NAME = btc

CXX = c++
CXXFLAGS = -MMD -Wall -Wextra -Werror -g3 -std=c++98

SRCS =  BitcoinExchange.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

clean:
	rm -rf ${OBJS} ${DEPS}

fclean: clean
	rm -rf ${NAME}

re : fclean
	make all

grind: ${NAME}
		valgrind ./$(NAME) "je teste valgrind"

test: $(NAME)
	./$(NAME) "123 pouet pouet"

.PHONY: all clean fclean re grind test

-include ${DEPS}