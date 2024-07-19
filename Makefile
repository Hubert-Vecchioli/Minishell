#so_long
NAME 		= minishell
SRCS 			=	$(addprefix srcs/main/, $(addsuffix .c, \
					main \
					minishell \
					init \
					env_var \
					generate_prompt \
					ft_clean_prompt \
					easy_errors \
					easy_errors_utils \
					expand_tilde \
					init_ast))
SRCS 			+=	$(addprefix srcs/parse/, $(addsuffix .c, \
					print_ast \
					utils_ast))
SRCS 			+=	$(addprefix srcs/utils/, $(addsuffix .c, \
					utils_list))
SRCS 			+=	$(addprefix srcs/execute/, $(addsuffix .c, \
					exec_ast \
					exec_builtin \
					ft_heredoc \
					ft_pipe \
					solve_path \
					exec_redir))
SRCS 			+=	$(addprefix srcs/end/, $(addsuffix .c, \
					end_status \
					ft_exit))
SRCS 			+=	$(addprefix srcs/clean/, $(addsuffix .c, \
					clean_ast \
					clean_list \
					save_ast_lk \
					ret_status))
SRCS 			+=	$(addprefix srcs/built-in/cd/, $(addsuffix .c, \
					ft_cd_step1 \
					ft_cd_step2 \
					ft_cd \
					ft_cd_utils1))
SRCS 			+=	$(addprefix srcs/built-in/echo/, $(addsuffix .c, \
					ft_echo ))
SRCS 			+=	$(addprefix srcs/built-in/env/, $(addsuffix .c, \
					ft_env ))
SRCS 			+=	$(addprefix srcs/built-in/export/, $(addsuffix .c, \
					ft_export ))
SRCS 			+=	$(addprefix srcs/built-in/pwd/, $(addsuffix .c, \
					ft_pwd ))
SRCS 			+=	$(addprefix srcs/built-in/unset/, $(addsuffix .c, \
					ft_unset ))
SRCS 			+=	$(addprefix srcs/built-in/, $(addsuffix .c, \
					utils_builtin ))
OBJS			=  ${SRCS:.c=.o}

#compiler
CC			= cc
FLAGS       = -Wall -Wextra -Werror -Imlx -I ./includes -I $(LIBFT_DIR) 

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