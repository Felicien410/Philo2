NAME = philo

SRCS = philo.c \
       utils.c \
       time.c \
	   print_struct.c \
	   routine.c \
	   init.c

OBJS = $(SRCS:.c=.o)

HEADERS = -I ./Includes/

CFLAGS = -Wall -Werror -Wextra

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(HEADERS) -o $(NAME) $(OBJS) -lpthread
	@$(MAKE) clean

%.o: %.c
	gcc $(CFLAGS) $(HEADERS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
