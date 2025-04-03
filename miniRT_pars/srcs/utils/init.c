/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:55:02 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 03:19:43 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	p_scene(char *filename, t_scene *scene)
{
	int	fd;

	get_fd(filename, &fd, 1, scene);
	scene->scene_len = get_scene_len(fd);
	scene->scene_arr = (char **)malloc(sizeof(char *) * (scene->scene_len + 1));
	if (!(scene->scene_arr))
	{
		printf("Error : Malloc error\n");
		exit(1);
	}
	get_fd(filename, &fd, 2, scene);
	get_scene(fd, scene);
	validate_scene(scene);
	scene->cylinder_lst = NULL;
	parse(scene);
}
