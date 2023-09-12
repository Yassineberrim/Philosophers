NAME = philo

SRCS = philo.c utils.c \

CC = cc

CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread -g

OBJS = ${SRCS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME)
clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all