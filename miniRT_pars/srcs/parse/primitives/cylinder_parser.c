/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:54:34 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/01 03:34:51 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../miniRT.h"

void	cylinder_parser(char *scene_elt, t_scene *scene)
{
	char		**splitted_elt;
	char		**splitted_coord;
	t_cylinder	cylinder;
	t_list		*new_cylinder;

	init_cylinder(&cylinder);
	splitted_elt = ft_split_space(scene_elt);
	check_arg_nbr(splitted_elt, 6, scene);
	splitted_coord = ft_split(splitted_elt[1], ',');
	if (!get_3dcoord(&(cylinder.center_coord), splitted_coord, 0))
		free_pars_error(scene, splitted_elt, "Element value format error \n");
	splitted_coord = ft_split(splitted_elt[2], ',');
	if (!get_3dcoord(&(cylinder.normal_vector), splitted_coord, 1))
		free_pars_error(scene, splitted_elt, "Element value format error \n");
	if (!is_valid_float(splitted_elt[3]) || !is_valid_float(splitted_elt[4]))
		free_pars_error(scene, splitted_elt, "Element value format error \n");
	cylinder.diameter = ft_atof(splitted_elt[3]);
	cylinder.height = ft_atof(splitted_elt[4]);
	splitted_coord = ft_split(splitted_elt[5], ',');
	free_2d_arr(splitted_elt);
	get_rgb_color(&(cylinder.color), splitted_coord, scene);
	new_cylinder = ft_lstnew(&cylinder);
	ft_lstadd_back(&(scene->cylinder_lst), new_cylinder);
}
