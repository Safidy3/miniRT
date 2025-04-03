NAME = miniRT

ERROR_PATH = ./srcs/error-handling
GNL_PATH = ./srcs/libs/get_next_line
UTILS_PATH = ./srcs/utils
PARSE_PATH = ./srcs/parse

SRCS = ./miniRT.c ./data_create.c $(ERROR_PATH)/scene.c  debug_print.c \
$(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c \
$(UTILS_PATH)/scene.c $(UTILS_PATH)/init.c $(UTILS_PATH)/protected.c \
$(UTILS_PATH)/elt_value_format.c $(UTILS_PATH)/data_manip.c $(UTILS_PATH)/free.c \
$(PARSE_PATH)/parse.c $(PARSE_PATH)/light_parser.c $(PARSE_PATH)/object_parser.c \

OBJS = $(SRCS:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g
LIBFT_FLAG = -lft
LIBFT_PATH = ./srcs/libs/libft/

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(<:%.c=%.o)

$(NAME) : $(OBJS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(LIBFT_PATH) $(LIBFT_FLAG)

all : $(NAME)

clean:
	rm -f ${OBJS}
	@make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	@make clean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re                                                             