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
test_expected_22: all
	./RPN "2 5 6 + *"

test_expected_42: all
	./RPN  "8 9 * 9 - 9 - 9 - 4 - 1 +"

test_expected_result_42: all
	./RPN   "7 7 * 7 -"

test_expected_0: all
	./RPN  "1 2 * 2 / 2 * 2 4 - +"

test_expected_error_infix: all
	./RPN "(1 + 1)"

test_expected_error_invalid_element: all
	./RPN "(1 1) +"

test_expected_error_no_operator: all
	./RPN "1 1"

test_expected_error_first_elem_is_operator: all
	./RPN "- 1 1 -"

test_expected_error_missing_one_operator: all
	./RPN "1 1 1 1 +"

test_expected_error_impossible_division_by_0: all
	./RPN "1 0 /"

test_expected_error_missing_a_digit: all
	./RPN "9 9 + - 9 -"

# make -i pour ignorer les return val du main!

test_all: all test_expected_0 test_expected_22 test_expected_42 test_expected_result_42 test_expected_error_first_elem_is_operator test_expected_error_impossible_division_by_0 test_expected_error_infix test_expected_error_invalid_element test_expected_error_missing_one_operator test_expected_error_no_operator test_expected_result_42 test_expected_error_missing_a_digit
	@echo "_____________________________________________________________________"
	@echo "\e[1;32mexpected results: 0 - 22 - 42 - 42\e[1;32m"
	@echo "\e[1;32mexpected errors: "
	@echo "--missing operand cannot fully calculate the sequence--"
	@echo "--Divide by zero impossible.--"
	@echo "--Not a RPN sequence (no operator at the end).--"
	@echo "--Not an integer < 10 nor an operator. --"
	@echo "--Operator missing cannot fully calculate the sequence--"
	@echo "--No operator in this sequence.--"
	@echo "--missing operand cannot fully calculate the sequence.--"

.PHONY: all clean fclean re grind test_all test_expected_0 test_expected_22 test_expected_42 test_expected_error_first_elem_is_operator test_expected_error_impossible_division_by_0 test_expected_error_infix test_expected_error_invalid_element test_expected_error_missing_a_digit test_expected_error_missing_one_operator test_expected_error_no_operator test_expected_result_42

-include ${DEPS}