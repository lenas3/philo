NAME = philo
SRC = utils.c main.c philo.c init.c monitoring.c

OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address -g
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