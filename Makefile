VECTORS_SRCS = ./vector_maths/ray_utils.c ./vector_maths/vect_add.c ./vector_maths/vect_function.c ./vector_maths/vect_mult_div.c\
				./vector_maths/vect_sub.c ./vector_maths/vect_utils.c

OBJECTS_SRCS = ./objects/create_objects.c ./objects/hit_objects.c

MATERIALS_SRCS = ./materials/materials.c

RENDER_SRCS = ./render/render_image.c ./render/render_utils.c

SRCS = main.c data_free.c\
		$(VECTORS_SRCS) $(OBJECTS_SRCS) $(MATERIALS_SRCS) $(RENDER_SRCS)

FLAGS = -Wall -Werror -Wextra -I/usr/include
# FLAGS = -I/usr/include
FLAGS_MINI = -Lmlx_linux -Imlx_linux -lXext -lX11 -lm -lz

LIB_MLX_PATH = ./minilibx-linux
LIB_MLX_ARCHIVE = $(LIB_MLX_PATH)/libmlx.a

LIBFT_PATH = ./libft
LIBFT_ARCHIVE = $(LIBFT_PATH)/libft.a

OBJS = $(SRCS:.c=.o)
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