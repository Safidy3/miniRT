/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 06:35:47 by safandri          #+#    #+#             */
/*   Updated: 2025/04/10 20:35:06 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <math.h>
# include "unistd.h"
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include "../minilibx-linux/mlx.h"
# include "./get_next_line/get_next_line.h"
# include "../libft/libft.h"

// #define WIDTH 1280
// #define HEIGHT 720
# define WIDTH 640
# define HEIGHT 310
# define FOV 90
# define NEAR 0.1
# define FAR 100.0
# define M_PI 3.14159265358979323846
# define MIN_T 0.01
# define MAX_T INT_MAX
# define MAX_RECURS_DEPTH 10
# define ANTIALIASING_SAMPLES 100

# define E_ARG "Ivalid argument found\n"
# define E_FLOAT "Ivalid float number found\n"
# define E_NORM "Direction should be normalized vector\n"
# define E_BRIGHTNESS "Brightness should be in range [0, 1]\n"
# define E_PARAM "Diameter/radius/brightness can not be negative\n"
# define E_COL "R, G, B color should be in range [0, 255]\n"
# define E_OBJ_CAP "Error : Element with capital letter \
	should be declared once.\n"
# define E_NUM_PARAM "The number of parameter of an object is incorect.\n"
# define E_ID "You can only enter [C, L, A, sp, pl, cy] as \
	element of the scene.\n"

enum	e_material
{
	LAMBERTIAN,
};

enum	e_shape
{
	SPHERE,
	PLANE,
	CYLINDRE,
	POINT_LIGHT,
	AMBIENT_LIGHT,
	CAMERA
};

typedef struct s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct s_rgb
{
	float		r;
	float		g;
	float		b;
}				t_rgb;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	t_vec3	point_at;
}				t_ray;

typedef struct s_cam
{
	t_vec3	lower_l;
	t_vec3	horizintal;
	t_vec3	vertical;
	t_vec3	origin;
	t_vec3	direction;
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	float	fov;
}			t_cam;

typedef struct s_hit_record
{
	float			t;
	t_vec3			hit_point;
	t_vec3			normal;
	t_vec3			color;
}					t_hit_record;

typedef struct s_obj_proprieties
{
	t_vec3	color;
	float	parameter;
	int		material;
	int		use_texture;
}			t_proprieties;

typedef struct s_object
{
	int				id;
	int				shape;
	t_vec3			center;
	t_vec3			direction;
	float			radius;
	float			height;
	t_proprieties	proprieties;
	t_hit_record	hit_record;
}					t_object;

typedef struct s_edge_object
{
	t_object	*obj;
	t_object	*obj2;
	t_object	*obj3;
	t_object	*obj4;
	t_object	*obj5;
}				t_edge_object;

typedef struct s_data
{
	void					*mlx;
	void					*win;
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
	t_ray					**camera_rays;
	t_object				***hit_objects;
	t_object				*seleced_object;
	t_cam					cam;
	t_list					*world;
}							t_data;

typedef struct s_put_vec3
{
	char	str[20];
	char	x[20];
	char	y[20];
	char	z[20];
	char	f[20];
	int		padding;
	int		px;
	int		py;
}			t_put_vec3;

typedef struct s_hit_equation
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t;
	float	t2;
}			t_hit_equation;

typedef struct s_obj
{
	int			shape;
	t_vec3		center;
	t_vec3		normal;
	float		brightness;
	float		diameter;
	float		height;
	t_vec3		color;
}				t_obj;

typedef struct s_scene
{
	int			scene_len;
	char		**scene_arr;
	t_list		*obj_lst;
	t_data		*data;
}				t_scene;

/******************************************************/

void			print_vec3(t_vec3 v, char *name);
t_vec3			create_vec3(float x, float y, float z);
t_vec3			create_nullvec(void);
float			vec3_len(t_vec3 v);
float			vec3_squared_len(t_vec3 v);
t_vec3			color_add(t_vec3 a, t_vec3 b);
t_vec3			vec3_add(t_vec3 a, t_vec3 b);
t_vec3			vec3_add3(t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3			vec3_add_float(t_vec3 a, float f);
t_vec3			vec3_sub(t_vec3 a, t_vec3 b);
t_vec3			vec3_sub3(t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3			vec3_sub_float(t_vec3 a, float f);
t_vec3			vec3_mult(t_vec3 a, t_vec3 b);
t_vec3			vec3_mult_float(t_vec3 a, float b);
t_vec3			vec3_safe_mult_float(t_vec3 a, float b);
t_vec3			vec3_div(t_vec3 a, t_vec3 b);
t_vec3			vec3_div_float(t_vec3 a, float b);
t_vec3			vec3_normalize(t_vec3 v);
t_vec3			vec3_unit(t_vec3 v);
float			vec3_dot(t_vec3 a, t_vec3 b);
t_vec3			vec3_cross(t_vec3 a, t_vec3 b);
t_vec3			vec3_inverse(t_vec3 v);
int				is_null_vec(t_vec3 v);

t_ray			create_ray(t_vec3 origin, t_vec3 dir);
t_vec3			ray_point_at(t_ray ray, float t);

void			my_mlx_pixel_put(t_data *data, int x, int y, t_vec3 r_col);
void			erase_main_screen(t_data *data);
void			put_pixel_color(t_data *data);
t_vec3			ray_casted_color(t_data *data, int x, int y);
int				handle_key(int keycode, void *param);
int				mouse_hook(int keycode, int x, int y, void *param);
t_vec3			vec3_random_in_unit_object(void);

t_proprieties	create_proprieties(t_vec3 color, int material,
					float parameter, int use_texture);

void			create_camera(t_data *data, t_vec3 origin,
					t_vec3 look_at, float fov);
void			update_camera(t_data *data, t_vec3 origin,
					t_vec3 look_at, float fov);
t_object		*create_obj_cam(t_vec3 origin, t_vec3 direction, float fov);
t_object		*create_sphere(t_vec3 center, float diameter);
t_object		*create_plane(t_vec3 center, t_vec3 direction);
t_object		*create_cylinder(t_vec3 center, t_vec3 direction,
					float diameter, float height);
t_object		*create_pl(t_vec3 center, t_vec3 color, float brightness);
t_object		*create_al(t_vec3 color, float brightness);

void			scene_add_obj(t_list **world, t_object *obj,
					t_proprieties prts);
int				hit_obj(t_object *obj, const t_ray r,
					t_hit_record *hit_rec);
void			delete_obj(void *obj);
t_object		*make_obj(t_list *obj);
t_object		*get_first_hit_obj(const t_ray r, t_list *world);
t_object		*get_light(t_list *og_world, int light_type);

int				hit_sphere(t_object *obj, const t_ray r, t_hit_record *hit_rec);
int				hit_plane(t_object *obj, const t_ray r, t_hit_record *hit_rec);
int				hit_cylinder(t_object *obj, const t_ray r,
					t_hit_record *hit_rec);

void			translate_object(t_data *data, t_vec3 translation);
void			rotate_x(t_data *data, float theta);
void			rotate_y(t_data *data, float theta);
void			rotate_z(t_data *data, float theta);
void			object_translation(int keycode, t_data *data);
void			object_rotation(int keycode, t_data *data);

void			compute_camera_rays(t_data *data);
void			compute_objects_hits(t_data *data);
void			compute_objects_hits_debug(t_data *data);

void			clear_sceen(t_list **world);
void			free_data(t_data *data);
int				close_window(void *param);

void			put_pixel_color_debug(t_data *data);
t_vec3			color_debug(t_data *data, int x, int y);

/************************************************* */

t_vec3			create_3d(float x, float y, float z);
t_vec3			create_3dnull(void);
t_vec3			create_rgb(float x, float y, float z);
t_vec3			make_coord(int index, char **splitted_obj,
					int is_normal_vect, t_scene *scene);
float			ft_atofl(int index, char **arr_obj, t_scene *scene);
t_vec3			make_rgb(int index, char **splitted_obj, t_scene *scene);
t_vec3			make_color(t_vec3 a);
int				check_normilized(t_vec3 v);

t_obj			make_cylindre(t_scene *scene, char **splitted_obj);
t_obj			make_sphere(t_scene *scene, char **splitted_obj);
t_obj			make_plan(t_scene *scene, char **splitted_obj);
t_obj			make_camera(t_scene *scene, char **splitted_obj);
t_obj			make_light(t_scene *scene, char **splitted_obj);
t_obj			make_amient(t_scene *scene, char **splitted_obj);

/* ./srcs/utils/scene.c */
int				get_scene_len(int fd);
void			get_scene(int fd, t_scene *scene);
void			validate_scene(t_scene *scene);

/* ./srcs/utils/utils.c */
void			p_scene(char *filename, t_scene *scene);

/* ./srcs/utils/protected.c */
void			get_fd(char *filename, int *fd, int is_first_fd,
					t_scene *scene);

/* ./srcs/parse */
void			parse(t_scene *scene);

/* ./srcs/utils/data_manip.c */
int				is_valid_float(char *str);

/* ./srcs/utils/free.c */
void			free_2d_arr(char **arr);
void			clear_plane(void *g_plane_lst);
void			clear_sphere(void *g_sphere_lst);
void			clear_cylinder(void *g_cylinder_lst);
void			clear_p_scene(t_scene *scene);

int				is_char_type_id(char c);
int				is_str_type_id(char *str);
int				is_in_range(float nbr, char c);
int				validate_scene_name(char *scene);
int				is_valid_id(char **scene);

/* ./srcs/elt_value_format */
void			check_arg_nbr(char **splitted_elt,
					int arg_number, t_scene *scene);
void			check_dup_capital(char **scene);

void			free_pars_error(t_scene *scene, char **splitted_elt, char *str);
void			free_vec3_error(t_scene *scene, char **splitted_elt,
					char **splitted_obj, char *str);

void			get_pars(t_scene *scene, int argc, char **argv);

void			print_split(char **s);

#endif