/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:14:18 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 03:17:58 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
	{
		printf("Error\nInvalid number of argument.");
		return (1);
	}
	if (validate_scene_name(argv[1]))
	{
		printf("Error\nInvalid filename \n");
		return (1);
	}
	p_scene(argv[1], &scene);

	t_list	*tmp;
	tmp = scene.cylinder_lst;
	while (tmp)
	{
		print_cylinder((t_obj *)(tmp->content));
		tmp = tmp->next;
	}
	clear_p_scene(&scene);
	return (0);
}
