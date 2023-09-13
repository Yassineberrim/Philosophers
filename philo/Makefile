NAME = philo

SRCS = philo.c utils.c philosophers.c check.c\

CC = cc

CFLAGS = -Wall -Werror -Wextra

OBJS = ${SRCS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(FLAGS) $(SRCS) -o $(NAME)
clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all