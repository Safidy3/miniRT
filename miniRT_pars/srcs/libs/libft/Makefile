SRCS = ft_isalpha.c\
ft_memcpy.c\
ft_memchr.c\
ft_memset.c\
ft_strlen.c\
ft_tolower.c\
ft_isascii.c\
ft_strncmp.c\
ft_toupper.c\
ft_bzero.c\
ft_isdigit.c\
ft_strnstr.c\
ft_isalnum.c\
ft_isprint.c\
ft_memmove.c\
ft_strlcpy.c\
ft_strlcat.c\
ft_strchr.c\
ft_strrchr.c\
ft_memcmp.c\
ft_atoi.c\
ft_calloc.c\
ft_strdup.c\
ft_substr.c\
ft_strjoin.c\
ft_strtrim.c\
ft_striteri.c\
ft_putchar_fd.c\
ft_putstr_fd.c\
ft_putendl_fd.c\
ft_strmapi.c\
ft_itoa.c\
ft_putnbr_fd.c\
ft_split.c \
ft_split_space.c \
ft_lst_rt.c

OBJS = $(SRCS:%.c=%.o)

NAME = libft.a

%.o : %.c
	gcc -Wall -Wextra -Werror -c $< -o $(<:%.c=%.o)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all : $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
