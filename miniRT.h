/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:50:44 by safandri          #+#    #+#             */
/*   Updated: 2025/02/22 16:40:15 by safandri         ###   ########.fr       */
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
#define FOV 60
#define NEAR 0.1
#define FAR 100.0
#define M_PI 3.14159265358979323846
#define MIN_T 0.001
#define MAX_T (float)INT_MAX
#define NUM_THREADS 8

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

typedef struct s_material
{
	t_vec3	albedo;
	t_vec3	metal;
	t_vec3	lambertian;

	int		use_metal;
}			t_material;

typedef struct s_hit_shpere
{
	int				id;
	t_vec3			center;
	float			radius;

	t_vec3			albedo;
	float			metal_fuzz;
	int				use_metal;

	t_material		material;
	t_hit_record	hit_record;
}					t_hit_shpere;


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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(t_data *img, t_vec3 p0, t_vec3 p1, int color);

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
t_vec3	vec3_div(t_vec3 a, t_vec3 b);
t_vec3	vec3_div_float(t_vec3 a, float b);

t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_unit(t_vec3 v);
float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);


t_vec3	vec3_random_in_unit_object();

t_ray	create_ray(t_vec3 origin, t_vec3 dir);
t_vec3	ray_point_at(t_ray ray, float t);


int	metal_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_shpere obj);
int	lamberian_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_shpere obj);


t_mat4	mat4_look_at(t_vec3 pos, t_vec3 target, t_vec3 up);
t_vec3	mat4_mult_vec3(t_mat4 mat, t_vec3 v);
t_mat4	mat4_perspective(float fov, float aspect, float near, float far);

void	render_triangle(t_data *img, t_mat4 view, t_mat4 projection);
void	render_cube(t_data *img, t_mat4 view, t_mat4 projection);


t_hit_shpere	create_sphere(t_vec3 center, float radius);
void			scene_add_sphere(t_list **world, t_vec3 center, float radius, t_vec3 albedo, int use_metal, int metal_fuzz);

void			delete_obj(void *obj);
void			clear_sceen(t_list **world);
t_hit_shpere	*make_obj(t_list *obj);


t_material	create_material(t_vec3 albedo, t_vec3 metal, t_vec3 lambertian, int use_metal);

void	free_data(t_data *data);
int		close_window(void *param);

#endif