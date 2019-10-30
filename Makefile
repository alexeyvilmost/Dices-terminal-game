NAME = Dices

SRC = utility.cpp print.cpp Dices.cpp User.cpp Game.cpp main.cpp

CLSO = $(CLS:.cpp=.o)

GREEN = "\033[1;32m"
ENDC = "\033[0m"

OBJ = $(addprefix objects/,$(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@g++ $(OBJ) -o $@
	@echo $(GREEN) Project ready. Use ./Dices to run $(ENDC)

objects/%.o: sources/%.cpp
	@g++ -o $@ -c $<
	@echo $(GREEN) $< compiled successfully $(ENDC)

clean:
	@rm -rf objects/*.o
	@echo $(GREEN) All clean $(ENDC)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
