/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:53:04 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/02 20:27:54 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

// TODO: double check leaks, especially after exit.
void	light_parser(t_light *light, char *scene_elt, int is_bonus,
		t_scene *scene)
{
	char	**splitted_elt;
	char	**splitted_coord;

	splitted_elt = ft_split_space(scene_elt);
	check_arg_nbr(splitted_elt, 4, scene);
	light->id = scene_elt[0];
	splitted_coord = ft_split(splitted_elt[1], ',');
	if (!is_valid_float(splitted_elt[2]))
		free_pars_error(scene, splitted_elt, "Element value format error \n");
	light->brightness = ft_atof(splitted_elt[2]);
	if (!get_3dcoord(&(light->center_coord), splitted_coord, 0)
		|| !is_in_range(light->brightness, 'r'))
		free_pars_error(scene, splitted_elt, "Element value format error \n");
	if (is_bonus)
	{
		splitted_coord = ft_split(splitted_elt[3], ',');
		free_2d_arr(splitted_elt);
		get_rgb_color(&(light->color), splitted_coord, scene);
	}
	else
		free_pars_error(scene, splitted_elt, NULL);
}
