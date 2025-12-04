SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
OBJ := $(OBJ:src/%=%)
OBJ := $(addprefix obj/, $(OBJ))

CC = c++
LD = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

NAME = webserv

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $(CFLAGS) -o $@ $^

obj/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all
