/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:33:13 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/02 20:17:53 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

// void	parse(t_scene *scene)
// {
// 	char	**scene_arr;

// 	scene_arr = scene->scene_arr;
// 	print_2d_arr(scene->scene_arr);

// 	while (*scene_arr)
// 	{
// 		if (**scene_arr == 'A')
// 			ambient_parser(&(scene->ambient), *scene_arr, scene);
// 		else if (**scene_arr == 'C')
// 			camera_parser(&(scene->camera), *scene_arr, scene);
// 		else if (**scene_arr == 'L')
// 			light_parser(&(scene->light), *scene_arr, 1, scene);
// 		else if ((*scene_arr)[0] == 's' && (*scene_arr)[1] == 'p')
// 			sphere_parser(*scene_arr, scene);
// 		else if ((*scene_arr)[0] == 'p' && (*scene_arr)[1] == 'l')
// 			plane_parser(*scene_arr, scene);
// 		else if ((*scene_arr)[0] == 'c' && (*scene_arr)[1] == 'y')
// 			cylinder_parser(*scene_arr, scene);
// 		else if (**scene_arr == 10 && !((*scene_arr)[1]))
// 		{
// 			scene_arr++;
// 			if (!scene_arr)
// 			{
// 				free_2d_arr(scene->scene_arr);
// 				exit(1);
// 			}
// 			continue ;
// 		}
// 		else
// 		{
// 			printf("Error\n");
// 			printf("You can only enter [C, L, A, sp, pl, cy] as element of the scene.\n");
// 			free_2d_arr(scene->scene_arr);
// 			exit(1);
// 		}
// 		scene_arr++;
// 	}
// }


void	parse(t_scene *scene)
{
	char	**scene_arr;

	scene_arr = scene->scene_arr;
	print_2d_arr(scene->scene_arr);

	while (*scene_arr)
	{
		if (**scene_arr == 'A')
			ambient_parser(&(scene->ambient), *scene_arr, scene);
		else if (**scene_arr == 'C')
			camera_parser(&(scene->camera), *scene_arr, scene);
		else if (**scene_arr == 'L')
			light_parser(&(scene->light), *scene_arr, 1, scene);
		else if ((*scene_arr)[0] == 's' && (*scene_arr)[1] == 'p')
			sphere_parser(*scene_arr, scene);
		else if ((*scene_arr)[0] == 'p' && (*scene_arr)[1] == 'l')
			plane_parser(*scene_arr, scene);
		else if ((*scene_arr)[0] == 'c' && (*scene_arr)[1] == 'y')
			cylinder_parser(*scene_arr, scene);
		else if (**scene_arr == 10 && !((*scene_arr)[1]))
		{
			scene_arr++;
			if (!scene_arr)
			{
				free_2d_arr(scene->scene_arr);
				exit(1);
			}
			continue ;
		}
		else
		{
			printf("Error\n");
			printf("You can only enter [C, L, A, sp, pl, cy] as element of the scene.\n");
			free_2d_arr(scene->scene_arr);
			exit(1);
		}
		scene_arr++;
	}
}