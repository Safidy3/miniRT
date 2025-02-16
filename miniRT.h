/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:50:44 by safandri          #+#    #+#             */
/*   Updated: 2025/02/13 15:15:26 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "minilibx-linux/mlx.h"
#include "stdio.h"
#include "unistd.h"
#include <stdlib.h>
#include <math.h>

#define WIDTH 960
#define HEIGHT 720
#define FOV 60
#define NEAR 0.1
#define FAR 100.0
#define M_PI 3.14159265358979323846

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

typedef struct s_data
{
	void    *mlx;               // Pointer to the MLX instance
	void    *win;               // Pointer to the window instance
	void    *img;               // Pointer to the image
	char    *addr;              // Address of the image data
	int     bits_per_pixel;     // Bits per pixel (color depth)
	int     line_length;        // Length of a line in bytes
	int     endian;             // Endianess of the pixel data
}			t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(t_data *img, t_vec3 p0, t_vec3 p1, int color);

void	print_vec3(t_vec3 v, char *name);
t_vec3	create_vec3(float x,float y, float z);
float	vec3_len(t_vec3 v);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_add3(t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub3(t_vec3 a, t_vec3 b, t_vec3 c);

t_vec3	vec3_mult(t_vec3 a, t_vec3 b);
t_vec3	vec3_mult_float(t_vec3 a, float b);
t_vec3	vec3_div(t_vec3 a, t_vec3 b);
t_vec3	vec3_div_float(t_vec3 a, float b);

t_vec3	vec3_normalize(t_vec3 v);
t_vec3	unit_vector(t_vec3 v);
float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

t_ray	create_ray(t_vec3 origin, t_vec3 dir);
t_vec3	ray_point_at(t_vec3 origin, t_vec3 dir, float t);

t_mat4	mat4_look_at(t_vec3 pos, t_vec3 target, t_vec3 up);
t_vec3	mat4_mult_vec3(t_mat4 mat, t_vec3 v);
t_mat4	mat4_perspective(float fov, float aspect, float near, float far);


void	render_triangle(t_data *img, t_mat4 view, t_mat4 projection);
void	render_cube(t_data *img, t_mat4 view, t_mat4 projection);

#endif