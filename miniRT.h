/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:50:44 by safandri          #+#    #+#             */
/*   Updated: 2025/03/27 12:58:19 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "minilibx-linux/mlx.h"
#include "libft/libft.h"
#include "stdio.h"
#include "unistd.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>

// #define WIDTH 1280
// #define HEIGHT 720
#define WIDTH 640
#define HEIGHT 310
#define FOV 90
#define NEAR 0.1
#define FAR 100.0
#define M_PI 3.14159265358979323846
#define MIN_T 0.001
#define MAX_T (float)INT_MAX
#define MAX_RECURS_DEPTH 10
#define ANTIALIASING_SAMPLES 100

enum	e_shape
{
	SPHERE,
	RECTANGLE,
	PLANE,
	INF_CYLINDRE,
	CYLINDRE,
	LIGHT_SOURCE,
	POINT_LIGHT,
	AMBIENT_LIGHT,
	CAMERA
};

enum	e_material
{
	LAMBERTIAN,
	METAL,
	DIELECTRIC,
	LIGHT
};

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}			t_vec3;

typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
}			t_rgb;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	t_vec3	point_at;
}				t_ray;

typedef struct s_cam
{
	t_vec3	lower_L;
	t_vec3	horizintal;
	t_vec3	vertical;
	t_vec3	origin;
	t_vec3	direction;
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
	float	material_parameter;
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

	t_vec3			plane[4];

	t_proprieties	proprieties;

	t_hit_record	hit_record;
}					t_object;

struct s_threads;
struct s_thread_data;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	
	void	*option_img;
	void	*option_win;
	char	*option_addr;
	int		o_bits_per_pixel;
	int		o_line_length;
	int		o_endian;

	t_ray		**camera_rays;
	t_object	***hit_objects;

	t_object	*seleced_object;

	struct s_threads *thread;
	struct s_thread_data	*thread_data;
	int		thread_id;

	int		AA_sample;
	t_cam	cam;
	t_list	*world;
}			t_data;

typedef struct s_threads
{
	pthread_t	threads[1000];
	int     	thread_num;
	int			thread_id;
	int			pix_unit;
	t_data		*data;
	pthread_mutex_t lock;
}	t_threads;

typedef struct s_thread_data
{
	t_data		*data;
	t_threads	*thread;
	int			thread_id;
}	t_thread_data;

/******************************************************/

int		handle_key(int keycode, void *param);
void	my_mlx_pixel_put(t_data *data, int x, int y, t_vec3 r_col);
void	put_pixel_color(t_data *data);
t_vec3	path_traced_color(const t_ray r, t_list *world, int depth, t_object	*src_obj);
t_vec3	compute_path_traced_color(t_data *data, int x, int y);
t_vec3	ray_casted_color(t_data *data, int x, int y);

void	print_vec3(t_vec3 v, char *name);
t_vec3	create_vec3(float x,float y, float z);
t_vec3	create_nullvec();
float	vec3_len(t_vec3 v);
float	vec3_squared_len(t_vec3 v);
t_vec3	color_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_add3(t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3	vec3_add_float(t_vec3 a, float f);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub3(t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3	vec3_sub_float(t_vec3 a, float f);
t_vec3	vec3_mult(t_vec3 a, t_vec3 b);
t_vec3	vec3_mult_float(t_vec3 a, float b);
t_vec3	vec3_safe_mult_float(t_vec3 a, float b);
t_vec3	vec3_div(t_vec3 a, t_vec3 b);
t_vec3	vec3_div_float(t_vec3 a, float b);

t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_unit(t_vec3 v);
float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
t_vec3	vec3_inverse(t_vec3 v);
int		isNullVec3(t_vec3 v);


void	put_vector3(t_data *data, t_vec3 center, char *str, int px, int *py);
void	put_obj_type(t_object *obj, t_data *data, int px, int *py);
void	put_float(t_data *data, float value, char *str, int px, int *py);
void	option_window(t_data *data, t_object *object);
void	erase_screen(t_data *data);

t_vec3	vec3_random_in_unit_object();

t_ray	create_ray(t_vec3 origin, t_vec3 dir);
t_vec3	ray_point_at(t_ray ray, float t);


int				metal_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_object obj);
int				lamberian_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_object obj);
int				dielectric_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_object obj);
int				light_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_object obj);
t_vec3			texture_checker(const t_vec3 point, t_vec3 color1, t_vec3 color2);
t_proprieties	create_proprieties(t_vec3 color, int material, float material_parameter, int use_texture);

void		create_camera(t_data *data, t_vec3 origin, t_vec3 look_at, float fov);
void		update_camera(t_data *data, t_vec3 origin, t_vec3 look_at, float fov);
t_cam		dup_camera(t_cam cam);
t_object	*create_obj_cam(t_vec3 origin, t_vec3 direction, float fov);
t_object	*create_sphere(t_vec3 center, float diameter);
t_object	*create_plane(t_vec3 center, t_vec3 direction);
t_object	*create_rectangle(t_vec3 x0, t_vec3 x1, t_vec3 y0, t_vec3 y1);
t_object	*create_inf_cylinder(t_vec3 center, t_vec3 direction, float radius);
t_object	*create_cylinder(t_vec3 center, t_vec3 direction, float diameter, float height);
t_object	*create_point_light(t_vec3 center, t_vec3 color, float brightness);
t_object	*create_ambient(t_vec3 color, float brightness);

void	translate_object(t_data *data, t_vec3 translation);
void	rotate_x(t_data *data, float theta);
void	rotate_y(t_data *data, float theta);
void	rotate_z(t_data *data, float theta);
void	compute_camera_rays(t_data *data);
void	compute_objects_hits(t_data *data);
void	compute_objects_hits_debug(t_data *data);

t_list		*deep_copy_world(t_list *world);
void		scene_add_obj(t_list **world, t_object *obj, t_proprieties prts);
int			hit_obj(t_object *obj, const t_ray r, t_hit_record *hit_rec);

void		sortlist(t_list **t);
void		list_swapp(t_list *a, t_list *b);
void		delete_obj(void *obj);
void		clear_sceen(t_list **world);
t_object	*make_obj(t_list *obj);

void	free_data(t_data *data);
int		close_window(void *param);

t_object	*get_first_hit_obj(const t_ray r, t_list *world);
t_object	*get_safe_hit_obj(const t_ray r, t_list *world);
int			isVoid(float x, float y, t_data *data);
t_object	*get_light(t_list *og_world, int light_type);

void	put_pixel_color_debug(t_data *data);
t_vec3	color_debug(t_data *data, int x, int y);

void	printT(t_list *t);

void	erase_main_screen(t_data *data);

/************  thread  *************/

void	add_sceen(t_data *data);
void	*thread_routing(void *param);
void	put_pixel_color_thread(t_threads *thread);
void	add_cornell_box(t_list **world);

#endif