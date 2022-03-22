NAME = philo

SRCS = main.c \
		ft_atoi.c \
		ft_init_info.c \
		ft_init_philo.c \
		ft_clear_philo.c \
		ft_launcher.c \
		ft_utils.c \
		ft_routine.c \
		ft_check_philo.c 

CFLAGS = -Wall -Wextra -Werror

CC = gcc

OBJ = $(SRCS:.c=.o)

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
		rm -f $(NAME)

fclean:	clean
		rm -f $(OBJ)

re : fclean $(NAME)

.PHONY: $(NAME) all clean fclean re