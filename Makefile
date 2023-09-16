# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 18:42:37 by fcatteau          #+#    #+#              #
#    Updated: 2023/09/16 14:50:16 by fcatteau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/philo.c \
       srcs/utils.c \
       srcs/time.c \
       srcs/routine.c \
       srcs/init.c \
	   srcs/dead_file.c \
	   srcs/routine2.c

OBJS = $(SRCS:.c=.o)

HEADERS = -I ./Includes/

CFLAGS =  -Wall -Werror -Wextra #-fsanitize=thread

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(HEADERS) -o $(NAME) $(OBJS) -lpthread

%.o: %.c
	gcc $(CFLAGS) $(HEADERS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
