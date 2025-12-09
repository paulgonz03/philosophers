NAME = philosophers

CC = cc

SRC = \
	philosophers.c utils_philosophers.c monitor.c routine.c\

OBJ = ${SRC:%.c=objects/%.o}

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

objects/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) -rf objects

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re