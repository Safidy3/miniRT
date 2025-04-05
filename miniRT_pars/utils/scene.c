/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:22:13 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 04:53:52 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	get_scene_len(int fd)
{
	char	*scene;
	int		scene_len;

	scene = get_next_line(fd);
	scene_len = 0;
	while (scene)
	{
		if (ft_strcmp(scene, "\n"))
			scene_len++;
		free(scene);
		scene = get_next_line(fd);
	}
	close(fd);
	return (scene_len);
}

void	get_scene(int fd, t_scene *scene)
{
	int		i;
	char	*l_scene;

	i = 0;
	l_scene = get_next_line(fd);
	while (l_scene)
	{
		if (!ft_strcmp(l_scene, "\n"))
			free(l_scene);
		else
			scene->scene_arr[i++] = l_scene;
		l_scene = get_next_line(fd);
	}
	scene->scene_arr[i] = NULL;
	close(fd);
}

void	validate_scene(t_scene *scene)
{
	if (!(*(scene->scene_arr)) || !(scene->scene_arr))
	{
		ft_putstr_err("Error : Cannot support empty scene.\n");
		free(scene->scene_arr);
		exit(1);
	}
	check_dup_capital(scene->scene_arr);
}

void	free_pars_error(t_scene *scene, char **splitted_elt, char *str)
{
	if (str)
	{
		ft_putstr_err("Error : ");
		ft_putstr_err(str);
		ft_putstr_err(".\n");
	}
	if (splitted_elt)
		free_2d_arr(splitted_elt);
	clear_p_scene(scene);
	exit(1);
}

void	free_vec3_error(t_scene *scene, char **splitted_elt,
			char **splitted_obj, char *str)
{
	if (str)
	{
		ft_putstr_err("Error : ");
		ft_putstr_err(str);
		ft_putstr_err(".\n");
	}
	if (splitted_elt)
		free_2d_arr(splitted_elt);
	if (splitted_obj)
		free_2d_arr(splitted_obj);
	clear_p_scene(scene);
	exit(1);
}
