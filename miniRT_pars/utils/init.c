/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:55:02 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 06:59:31 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	p_scene(char *filename, t_scene *scene)
{
	int	fd;

	get_fd(filename, &fd, 1, scene);
	scene->obj_lst = NULL;
	scene->scene_len = get_scene_len(fd);
	scene->scene_arr = (char **)malloc(sizeof(char *) * (scene->scene_len + 1));
	if (!(scene->scene_arr))
	{
		ft_putstr_err("Error : Malloc error\n");
		exit(1);
	}
	get_fd(filename, &fd, 2, scene);
	get_scene(fd, scene);
	validate_scene(scene);
	parse(scene);
}

t_vec3	make_coord(int index, char **splitted_obj,
	int is_normal_vect, t_scene *scene)
{
	t_vec3	coord;
	char	**arr_coord;

	arr_coord = ft_split(splitted_obj[index], ',');
	if (!is_valid_float(arr_coord[0]) || !is_valid_float(arr_coord[1])
		|| !is_valid_float(arr_coord[2]))
		free_vec3_error(scene, arr_coord, splitted_obj, E_FLOAT);
	coord.x = ft_atof(arr_coord[0]);
	coord.y = ft_atof(arr_coord[1]);
	coord.z = ft_atof(arr_coord[2]);
	free_2d_arr(arr_coord);
	if (is_normal_vect && (!is_in_range(coord.x, 'v')
			|| !is_in_range(coord.y, 'v')
			|| !is_in_range(coord.z, 'v')))
		free_vec3_error(scene, arr_coord, splitted_obj, E_NORM);
	return (coord);
}

t_vec3	make_rgb(int index, char **splitted_obj, t_scene *scene)
{
	t_vec3	color;
	char	**arr_coord;
	char	*str_coord;

	str_coord = splitted_obj[index];
	arr_coord = ft_split(str_coord, ',');
	if (!is_valid_float(arr_coord[0]) || !is_valid_float(arr_coord[1])
		|| !is_valid_float(arr_coord[2]))
		free_vec3_error(scene, arr_coord, splitted_obj, E_FLOAT);
	color.x = ft_atof(arr_coord[0]);
	color.y = ft_atof(arr_coord[1]);
	color.z = ft_atof(arr_coord[2]);
	free_2d_arr(arr_coord);
	if (!is_in_range(color.x, 'c') || !is_in_range(color.y, 'c')
		|| !is_in_range(color.z, 'c'))
		free_vec3_error(scene, arr_coord, splitted_obj, E_COL);
	return (make_color(color));
}
