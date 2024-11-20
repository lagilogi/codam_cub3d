NAME =			libft.a
CFLAGS =		-Wall -Werror -Wextra -g
SRCS = 			ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
		ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
		ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
		ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
		ft_toupper.c ft_memcpy.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
		ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
		ft_lstiter.c ft_lstmap.c \
		ft_printf.c ft_nmbrs.c ft_ptrs.c ft_putchar.c ft_putstr.c \
		get_next_line_utils.c get_next_line.c

OBJ_DIR		=	./objects/
OBJ 		=	$(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

all:			$(NAME)

$(NAME):		$(OBJ)
	ar rcs libft.a $(OBJ)

$(OBJ_DIR)%.o:	%.c
				@mkdir -p $(@D)
				$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: 	fclean all

.PHONY:	all bonus clean fclean re