/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:52:51 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/02 20:27:29 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

// TODO: in each exit() double check leaks here and to add nice error message.
void	ambient_parser(t_ambient *ambient, char *scene_elt, t_scene *scene)
{
	char	**splitted_elt;
	char	**splitted_color;

	splitted_elt = ft_split_space(scene_elt);
	check_arg_nbr(splitted_elt, 3, scene);
	ambient->id = scene_elt[0];
	if (!is_valid_float(splitted_elt[1]))
		free_pars_error(scene, splitted_elt, "Element value format error\n");
	ambient->brightness = ft_atof(splitted_elt[1]);
	if (!is_in_range(ambient->brightness, 'r'))
		free_pars_error(scene, splitted_elt, "brightness value should be in range of [0.0f, 0.1]");
	splitted_color = ft_split(splitted_elt[2], ',');
	free_2d_arr(splitted_elt);
	get_rgb_color((&ambient->color), splitted_color, scene);
}
