PARS_ROOT = ./miniRT_pars

ERROR_PATH = $(PARS_ROOT)/error-handling
GNL_PATH = $(PARS_ROOT)/get_next_line
UTILS_PATH = $(PARS_ROOT)/utils
PARSE_PATH = $(PARS_ROOT)/parse

PARSING_SRCS = $(PARS_ROOT)/miniRT.c $(PARS_ROOT)/data_create.c \
				$(ERROR_PATH)/scene.c $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c \
				$(UTILS_PATH)/scene.c $(UTILS_PATH)/init.c $(UTILS_PATH)/protected.c \
				$(UTILS_PATH)/elt_value_format.c $(UTILS_PATH)/data_manip.c $(UTILS_PATH)/free.c \
				$(PARSE_PATH)/parse.c $(PARSE_PATH)/light_parser.c $(PARSE_PATH)/object_parser.c

TRANSFORM_SRCS = ./object_transform/transform.c ./object_transform/key_hooks.c ./object_transform/hooks_utils.c

OPTION_WINDOW_SRCS = ./option_window/print_utils.c ./option_window/option_window.c

VECTORS_SRCS = ./vector_maths/ray_utils.c ./vector_maths/vect_add.c ./vector_maths/vect_function.c ./vector_maths/vect_mult_div.c\
				./vector_maths/vect_sub.c ./vector_maths/vect_utils.c

OBJECTS_SRCS = ./objects/create_objects.c ./objects/obj_light.c ./objects/thread_copy_world.c\
				./objects/obj_camera.c ./objects/obj_cylinder.c ./objects/obj_plane.c ./objects/obj_sphere.c

MATERIALS_SRCS = ./materials/materials.c ./materials/material_utils.c

RENDER_SRCS = ./render/render_utils.c ./render/render_debug.c\
			  ./render/thread_render.c ./render/render_utils2.c ./render/thread_render_utils.c

SRCS = main.c data_free.c  exemple_sceen.c print_debug.c\
		$(VECTORS_SRCS) $(OBJECTS_SRCS) $(MATERIALS_SRCS) $(RENDER_SRCS) $(OPTION_WINDOW_SRCS) $(TRANSFORM_SRCS) $(PARSING_SRCS)

FLAGS = -Wall -Werror -Wextra -I/usr/include
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

debug: all
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

datarace_debug: all
	@valgrind --tool=helgrind ./$(NAME)

.PHONY: all clean fclean re