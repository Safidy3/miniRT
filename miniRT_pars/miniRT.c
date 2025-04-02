/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:14:18 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/02 00:02:59 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
	{
		printf("Error\n");
		printf("Invalid number of argument.");
		return (1);
	}
	if (validate_scene_name(argv[1]))
	{
		printf("Error\n");
		printf("Invalid filename \n");
		return (1);
	}
	p_scene(argv[1], &scene);

	// t_list	*tmp;
	// tmp = scene.sphere_lst;
	// while (tmp)
	// {
	// 	print_sphere((t_sphere *)(tmp->content));
	// 	tmp = tmp->next;
	// }
	// tmp = scene.cylinder_lst;
	// while (tmp)
	// {
	// 	print_cylinder((t_cylinder *)(tmp->content));
	// 	tmp = tmp->next;
	// }
	// tmp = scene.plane_lst;
	// while (tmp)
	// {
	// 	print_plane((t_plane *)(tmp->content));
	// 	tmp = tmp->next;
	// }
	clear_p_scene(&scene);
	return (0);
}
