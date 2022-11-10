CC = cc
CFLAGS = -Wall -Wextra -Werror 
INCLUDE = -I$(PHILO_HEADERS)
SRCS = ./src/main.c\
		./src/monitor.c\
		./src/put_error.c\
		./src/init_data.c\
		./src/case_of_a_philo.c\
		./src/pthread_create_and_join.c\
		./src/libft_philo/ft_strlen.c\
		./src/libft_philo/ft_isdigit.c\
		./src/libft_philo/ft_putstr_fd.c\
		./src/libft_philo/ft_putchar_fd.c\
		./src/libft_philo/ft_putendl_fd.c\
		./src/libft_philo/ato_positive_int.c\
		./src/simulate_one_philosopher/think.c\
		./src/simulate_one_philosopher/put_action.c\
		./src/simulate_one_philosopher/sleep_philo.c\
		./src/simulate_one_philosopher/get_mili_sec.c\
		./src/simulate_one_philosopher/update_time_stamp.c\
		./src/simulate_one_philosopher/take_forks_and_eat.c\
		./src/simulate_one_philosopher/put_action_and_usleep.c\
		./src/simulate_one_philosopher/simulate_one_philosopher.c\

OBJS = $(SRCS:.c=.o)
NAME = philo

PHILO_HEADERS = ./includes/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

# $(NAME): $(OBJS)
# 		ar r $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus