/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:53:04 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 04:53:52 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_obj	make_light(t_scene *scene, char **splitted_obj)
{
	t_obj	tmp;

	tmp.shape = POINT_LIGHT;
	tmp.center = make_coord(1, splitted_obj, 0, scene);
	tmp.brightness = ft_atofl(2, splitted_obj, scene);
	tmp.color = make_rgb(3, splitted_obj, scene);
	if (ft_arr_len((void **)splitted_obj) == 5)
		tmp.diameter = ft_atofl(4, splitted_obj, scene);
	else
		tmp.diameter = 1;
	tmp.normal_vector = create_3dnull();
	tmp.height = 0;
	tmp.metalness = 0.0;
	tmp.use_texture = 0;
	return (tmp);
}

t_obj	make_amient(t_scene *scene, char **splitted_obj)
{
	t_obj	tmp;

	tmp.shape = AMBIENT_LIGHT;
	tmp.brightness = ft_atofl(1, splitted_obj, scene);
	tmp.color = make_rgb(2, splitted_obj, scene);
	tmp.center = create_3dnull();
	tmp.normal_vector = create_3dnull();
	tmp.diameter = 0.0;
	tmp.metalness = 0.0;
	tmp.use_texture = 0;
	tmp.height = 0.0;
	return (tmp);
}

t_obj	make_camera(t_scene *scene, char **splitted_obj)
{
	t_obj	tmp;

	tmp.shape = CAMERA;
	tmp.center = make_coord(1, splitted_obj, 0, scene);
	tmp.normal_vector = make_coord(2, splitted_obj, 1, scene);
	tmp.diameter = ft_atofl(3, splitted_obj, scene);
	tmp.color = create_3dnull();
	tmp.height = 0;
	tmp.metalness = 0.0;
	tmp.use_texture = 0;
	tmp.brightness = 0.0;
	return (tmp);
}
