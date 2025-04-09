/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:53:04 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/09 15:55:34 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_obj	make_light(t_scene *scene, char **splitted_obj)
{
	t_obj	tmp;

	tmp.shape = POINT_LIGHT;
	tmp.center = make_coord(1, splitted_obj, 0, scene);
	tmp.brightness = ft_atofl(2, splitted_obj, scene);
	if (tmp.brightness > 1 || tmp.brightness < 0)
		free_pars_error(scene, splitted_obj, E_BRIGHTNESS);
	tmp.color = create_rgb(1.0, 1.0, 1.0);
	tmp.normal_vector = create_3dnull();
	tmp.height = 0;
	tmp.diameter = 0.0;
	return (tmp);
}

#include <stdio.h>

t_obj	make_amient(t_scene *scene, char **splitted_obj)
{
	t_obj	tmp;

	tmp.shape = AMBIENT_LIGHT;
	tmp.brightness = ft_atofl(1, splitted_obj, scene);
	printf("B = %f\n", tmp.brightness);
	if (tmp.brightness > 1 || tmp.brightness < 0)
		free_pars_error(scene, splitted_obj, E_BRIGHTNESS);
	tmp.color = make_rgb(2, splitted_obj, scene);
	tmp.center = create_3dnull();
	tmp.normal_vector = create_3dnull();
	tmp.diameter = 0.0;
	tmp.height = 0.0;
	return (tmp);
}
