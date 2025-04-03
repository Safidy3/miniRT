/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:53:04 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 04:07:24 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_obj	make_light(t_scene *scene, char **splitted_obj)
{
	t_obj	tmp;

	tmp.shape = POINT_LIGHT;
	tmp.center_coord = make_coord(1, splitted_obj, 0, scene);
	tmp.diameter = ft_atofl(2, splitted_obj, scene);
	tmp.color = create_rgb(255.0, 255.0, 255.0);
	tmp.normal_vector = create_3dnull();
	tmp.height = 0;
	return (tmp);
}

t_obj	make_amient(t_scene *scene, char **splitted_obj)
{
	t_obj	tmp;

	tmp.shape = AMBIENT_LIGHT;
	tmp.diameter = ft_atofl(1, splitted_obj, scene);
	tmp.color = make_rgb(2, splitted_obj, scene);
	tmp.center_coord = create_3dnull();
	tmp.normal_vector = create_3dnull();
	tmp.height = 0;
	return (tmp);
}
