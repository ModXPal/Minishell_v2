SRCS		=	ft_memset.c\
			ft_bzero.c\
			ft_memcpy.c\
			ft_memccpy.c\
			ft_memmove.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_strlen.c\
			ft_isalpha.c\
			ft_isdigit.c\
			ft_isalnum.c\
			ft_isascii.c\
			ft_isprint.c\
			ft_toupper.c\
			ft_tolower.c\
			ft_strchr.c\
			ft_strrchr.c\
			ft_strncmp.c\
			ft_strlcpy.c\
			ft_strlcat.c\
			ft_strnstr.c\
			ft_atoi.c\
			ft_calloc.c\
			ft_strdup.c\
			ft_substr.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_split.c\
			ft_itoa.c\
			ft_strmapi.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c\
			ft_envar_new.c\
			ft_envaradd_back.c\
			ft_envarlast.c\
			ft_charcmp.c\
			ft_envarsize.c \
			ft_lst_insert.c \
			ft_envar_insert.c \
			ft_envar_position.c \
			ft_lst_remove.c \
			ft_envar_remove.c \
			ft_envar_find_content.c \
			ft_strcmp.c \
			ft_split_pipes.c \
			ft_split_quotes.c\
			ft_split_quotes_utils.c\

OBJS		= $(SRCS:.c=.o)

NAME		= libft.a

CC			= gcc

RM			= rm -rf

CFLAGS		= -Wall -Wextra -Werror -I../include 

all:		$(NAME)

%.o : %.c
	@${CC} -c ${CFLAGS} $< -o $@

$(NAME):	$(OBJS)
				@ar rc $(NAME) $^
				@echo "$(NAME) created"
				@ranlib $(NAME)

clean:
				@${RM} ${OBJS}
				@echo "libft .o deleted"

fclean:		clean
				@${RM} $(NAME)
				@echo "$(NAME) deleted"

re:			fclean all

.PHONY:		all clean fclean re
