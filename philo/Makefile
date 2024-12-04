NAME = philo
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main.c init_status.c utils.c routine.c status.c utils2.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread 

clean : 
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all
