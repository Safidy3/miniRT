/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:09:45 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/02 00:23:03 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	free_2d_arr(char **arr)
{
	char	**tmp;
	int		i;

	if (!arr || !(*arr))
		return ;
	tmp = arr;
	i = 0;
	while (*arr && arr)
	{
		free(*arr);
		i++;
		arr++;
	}
	if (tmp)
		free(tmp);
}

void	clear_plane(void *g_plane_lst)
{
	(void)g_plane_lst;
}

void	clear_cylinder(void *g_cylinder_lst)
{
	(void)g_cylinder_lst;
}

void	clear_sphere(void *g_sphere_lst)
{
	(void)g_sphere_lst;
}

void	clear_p_scene(t_scene *scene)
{
	ft_lstclear(&(scene->plane_lst), clear_plane);
	ft_lstclear(&(scene->cylinder_lst), clear_cylinder);
	ft_lstclear(&(scene->sphere_lst), clear_sphere);
	free_2d_arr(scene->scene_arr);
}
