NAME = RPN

CXX = c++
CXXFLAGS = -MMD -g3 -Wall -Wextra -Werror -std=c++98
INC = -I ./inc

SRC_PATH = sources/
OBJ_PATH= objs/

SRCS = ${addprefix ${SRC_PATH}, \
		 main.cpp \
		 RevPolishNot.cpp}

OBJS = ${SRCS:${SRC_PATH}%.cpp=${OBJ_PATH}%.o}
DEPS = ${SRCS:${SRC_PATH}%.cpp=${OBJ_PATH}%.d}


${NAME}: ${OBJ_PATH} ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

${OBJ_PATH}:
	mkdir -p objs

${OBJ_PATH}%.o: ${SRC_PATH}%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@ ${INC}

all: ${NAME}

clean:
	rm -rf ${OBJ_PATH}

.PHONY: fclean
fclean: clean
	rm -rf ${NAME}

re: fclean
	make all

# grind: ${NAME}
# 	valgrind -s --track-origins=yes --track-fds=yes --leak-check=full --show-leak-kinds=all 
test:
	./RPN "2 5 6 + *"

test2:
	./RPN  "8 9 * 9 - 9 - 9 - 4 - 1 +"

test3:
	./RPN   "7 7 * 7 -"

test4:
	./RPN  "1 2 * 2 / 2 * 2 4 - +"

test5:
	 ./RPN "(1 + 1)"

.PHONY: all clean fclean re grind 

-include ${DEPS}