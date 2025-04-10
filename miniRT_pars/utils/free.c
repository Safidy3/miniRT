/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:09:45 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/09 15:26:29 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	free_2d_arr(char **arr)
{
	char	**tmp;

	if (!arr || !(*arr))
		return ;
	tmp = arr;
	while (*arr)
		free(*arr++);
	free(tmp);
}

void	clear_plane(void *g_plane_lst)
{
	(void)g_plane_lst;
}

void	clear_cylinder(void *g_cylinder_lst)
{
	free(g_cylinder_lst);
}

void	clear_sphere(void *g_sphere_lst)
{
	(void)g_sphere_lst;
}

void	clear_p_scene(t_scene *scene)
{
	ft_lstclear(&(scene->obj_lst), clear_cylinder);
	free_2d_arr(scene->scene_arr);
}
