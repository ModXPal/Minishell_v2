NAME		=	minishell

SRC_FILES	=	src/main.c \
			src/builtin/ft_echo.c \
			src/builtin/ft_env.c \
			src/builtin/ft_export.c \
			src/builtin/ft_export_utils.c \
			src/builtin/ft_export_utils_2.c \
			src/builtin/ft_export_utils_3.c \
			src/builtin/ft_export_utils_4.c \
			src/builtin/ft_pwd.c \
			src/builtin/ft_exit.c \
			src/builtin/ft_unset.c \
			src/builtin/ft_unset_utils.c  \
			src/builtin/ft_cd.c \
			src/builtin/ft_cd_utils.c \
			src/builtin/ft_cd_utils_2.c \
			src/builtin/ft_cd_utils_3.c \
			src/builtin/ft_cd_utils_4.c \
			src/excve/ft_excve.c \
			src/excve/dup.c \
			src/multipipes/exec.c \
			src/multipipes/get_path.c \
			src/multipipes/multipipes.c \
			src/multipipes/close.c \
			src/multipipes/error.c \
			src/multipipes/exec_builtin.c \
			src/multipipes/exec_execve.c \
			src/parsing/init.c \
			src/parsing/parsing.c \
			src/parsing/parsing_utils.c \
			src/parsing/get_len.c \
			src/parsing/get_envar.c \
			src/parsing/error.c \
			src/parsing/syntax_check.c \
			src/parsing/heredoc.c \
			src/parsing/redirection.c \
			src/parsing/input_list.c \
			src/parsing/count.c \
			src/free/free_1.c \
			src/free/free_2.c \
			src/signal/signal.c \

LIBFT_PATH	=	libft/

LIBFT_LIB	=	libft/libft.a 

INCLUDE_PATH	=	include/

SRC_OBJS	=	$(SRC_FILES:.c=.o)

LIBFTMAKE	=	$(MAKE) --no-print-directory -C $(LIBFT_PATH)

CC		=	clang

CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDE_PATH) -g #-fsanitize=address

RM		=	rm -rf

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@

all:			$(NAME)

$(NAME):		$(SRC_OBJS)
					@$(LIBFTMAKE)
					@$(CC) -lreadline $(CFLAGS) $(SRC_OBJS) $(LIBFT_LIB) -o $(NAME)
					@echo "$(NAME) created"

clean:
			@make --no-print-directory -C $(LIBFT_PATH) clean
			@$(RM) $(SRC_OBJS)
			@echo "$(NAME) .o deleted"

fclean:			clean
				@$(RM) $(NAME) $(LIBFT_LIB)
				@echo "libft.a deleted"
				@echo "$(NAME) deleted"

re:			fclean all

.PHONY:			all clean fclean re
