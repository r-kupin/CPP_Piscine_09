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

NAME = btc
ASAN = $(NAME)_asan

SRCS = src/BitcoinExchange.cpp  src/Date.cpp  src/main.cpp

OBJS = $(SRCS:.cpp=.o)

CXX = clang++

CXXFLAGS = -Wall -Wextra -Werror -gdwarf-4 -std=c++98
ASANFLAGS = -g -fsanitize=address

all: $(NAME)

asan: $(ASAN)
	./$(ASAN) "resources/test_input.txt"
	./$(ASAN) "resources/empty_input.txt"

valgrnd: $(NAME)
	valgrind ./$(NAME) "resources/test_input.txt"
	valgrind ./$(NAME) "resources/empty_input.txt"

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
