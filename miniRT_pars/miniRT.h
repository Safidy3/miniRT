/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:42:20 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/02 20:32:42 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./srcs/includes/error_handling.h"
# include "./srcs/includes/global.h"
# include "./srcs/libs/get_next_line/get_next_line.h"
# include "./srcs/libs/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

enum	e_shape
{
	SPHERE,
	PLANE,
	CYLINDRE,
	POINT_LIGHT,
	AMBIENT_LIGHT,
	CAMERA
};

typedef struct s_scene		t_scene;

typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_light		t_light;

typedef struct s_plane		t_plane;
typedef struct s_sphere		t_sphere;
typedef struct s_cylinder	t_cylinder;

typedef struct s_3dcoord	t_3dcoord;
typedef struct s_rgb		t_rgb;

struct						s_3dcoord
{
	float					x;
	float					y;
	float					z;
};

struct						s_rgb
{
	float					red;
	float					green;
	float					blue;
};

struct						s_ambient
{
	char					id;
	float					brightness;
	t_rgb					color;
};

struct						s_camera
{
	char					id;
	t_3dcoord				center_coord;
	t_3dcoord				vector_dir;
	float					fov;
};

struct						s_light
{
	char					id;
	t_3dcoord				center_coord;
	float					brightness;
	t_rgb					color;
};

struct						s_plane
{
	char					id[3];
	t_3dcoord				center_coord;
	t_3dcoord				normal_vector;
	t_rgb					color;
};

struct						s_sphere
{
	char					id[3];
	t_3dcoord				center_coord;
	float					diameter;
	t_rgb					color;
};

struct						s_cylinder
{
	char					id[3];
	t_3dcoord				center_coord;
	t_3dcoord				normal_vector;
	float					diameter;
	float					height;
	t_rgb					color;
};

struct						s_scene
{
	int						scene_len;
	char					**scene_arr;
	t_ambient				ambient;
	t_camera				camera;
	t_light					light;
	t_plane					plane;
	t_list					*sphere_lst;
	t_list					*cylinder_lst;
	t_list					*plane_lst;
};

/* TODO: remove this for last push */
void						print_2d_arr(char **arr);
void						print_sphere(t_sphere *sphere);
void						print_cylinder(t_cylinder *cylinder);

/* ./srcs/utils/scene.c */
int							get_scene_len(int fd);
void						get_scene(int fd, t_scene *scene);
void						validate_scene(t_scene *scene);

/* ./srcs/utils/utils.c */
void						p_scene(char *filename, t_scene *scene);

/* ./srcs/utils/protected.c */
void						get_fd(char *filename, int *fd, int is_first_fd,
								t_scene *scene);

/* ./srcs/utils/init.c */
void						init_sphere(t_sphere *sphere);
void						init_cylinder(t_cylinder *cylinder);
void						init_plane(t_plane *plane);
void						print_plane(t_plane *plane);

/* ./srcs/parse */
void						parse(t_scene *scene);
void						ambient_parser(t_ambient *ambiant, char *scene_elt,
								t_scene *scene);
void						camera_parser(t_camera *camera, char *scene_elt,
								t_scene *scene);
void						light_parser(t_light *light, char *scene_elt,
								int is_bonus, t_scene *scene);

/* ./srcs/parse/primitives */
void						cylinder_parser(char *scene_elt, t_scene *scene);
void						plane_parser(char *scene_elt, t_scene *scene);
void						sphere_parser(char *scene_elt, t_scene *scene);

/* ./srcs/utils/data_manip.c */
int							is_valid_float(char *str);
float						ft_atof(char *str);

/* ./srcs/utils/free.c */
void						free_2d_arr(char **arr);
void						clear_plane(void *g_plane_lst);
void						clear_sphere(void *g_sphere_lst);
void						clear_cylinder(void *g_cylinder_lst);
void						clear_p_scene(t_scene *scene);

/* ./srcs/utils/elt_value_format.c */
int							get_3dcoord(t_3dcoord *coord, char **arr_coord,
								int is_normal_vect);
void						get_rgb_color(t_rgb *color, char **arr_coord,
								t_scene *scene);

/* ./srcs/elt_value_format */
void						check_arg_nbr(char **splitted_elt, int arg_number,
								t_scene *scene);
void						check_dup_capital(char **scene);

void						free_pars_error(t_scene *scene, char **splitted_elt, char *str);

#endif