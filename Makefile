SRC = main.c vect_utils.c mlx_drawer_utils.c data_free.c

FLAGS = -Wall -Werror -Wextra -I/usr/include
# FLAGS = -I/usr/include
FLAGS_MINI = -Lmlx_linux -Imlx_linux -lXext -lX11 -lm -lz

LIB_MLX_PATH = ./minilibx-linux
LIB_MLX_ARCHIVE = $(LIB_MLX_PATH)/libmlx.a

LIBFT_PATH = ./libft
LIBFT_ARCHIVE = $(LIBFT_PATH)/libft.a

OBJS = $(SRC:.c=.o)
NAME = miniRT

%.o: %.c
	@$(CC) -g $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT_ARCHIVE) $(OBJS) $(LIB_MLX_ARCHIVE)
	@$(CC) -g $(FLAGS) $(OBJS) $(LIB_MLX_ARCHIVE) $(LIBFT_ARCHIVE) -o $(NAME) $(FLAGS_MINI)

$(LIB_MLX_ARCHIVE):
	@make -C $(LIB_MLX_PATH)

$(LIBFT_ARCHIVE):
	@make bonus -C $(LIBFT_PATH)

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(LIB_MLX_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

run: all
	@./$(NAME)

runAA: all
	@./$(NAME) 100

debug: all
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re