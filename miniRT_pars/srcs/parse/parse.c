/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:33:13 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 02:15:43 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	obj_arg_error(t_scene *scene, char **splitted_obj, char *str)
{
	int	num;
	char	*shape;

	shape = splitted_obj[0];
	if (ft_strcmp3(shape, str, "A") && ft_strcmp3(shape, str, "C")
		&& ft_strcmp3(shape, str, "L") && ft_strcmp3(shape, str, "sp")
		&& ft_strcmp3(shape, str, "pl") && ft_strcmp3(shape, str, "cy"))
		return (0);
	if (!ft_strcmp(shape, "C"))
		num = 4;
	else if (!ft_strcmp(shape, "A"))
		num = 3;
	else if (!ft_strcmp(shape, "L"))
		num = 3;
	else if (!ft_strcmp(shape, "sp"))
		num = 4;
	else if (!ft_strcmp(shape, "pl"))
		num = 4;
	else if (!ft_strcmp(shape, "cy"))
		num = 6;
	if (ft_arr_len((void **)splitted_obj) != num)
		free_pars_error(scene, splitted_obj, "Invalid number of parameter\n");
	return (1);
}

t_cylinder	make_cylindre(t_scene *scene, char **splitted_obj)
{
	t_cylinder	tmp;

	tmp.shape = CYLINDRE;
	tmp.center_coord = make_coord(1, splitted_obj, 0, scene);
	tmp.normal_vector = make_coord(2, splitted_obj, 1, scene);
	tmp.color = make_rgb(5, splitted_obj, scene);
	tmp.diameter = ft_atofl(3, splitted_obj, scene);
	tmp.height = ft_atofl(4, splitted_obj, scene);
	return (tmp);
}

t_cylinder	make_sphere(t_scene *scene, char **splitted_obj)
{
	t_cylinder	tmp;

	tmp.shape = SPHERE;
	tmp.center_coord = make_coord(1, splitted_obj, 0, scene);
	tmp.diameter = ft_atofl(2, splitted_obj, scene);
	tmp.color = make_rgb(3, splitted_obj, scene);
	tmp.normal_vector = create_3dnull();
	tmp.height = 0;
	return (tmp);
}

t_cylinder	make_plan(t_scene *scene, char **splitted_obj)
{
	t_cylinder	tmp;

	tmp.shape = PLANE;
	tmp.center_coord = make_coord(1, splitted_obj, 0, scene);
	tmp.normal_vector = make_coord(2, splitted_obj, 1, scene);
	tmp.color = make_rgb(3, splitted_obj, scene);
	tmp.diameter = 0.0;
	tmp.height = 0;
	return (tmp);
}

t_cylinder	make_camera(t_scene *scene, char **splitted_obj)
{
	t_cylinder	tmp;

	tmp.shape = CAMERA;
	tmp.center_coord = make_coord(1, splitted_obj, 0, scene);
	tmp.normal_vector = make_coord(2, splitted_obj, 1, scene);
	tmp.diameter = ft_atofl(3, splitted_obj, scene);
	tmp.color = create_rgbnull();
	tmp.height = 0;
	return (tmp);
}

t_cylinder	make_light(t_scene *scene, char **splitted_obj)
{
	t_cylinder	tmp;

	tmp.shape = POINT_LIGHT;
	tmp.center_coord = make_coord(1, splitted_obj, 0, scene);
	tmp.diameter = ft_atofl(2, splitted_obj, scene);
	tmp.color = create_rgb(255.0, 255.0, 255.0);
	tmp.normal_vector = create_3dnull();
	tmp.height = 0;
	return (tmp);
}

t_cylinder	make_amient(t_scene *scene, char **splitted_obj)
{
	t_cylinder	tmp;

	tmp.shape = AMBIENT_LIGHT;
	tmp.diameter = ft_atofl(1, splitted_obj, scene);
	tmp.color = make_rgb(2, splitted_obj, scene);
	tmp.center_coord = create_3dnull();
	tmp.normal_vector = create_3dnull();
	tmp.height = 0;
	return (tmp);
}

void	parse(t_scene *scene)
{
	char		**scene_arr;
	char		**splitted_obj;
	t_cylinder	*obj;
	t_cylinder	tmp;

	scene_arr = scene->scene_arr;
	print_2d_arr(scene->scene_arr);
	while (*scene_arr)
	{
		splitted_obj = ft_split_space(*scene_arr);
		if (obj_arg_error(scene, splitted_obj, "L"))
			tmp = make_light(scene, splitted_obj);
		else if (obj_arg_error(scene, splitted_obj, "A"))
			tmp = make_amient(scene, splitted_obj);
		else if (obj_arg_error(scene, splitted_obj, "C"))
			tmp = make_camera(scene, splitted_obj);
		else if (obj_arg_error(scene, splitted_obj, "cy"))
			tmp = make_cylindre(scene, splitted_obj);
		else if (obj_arg_error(scene, splitted_obj, "sp"))
			tmp = make_sphere(scene, splitted_obj);
		else if (obj_arg_error(scene, splitted_obj, "pl"))
			tmp = make_plan(scene, splitted_obj);
		else
			free_vec3_error(scene, splitted_obj, NULL, "You can only enter [C, L, A, sp, pl, cy] as element of the scene.\n");
		obj = (t_cylinder *)malloc(sizeof(t_cylinder));
		obj->shape = tmp.shape;
		obj->center_coord = tmp.center_coord;
		obj->normal_vector = tmp.normal_vector;
		obj->color = tmp.color;
		obj->diameter = tmp.diameter;
		obj->height = tmp.height;
		ft_lstadd_back(&(scene->cylinder_lst), ft_lstnew(obj));
		free_2d_arr(splitted_obj);
		scene_arr++;
	}
}
