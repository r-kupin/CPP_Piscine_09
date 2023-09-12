# 
# 
# 
#   /$$$$$$                             /$$$$$$   /$$$$$$ 
#  /$$__  $$                           /$$$_  $$ /$$__  $$
# | $$  \__/  /$$$$$$   /$$$$$$       | $$$$\ $$| $$  \ $$
# | $$       /$$__  $$ /$$__  $$      | $$ $$ $$|  $$$$$$/
# | $$      | $$  \ $$| $$  \ $$      | $$\ $$$$ >$$__  $$
# | $$    $$| $$  | $$| $$  | $$      | $$ \ $$$| $$  \ $$
# |  $$$$$$/| $$$$$$$/| $$$$$$$/      |  $$$$$$/|  $$$$$$/
#  \______/ | $$____/ | $$____/        \______/  \______/ 
#           | $$      | $$                                
#           | $$      | $$                                
#           |__/      |__/                                
# 
# 

NAME = rpn
NAME_LIB = $(NAME)_lib
ASAN = $(NAME)_asan
TEST = $(NAME)_test

SRCS = src/Interpreter.cpp \
			src/Interpreter_evaluator.cpp \
			src/Interpreter_input_checker.cpp \
			src/Interpreter_reverser.cpp \
			src/Interpreter_tokenizer.cpp \
			src/main.cpp \
			src/tokens/Number.cpp \
			src/tokens/Operator.cpp \
			src/tokens/Parenthesis.cpp
LIB_SRCS = src/Interpreter.cpp \
          	src/Interpreter_evaluator.cpp \
            src/Interpreter_input_checker.cpp \
            src/Interpreter_reverser.cpp \
            src/Interpreter_tokenizer.cpp \
            src/tokens/Number.cpp \
            src/tokens/Operator.cpp \
            src/tokens/Parenthesis.cpp
TEST_SRCS = test/input_check_test.cpp \
			test/number_test.cpp \
			test/operator_test.cpp \
			test/postfixer_test.cpp \
			test/tokenizer_test.cpp


OBJS = $(SRCS:.cpp=.o)
LIB_OBJS = $(LIB_SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

CXX = clang++
GXX = g++
LIB_CXX = ar rvs

CXXFLAGS = -Wall -Wextra -Werror -std=c++98
LINKER_FLAGS = -lgtest -lgtest_main -pthread
ASANFLAGS = -g -fsanitize=address

all: $(NAME)

asan: $(ASAN)
	./$(ASAN)

valgrnd: $(NAME)
	valgrind ./$(NAME) "3 + ((1 + 4) * 2) - 1"

test: $(TEST)
	./$(TEST) "3 + ((1 + 4) * 2) - 1"

$(ASAN): $(OBJS)
	$(CXX) $(ASANFLAGS) $(CXXFLAGS) $(OBJS) -o $(ASAN)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(NAME_LIB): $(LIB_OBJS)
	$(LIB_CXX) $(NAME_LIB) $(LIB_OBJS)

$(TEST): $(TEST_OBJS) $(NAME_LIB)
	$(GXX) $(TEST_OBJS) $(NAME_LIB) $(LINKER_FLAGS) -o $(TEST)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test/%.o: test/%.cpp
	$(GXX) -c $< -o $@

clean:
	@rm -fr $(OBJS)
	@rm -fr $(TEST_OBJS)

fclean: clean
	@rm -fr $(NAME)
	@rm -fr $(TEST)
	@rm -fr $(NAME_LIB)
	@rm -fr $(ASAN)

re:
	@$(MAKE) fclean
	@$(MAKE) all
