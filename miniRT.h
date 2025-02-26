/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:50:44 by safandri          #+#    #+#             */
/*   Updated: 2025/02/26 17:26:25 by safandri         ###   ########.fr       */
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
#define MAX_RECURS_DEPTH 50
#define ANTIALIASING_SAMPLES 100
#define NUM_THREADS 8

enum	e_shape
{
	SPHERE,
	PLANE
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
}			t_cam;

typedef struct s_hit_record
{
	float			t;
	t_vec3			hit_point;
	t_vec3			normal;
	t_vec3			color;
}					t_hit_record;

typedef struct s_hit_object
{
	int				id;
	t_vec3			center;
	float			radius;

	t_vec3			plane[4];

	t_vec3			color;
	float			material_parameter;
	int				material;

	int				use_texture;

	t_hit_record	hit_record;
}					t_hit_object;


typedef struct s_data
{
	void    *mlx;
	void    *win;
	void    *img;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
	int thread_id;
	t_cam	cam;
	t_list	*world;
}			t_data;

/******************************************************/

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	target;
	t_vec3	up;
}			t_camera;

typedef struct s_mat4
{
	float	m[4][4];
}			t_mat4;

/******************************************************/

void	my_mlx_pixel_put(t_data *data, int x, int y, t_vec3 r_col);
// void	draw_line(t_data *img, t_vec3 p0, t_vec3 p1, int color);

void	print_vec3(t_vec3 v, char *name);
t_vec3	create_vec3(float x,float y, float z);
float	vec3_len(t_vec3 v);
float	vec3_squared_len(t_vec3 v);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_add3(t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub3(t_vec3 a, t_vec3 b, t_vec3 c);

t_vec3	vec3_mult(t_vec3 a, t_vec3 b);
t_vec3	vec3_mult_float(t_vec3 a, float b);
t_vec3	vec3_safe_mult_float(t_vec3 a, float b);
t_vec3	vec3_div(t_vec3 a, t_vec3 b);
t_vec3	vec3_div_float(t_vec3 a, float b);

t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_unit(t_vec3 v);
float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
int		isNullVec3(t_vec3 v);


t_vec3	vec3_random_in_unit_object();

t_ray	create_ray(t_vec3 origin, t_vec3 dir);
t_vec3	ray_point_at(t_ray ray, float t);


int	metal_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_object obj);
int	lamberian_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_object obj);
int	dielectric_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_object obj);
int	light_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_object obj);


t_mat4	mat4_look_at(t_vec3 pos, t_vec3 target, t_vec3 up);
t_vec3	mat4_mult_vec3(t_mat4 mat, t_vec3 v);
t_mat4	mat4_perspective(float fov, float aspect, float near, float far);

void	render_triangle(t_data *img, t_mat4 view, t_mat4 projection);
void	render_cube(t_data *img, t_mat4 view, t_mat4 projection);

t_cam	create_camera(t_vec3 origin, t_vec3 look_at);

t_hit_object	create_sphere(t_vec3 center, float radius);
int				hit_sphere(t_hit_object *obj, const t_ray r, t_hit_record *hit_rec);
void			scene_add_sphere(t_list **world, t_vec3 center, float radius, t_vec3 color, int use_texture, float material_parameter, int material);


int				hit_plane(t_hit_object *obj, const t_ray r, t_hit_record *hit_rec);
t_hit_object	create_plane(t_vec3 x0, t_vec3 x1, t_vec3 y0, t_vec3 y1);

void			delete_obj(void *obj);
void			clear_sceen(t_list **world);
t_hit_object	*make_obj(t_list *obj);


void	free_data(t_data *data);
int		close_window(void *param);

#endif