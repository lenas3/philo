NAME = philo
SRC = utils.c \
		main.c

$(OBJS) = $(SRC:.c = .o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -O $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY : all clean fclean re