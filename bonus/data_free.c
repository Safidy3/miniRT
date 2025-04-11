/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:50:26 by safandri          #+#    #+#             */
/*   Updated: 2025/03/28 22:29:13 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->option_win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_image(data->mlx, data->option_img);
	mlx_destroy_display(data->mlx);
	while (++i < WIDTH)
	{
		free(data->camera_rays[i]);
		free(data->hit_objects[i]);
	}
	free(data->camera_rays);
	free(data->hit_objects);
	free(data->mlx);
	clear_sceen(&(data->world));
}

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}

void	delete_obj(void *obj)
{
	free(obj);
}

void	clear_sceen(t_list **world)
{
	if (world && *world)
	{
		ft_lstclear(world, &delete_obj);
		*world = NULL;
	}
}

t_object	*make_obj(t_list *obj)
{
	if (obj)
		return ((t_object *)obj->content);
	else
		return (NULL);
}
