/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:53:23 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/02 00:39:44 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

// TODO: double check leaks in each exit and add cool error message
void	camera_parser(t_camera *camera, char *scene_elt, t_scene *scene)
{
	char	**splitted_elt;
	char	**splitted_coord;

	splitted_elt = ft_split_space(scene_elt);
	check_arg_nbr(splitted_elt, 4, scene);
	camera->id = scene_elt[0];
	splitted_coord = ft_split(splitted_elt[1], ',');
	if (!is_valid_float(splitted_coord[0]) || !is_valid_float(splitted_coord[1])
		|| !is_valid_float(splitted_coord[2])
		|| !is_valid_float(splitted_elt[3]))
		free_pars_error(scene, splitted_elt, "Element value format error \n");
	camera->fov = ft_atof(splitted_elt[3]);
	if (!is_in_range(camera->fov, 'f'))
		free_pars_error(scene, splitted_elt, "Field of view should be in range of [0.0f, 180.0f]");
	camera->coord.x = ft_atof(splitted_coord[0]);
	camera->coord.y = ft_atof(splitted_coord[1]);
	camera->coord.z = ft_atof(splitted_coord[2]);
	free_2d_arr(splitted_coord);
	splitted_coord = ft_split(splitted_elt[2], ',');
	if (!is_valid_float(splitted_coord[0]) || !is_valid_float(splitted_coord[1])
		|| !is_valid_float(splitted_coord[2]))
		free_pars_error(scene, splitted_elt, "Element value format error \n");
	camera->vector_dir.x = ft_atof(splitted_coord[0]);
	camera->vector_dir.y = ft_atof(splitted_coord[1]);
	camera->vector_dir.z = ft_atof(splitted_coord[2]);
	free_2d_arr(splitted_coord);
	free_2d_arr(splitted_elt);
	if (!is_in_range(camera->vector_dir.x, 'v')
		|| !is_in_range(camera->vector_dir.y, 'v')
		|| !is_in_range(camera->vector_dir.z, 'v'))
		free_pars_error(scene, NULL, "Normalized orientation vector should be in range of [-1, 1]");
}
