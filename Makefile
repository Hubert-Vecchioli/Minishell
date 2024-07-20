###############################################################################
###############################################################################
#*****************************************************************************#
#********************** Makefile for minishell project  **********************#
#*****************************************************************************#
###############################################################################
###############################################################################

NAME 		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
###############################################################################
###############################################################################

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
###############################################################################
###############################################################################

MAINFILES 		= main.c \
				minishell.c \
				init.c \
				env_var.c \
				generate_prompt.c \
				ft_clean_prompt.c \
				easy_errors.c \
				easy_errors_utils.c \
				init_ast.c  \
				expand_tilde.c \
				expand_env.c
PARSEFILES		= print_ast.c \
				utils_ast.c
UTILSFILES 		= utils_list.c
EXECUTEFILES 	= exec_ast.c \
				exec_builtin.c \
				ft_heredoc.c \
				ft_pipe.c \
				solve_path.c \
				exec_redir.c
ENDFILES 		= end_status.c
CLEANFILES 		= clean_ast.c \
				clean_list.c \
				save_ast_lk.c \
				ret_status.c
BUILTINFILES	= ft_cd_step1.c \
				ft_cd_step2.c \
				ft_cd.c \
				ft_cd_utils1.c \
				ft_exit.c \
				ft_echo.c \
				ft_env.c \
				ft_export.c \
				ft_pwd.c \
				ft_unset.c \
				utils_builtin.c
###############################################################################
###############################################################################

INCS = ./includes
OBJDIRS = objs
SRCDIRS = srcs
PATHS	= $(addprefix main/, $(MAINFILES))\
		$(addprefix parse/, $(PARSEFILES))\
		$(addprefix utils/, $(UTILSFILES))\
		$(addprefix execute/, $(EXECUTEFILES))\
		$(addprefix end/, $(ENDFILES))\
		$(addprefix clean/, $(CLEANFILES))\
		$(addprefix built-in/, $(BUILTINFILES))
OBJS = $(addprefix $(OBJDIRS)/, $(patsubst %.c, %.o, $(PATHS)))
SRCS = $(addprefix $(SRCDIRS)/, $(PATHS))
###############################################################################
###############################################################################

$(NAME) : $(OBJDIRS) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(INCS) -L$(LIBFT_DIR) -lft -lreadline

$(OBJDIRS):
	mkdir -p $(OBJDIRS)
	mkdir -p $(addprefix $(OBJDIRS)/, main)
	mkdir -p $(addprefix $(OBJDIRS)/, parse)
	mkdir -p $(addprefix $(OBJDIRS)/, utils)
	mkdir -p $(addprefix $(OBJDIRS)/, execute)
	mkdir -p $(addprefix $(OBJDIRS)/, end)
	mkdir -p $(addprefix $(OBJDIRS)/, clean)
	mkdir -p $(addprefix $(OBJDIRS)/, built-in)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
###############################################################################
###############################################################################

all : $(NAME)

clean :
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJDIRS)

fclean : clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re : fclean all

$(OBJDIRS)/%.o: $(SRCDIRS)/%.c
	$(CC) $(CFLAGS) -I$(INCS) -c $< -o $@
###############################################################################
###############################################################################

.PHONY: all clean fclean re
###############################################################################
###############################################################################