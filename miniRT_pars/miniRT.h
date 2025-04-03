/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:42:20 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 03:59:01 by safandri         ###   ########.fr       */
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

# define E_FLOAT "Ivalid float number found\n"
# define E_NORM "Normal vector should be in range [-1, 1]\n"
# define E_PARAM "Diameter/radius/brightness can not be negative\n"
# define E_COL "R, G, B color should be in range [0, 255]\n"
# define E_OBJ_CAP "Error : Element with capital letter id should be only declared once.\n"
# define E_NUM_PARAM "Number of parameter of an object is incorect.\n"

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
typedef struct s_obj		t_obj;

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

struct						s_obj
{
	int						shape;
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
	t_list					*cylinder_lst;
};

t_3dcoord					create_3d(float x, float y, float z);
t_3dcoord					create_3dnull(void);
t_rgb						create_rgb(float x, float y, float z);
t_rgb						create_rgbnull(void);
t_3dcoord					make_coord(int index, char **splitted_obj, int is_normal_vect, t_scene *scene);
float						ft_atofl(int index, char **arr_obj, t_scene *scene);
t_rgb						make_rgb(int index, char **splitted_obj, t_scene *scene);

t_obj						make_cylindre(t_scene *scene, char **splitted_obj);
t_obj						make_sphere(t_scene *scene, char **splitted_obj);
t_obj						make_plan(t_scene *scene, char **splitted_obj);
t_obj						make_camera(t_scene *scene, char **splitted_obj);
t_obj						make_light(t_scene *scene, char **splitted_obj);
t_obj						make_amient(t_scene *scene, char **splitted_obj);

/* TODO: remove this for last push */
void						print_2d_arr(char **arr);
void						print_cylinder(t_obj *cylinder);

/* ./srcs/utils/scene.c */
int							get_scene_len(int fd);
void						get_scene(int fd, t_scene *scene);
void						validate_scene(t_scene *scene);

/* ./srcs/utils/utils.c */
void						p_scene(char *filename, t_scene *scene);

/* ./srcs/utils/protected.c */
void						get_fd(char *filename, int *fd, int is_first_fd,
								t_scene *scene);

/* ./srcs/parse */
void						parse(t_scene *scene);

/* ./srcs/utils/data_manip.c */
int							is_valid_float(char *str);

/* ./srcs/utils/free.c */
void						free_2d_arr(char **arr);
void						clear_plane(void *g_plane_lst);
void						clear_sphere(void *g_sphere_lst);
void						clear_cylinder(void *g_cylinder_lst);
void						clear_p_scene(t_scene *scene);

/* ./srcs/elt_value_format */
void						check_arg_nbr(char **splitted_elt, int arg_number,
								t_scene *scene);
void						check_dup_capital(char **scene);

void						free_pars_error(t_scene *scene, char **splitted_elt, char *str);
void						free_vec3_error(t_scene *scene, char **splitted_elt, char **splitted_obj, char *str);

#endif