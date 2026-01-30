NAME = philo
SRC = utils.c main.c philo.c

OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address 
#  valgrind --leak-check=full --show-leak-kinds=all
CC = cc

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re