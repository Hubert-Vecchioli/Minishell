#so_long
NAME 		= minishell
SRC 		= actions_commands.c actions_env.c actions_tokens.c end.c error.c generate_tokens.c \
				execute.c init.c main.c minishell.c
SRCS_DIR 	= ./srcs/
SRCS 		= $(addprefix $(SRCS_DIR), $(SRC))
OBJS		=  ${SRCS:.c=.o}

#compiler
CC			= cc
FLAGS       = -Wall -Wextra -Werror -Imlx -I ./include -I $(LIBFT_DIR) 

# 
LIBFT_DIR	= ./libft
LIBFT_PATH	= $(LIBFT_DIR)/libft.a

all : $(NAME)

.c.o:
	$(CC) $(FLAGS) -c $< -o ${<:.c=.o}
##  -lreadline to compile readline
$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_PATH) -o $(NAME) -lreadline
	@make clean

clean :
	@make clean -C $(LIBFT_DIR)
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY: all clean fclean re