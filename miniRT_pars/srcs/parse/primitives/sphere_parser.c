/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:54:25 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/01 03:15:51 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../miniRT.h"

void	sphere_parser(char *scene_elt, t_scene *scene)
{
	char		**splitted_elt;
	char		**splitted_coord;
	t_sphere	sphere;
	t_list		*new_sphere;

	splitted_elt = ft_split_space(scene_elt);
	check_arg_nbr(splitted_elt, 4, scene);
	init_sphere(&sphere);
	splitted_coord = ft_split(splitted_elt[1], ',');
	if (!get_3dcoord(&(sphere.center_coord), splitted_coord, 0)
			|| !is_valid_float(splitted_elt[2]))
		free_pars_error(scene, splitted_elt, "Element value format error\n");
	sphere.diameter = ft_atof(splitted_elt[2]);
	splitted_coord = ft_split(splitted_elt[3], ',');
	free_2d_arr(splitted_elt);
	get_rgb_color(&(sphere.color), splitted_coord, scene);
	new_sphere = ft_lstnew(&sphere);
	ft_lstadd_back(&(scene->sphere_lst), new_sphere);
	print_sphere((t_sphere *)(scene->sphere_lst->content));
}
