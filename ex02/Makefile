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

SRCS = 	src/main.cpp src/PmergeMe.cpp

OBJS = $(SRCS:.cpp=.o)

CXX = clang++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98
ASANFLAGS = -g -fsanitize=address

all: $(NAME)

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
