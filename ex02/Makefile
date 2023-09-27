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

NAME = PmergeMe
ASAN = $(NAME)_asan
WORDY = $(NAME)_wordy

SRCS = 	src/main.cpp

OBJS = $(SRCS:.cpp=.o)

CXX = clang++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98
ASANFLAGS = -g -fsanitize=address

all: $(NAME)

asan: $(ASAN)
	./$(ASAN)  ""

valgrnd: $(NAME)
	valgrind ./$(NAME)  "8 9 * 9 - 9 - 9 - 4 - 1 +"

$(ASAN): $(OBJS)
	$(CXX) $(ASANFLAGS) $(CXXFLAGS) $(OBJS) -o $(ASAN)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -fr $(OBJS)

fclean: clean
	@rm -fr $(NAME)
	@rm -fr $(ASAN)

re:
	@$(MAKE) fclean
	@$(MAKE) all
