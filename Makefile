NAME = philosophers

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
CC = cc

SRC = \
	philosophers.c\

OBJ = $(SRC:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3 

all: $(NAME)

$(NAME): $(OBJ)
	@make all -sC ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make clean -sC ./libft

fclean: clean
	rm -f $(NAME)
	@make fclean -sC ./libft

re: fclean all

.PHONY: all clean fclean re