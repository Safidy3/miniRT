/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:54:14 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/02 20:20:22 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../miniRT.h"

void	plane_parser(char *scene_elt, t_scene *scene)
{
	char	**splitted_elt;
	char	**splitted_coord;
	t_plane	plane;
	t_list	*new_plane;

	splitted_elt = ft_split_space(scene_elt);
	print_2d_arr(splitted_elt);
	check_arg_nbr(splitted_elt, 4, scene);
	init_plane(&plane);
	splitted_coord = ft_split(splitted_elt[1], ',');
	if (!get_3dcoord(&(plane.center_coord), splitted_coord, 0))
	{
		free_2d_arr(splitted_elt);
		free_2d_arr(scene->scene_arr);
		ft_lstclear(&(scene->plane_lst), clear_plane);
		exit(1);
	}
	splitted_coord = ft_split(splitted_elt[2], ',');
	if (!get_3dcoord(&(plane.normal_vector), splitted_coord, 1))
	{
		free_2d_arr(splitted_elt);
		free_2d_arr(scene->scene_arr);
		ft_lstclear(&(scene->plane_lst), clear_plane);
		exit(1);
	}
	// TODO: still check if should free
	splitted_coord = ft_split(splitted_elt[3], ',');
	free_2d_arr(splitted_elt);
	get_rgb_color(&(plane.color), splitted_coord, scene);
	new_plane = ft_lstnew(&plane);
	ft_lstadd_back(&(scene->plane_lst), new_plane);
}
