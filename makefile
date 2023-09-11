# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 22:49:29 by yberrim           #+#    #+#              #
#    Updated: 2023/09/11 23:15:17 by yberrim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = Philo.c utils.c \

CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=thread

OBJS = ${SRCS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC)  $(FLAGS) $(OBJS) -o $(NAME)
clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all