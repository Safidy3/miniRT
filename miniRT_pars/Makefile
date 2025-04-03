NAME = miniRT

ERROR_PATH = ./srcs/error-handling
GNL_PATH = ./srcs/libs/get_next_line
PARSE_PATH = ./srcs/parse
UTILS_PATH = ./srcs/utils

SRCS = ./miniRT.c ./data_create.c $(ERROR_PATH)/scene.c  debug_print.c \
$(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c \
$(UTILS_PATH)/scene.c $(UTILS_PATH)/init.c $(UTILS_PATH)/protected.c \
$(UTILS_PATH)/elt_value_format.c $(UTILS_PATH)/data_manip.c $(UTILS_PATH)/free.c \
$(PARSE_PATH)/parse.c $(PARSE_PATH)/light_parser.c $(PARSE_PATH)/object_parser.c \

OBJS = $(SRCS:%.c=%.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -g
LIBFT_PATH = ../libft
LIBFT_ARCHIVE = $(LIBFT_PATH)/libft.a

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $(<:%.c=%.o)

$(LIBFT_ARCHIVE):
	@make bonus -C $(LIBFT_PATH)

$(NAME) : $(LIBFT_ARCHIVE) $(OBJS)
	@make bonus -C $(LIBFT_PATH)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT_ARCHIVE)

all : $(NAME)

clean:
	rm -f ${OBJS}
	@make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	@make clean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re