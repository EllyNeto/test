NAME = philo
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror 
SRCS = main.c init_mode.c utils.c routine.c mode.c 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread 

clean : 
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all
