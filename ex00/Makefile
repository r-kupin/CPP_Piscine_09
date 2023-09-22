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

NAME = rpn
ASAN = $(NAME)_asan
WORDY = $(NAME)_wordy

SRCS = src/Interpreter.cpp \
			src/Interpreter_evaluator.cpp \
			src/Interpreter_input_checker.cpp \
			src/Interpreter_tokenizer.cpp \
			src/main.cpp \
			src/tokens/Number.cpp \
			src/tokens/Operator.cpp

OBJS = $(SRCS:.cpp=.o)
W_OBJS = $(SRCS:.cpp=_w.o)

CXX = clang++

CXXFLAGS = -Wall -Wextra -Werror -O0 -std=c++98
ASANFLAGS = -g -fsanitize=address

all: $(NAME)

asan: $(ASAN)
	./$(ASAN)  "8 9 * 9 - 9 - 9 - 4 - 1 +"

wordy: $(WORDY)
	./$(WORDY)  "8 9 * 9 - 9 - 9 - 4 - 1 +"

valgrnd: $(NAME)
	valgrind ./$(NAME)  "8 9 * 9 - 9 - 9 - 4 - 1 +"

$(ASAN): $(OBJS)
	$(CXX) $(ASANFLAGS) $(CXXFLAGS) $(OBJS) -o $(ASAN)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(WORDY): $(W_OBJS)
	$(CXX) $(CXXFLAGS) $(W_OBJS) -o $(WORDY)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/%_w.o: src/%.cpp
	$(CXX) $(CXXFLAGS)  -D PRINT=true -c $< -o $@

clean:
	@rm -fr $(OBJS)
	@rm -fr $(W_OBJS)

fclean: clean
	@rm -fr $(NAME)
	@rm -fr $(ASAN)
	@rm -fr $(WORDY)

re:
	@$(MAKE) fclean
	@$(MAKE) all
