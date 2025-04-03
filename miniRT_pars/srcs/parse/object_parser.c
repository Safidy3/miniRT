/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 03:14:08 by safandri          #+#    #+#             */
/*   Updated: 2025/04/03 09:43:02 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

t_obj	make_cylindre(t_scene *scene, char **splitted_obj)
{
	t_obj	tmp;

	tmp.shape = CYLINDRE;
	tmp.center_coord = make_coord(1, splitted_obj, 0, scene);
	tmp.normal_vector = make_coord(2, splitted_obj, 1, scene);
	tmp.color = make_rgb(5, splitted_obj, scene);
	tmp.diameter = ft_atofl(3, splitted_obj, scene);
	tmp.height = ft_atofl(4, splitted_obj, scene);
	return (tmp);
}

t_obj	make_sphere(t_scene *scene, char **splitted_obj)
{
	t_obj	tmp;

	tmp.shape = SPHERE;
	tmp.center_coord = make_coord(1, splitted_obj, 0, scene);
	tmp.diameter = ft_atofl(2, splitted_obj, scene);
	tmp.color = make_rgb(3, splitted_obj, scene);
	tmp.normal_vector = create_3dnull();
	tmp.height = 0;
	return (tmp);
}

t_obj	make_plan(t_scene *scene, char **splitted_obj)
{
	t_obj	tmp;

	tmp.shape = PLANE;
	tmp.center_coord = make_coord(1, splitted_obj, 0, scene);
	tmp.normal_vector = make_coord(2, splitted_obj, 1, scene);
	tmp.color = make_rgb(3, splitted_obj, scene);
	tmp.diameter = 0.0;
	tmp.height = 0;
	return (tmp);
}

t_obj	make_camera(t_scene *scene, char **splitted_obj)
{
	t_obj	tmp;

	tmp.shape = CAMERA;
	tmp.center_coord = make_coord(1, splitted_obj, 0, scene);
	tmp.normal_vector = make_coord(2, splitted_obj, 1, scene);
	tmp.diameter = ft_atofl(3, splitted_obj, scene);
	tmp.color = create_3dnull();
	tmp.height = 0;
	return (tmp);
}
