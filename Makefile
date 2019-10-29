NAME = Dices

CLS = sources/Dices.cpp sources/User.cpp sources/Game.cpp

SRC = sources/print.cpp sources/utility.cpp sources/main.cpp

CLSO = $(CLS:.cpp=.o)

OBJ = $(SRC:.cpp=.o)

all: $(SRC) $(CLS) $(NAME)

$(NAME): $(CLSO) $(OBJ)
	@g++ *.o -o $@
	@echo "\033[1;32mProject ready!\033[0m"

.cpp.o:
	@g++ $< -c
	@echo "\033[1;32m" $< " compiled!\033[0m"

clean:
	@rm -rf *.o
	@rm -rf sources/*.o
	@echo "\033[1;32mAll clean\033[0m"

fclean: clean
	@rm -rf $(NAME)

re: fclean all