/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:55:02 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 06:59:31 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

void	p_scene(char *filename, t_scene *scene)
{
	int	fd;

	get_fd(filename, &fd, 1, scene);
	scene->obj_lst = NULL;
	scene->scene_len = get_scene_len(fd);
	scene->scene_arr = (char **)malloc(sizeof(char *) * (scene->scene_len + 1));
	if (!(scene->scene_arr))
	{
		ft_putstr_err("Error : Malloc error\n");
		exit(1);
	}
	get_fd(filename, &fd, 2, scene);
	get_scene(fd, scene);
	validate_scene(scene);
	parse(scene);
}
