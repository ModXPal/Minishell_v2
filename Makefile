NAME		=	minishell

SRC_FILES	=	src/main.c \
			src/builtin/ft_echo.c \
			src/builtin/ft_env.c \
			src/builtin/ft_export.c \
			src/builtin/ft_export_utils.c \
			src/builtin/ft_pwd.c \
			src/builtin/ft_exit.c \
			src/builtin/ft_unset.c \
			src/builtin/ft_cd.c \
			src/builtin/ft_cd_utils.c \
			src/excve/ft_excve.c \
			src/parsing/parsing.c \
			src/parsing/parsing_utils.c \
			src/parsing/get_len.c \
			src/parsing/get_envar.c \
			src/parsing/error.c \

LIBFT_PATH	=	libft/

LIBFT_LIB	=	libft/libft.a

INCLUDE_PATH	=	include/

SRC_OBJS	=	$(SRC_FILES:.c=.o)

LIBFTMAKE	=	$(MAKE) --no-print-directory -C $(LIBFT_PATH)

CC		=	clang

CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDE_PATH) 

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
