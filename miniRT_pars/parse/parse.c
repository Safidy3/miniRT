/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:33:13 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/06 09:49:34 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	obj_arg_error(t_scene *scene, char **splitted_obj, char *str)
{
	int		num;
	char	*shape;

	num = 0;
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
		num = 6;
	else if (!ft_strcmp(shape, "pl"))
		num = 6;
	else if (!ft_strcmp(shape, "cy"))
		num = 8;
	if (ft_arr_len((void **)splitted_obj) != num)
		free_pars_error(scene, splitted_obj, E_NUM_PARAM);
	return (1);
}

void	get_obj_parameter(t_scene *scene, t_obj *tmp, char **splitted_obj)
{
	if (obj_arg_error(scene, splitted_obj, "L"))
		*tmp = make_light(scene, splitted_obj);
	else if (obj_arg_error(scene, splitted_obj, "A"))
		*tmp = make_amient(scene, splitted_obj);
	else if (obj_arg_error(scene, splitted_obj, "C"))
		*tmp = make_camera(scene, splitted_obj);
	else if (obj_arg_error(scene, splitted_obj, "cy"))
		*tmp = make_cylindre(scene, splitted_obj);
	else if (obj_arg_error(scene, splitted_obj, "sp"))
		*tmp = make_sphere(scene, splitted_obj);
	else if (obj_arg_error(scene, splitted_obj, "pl"))
		*tmp = make_plan(scene, splitted_obj);
	else
		free_vec3_error(scene, splitted_obj, NULL, E_ID);
}

void	parse(t_scene *scene)
{
	char	**scene_arr;
	char	**splitted_obj;
	t_obj	*obj;
	t_obj	tmp;

	scene_arr = scene->scene_arr;
	while (*scene_arr)
	{
		splitted_obj = ft_split_space(*scene_arr);
		get_obj_parameter(scene, &tmp, splitted_obj);
		obj = (t_obj *)malloc(sizeof(t_obj));
		obj->shape = tmp.shape;
		obj->center = tmp.center;
		obj->normal_vector = tmp.normal_vector;
		obj->color = tmp.color;
		obj->diameter = tmp.diameter;
		obj->brightness = tmp.brightness;
		obj->height = tmp.height;
		obj->metalness = tmp.metalness;
		ft_lstadd_back(&(scene->obj_lst), ft_lstnew(obj));
		free_2d_arr(splitted_obj);
		scene_arr++;
	}
}
