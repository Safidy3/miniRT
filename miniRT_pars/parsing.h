/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 06:35:47 by safandri          #+#    #+#             */
/*   Updated: 2025/04/03 09:44:20 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "./srcs/libs/get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

# define E_FLOAT "Ivalid float number found\n"
# define E_NORM "Normal vector should be in range [-1, 1]\n"
# define E_PARAM "Diameter/radius/brightness can not be negative\n"
# define E_COL "R, G, B color should be in range [0, 255]\n"
# define E_OBJ_CAP "Error : Element with capital letter \
	should be only declared once.\n"
# define E_NUM_PARAM "The number of parameter of an object is incorect.\n"
# define E_ID "You can only enter [C, L, A, sp, pl, cy] as \
	element of the scene.\n"

enum	e_shape
{
	SPHERE,
	PLANE,
	CYLINDRE,
	POINT_LIGHT,
	AMBIENT_LIGHT,
	CAMERA
};

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_rgb
{
	float		r;
	float		g;
	float		b;
}				t_rgb;

typedef struct	s_obj
{
	int			shape;
	t_vec3		center;
	t_vec3		normal_vector;
	float		diameter;
	float		height;
	t_vec3		color;
}				t_obj;

typedef struct	s_scene
{
	int			scene_len;
	char		**scene_arr;
	t_list		*obj_lst;
}				t_scene;

t_vec3			create_3d(float x, float y, float z);
t_vec3			create_3dnull(void);
t_vec3			create_rgb(float x, float y, float z);
t_vec3			make_coord(int index, char **splitted_obj,
					int is_normal_vect, t_scene *scene);
float			ft_atofl(int index, char **arr_obj, t_scene *scene);
t_vec3			make_rgb(int index, char **splitted_obj, t_scene *scene);

t_obj			make_cylindre(t_scene *scene, char **splitted_obj);
t_obj			make_sphere(t_scene *scene, char **splitted_obj);
t_obj			make_plan(t_scene *scene, char **splitted_obj);
t_obj			make_camera(t_scene *scene, char **splitted_obj);
t_obj			make_light(t_scene *scene, char **splitted_obj);
t_obj			make_amient(t_scene *scene, char **splitted_obj);

/* TODO: remove this for last push */
void			print_2d_arr(char **arr);
void			print_cylinder(t_obj *cylinder);
void			print_obj_list(t_scene *scene);

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
void			check_arg_nbr(char **splitted_elt, int arg_number, t_scene *scene);
void			check_dup_capital(char **scene);

void			free_pars_error(t_scene *scene, char **splitted_elt, char *str);
void			free_vec3_error(t_scene *scene, char **splitted_elt,
					char **splitted_obj, char *str);

void			get_pars(t_scene *scene, int argc, char **argv);

#endif