/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:54:18 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 03:19:53 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	get_fd(char *filename, int *fd, int is_first_fd, t_scene *scene)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		printf("Error : Could not open file. \n");
		if (is_first_fd == 2)
			free_2d_arr(scene->scene_arr);
		exit(1);
	}
}
