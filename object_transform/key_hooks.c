/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:49:26 by safandri          #+#    #+#             */
/*   Updated: 2025/03/28 22:25:23 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	erase_main_screen(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++x < WIDTH)
		while (++y < HEIGHT)
			my_mlx_pixel_put(data, x, y, create_nullvec());
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	mouse_hook(int keycode, int x, int y, void *param)
{
	t_data		*data;

	data = (t_data *)param;
	if (keycode == 1)
	{
		data->seleced_object = data->hit_objects[x][y];
		if (data->seleced_object)
		{
			ft_putstr("Object selected : ");
			print_obj(data->seleced_object);
		}
		else
			ft_putstr("No object selected\n");
	}
	return (0);
}

void	delete_world_object(t_data *data)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = data->world;
	prev = NULL;
	while (data->seleced_object->shape != CAMERA && tmp)
	{
		if (((t_object *)(tmp->content))->id == data->seleced_object->id)
		{
			if (!prev)
				data->world = tmp->next;
			else
			{
				prev->next = tmp->next;
				ft_lstdelone(tmp, free);
				break ;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
	compute_objects_hits(data);
	data->seleced_object = NULL;
	put_pixel_color_debug(data);
}

void	select_camera(t_data *data)
{
	t_list	*tmp;

	tmp = data->world;
	while (tmp)
	{
		if (((t_object *)(tmp->content))->shape == CAMERA)
		{
			data->seleced_object = (t_object *)(tmp->content);
			break ;
		}
		tmp = tmp->next;
	}
}

int	handle_key(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65436)
		data->seleced_object = get_light(data->world, POINT_LIGHT);
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 119 || keycode == 115 || keycode == 97
		|| keycode == 100 || keycode == 101 || keycode == 113)
		object_translation(keycode, data);
	else if (keycode == 105 || keycode == 112 || keycode == 111
		|| keycode == 108 || keycode == 107 || keycode == 59)
		object_rotation(keycode, data);
	else if (keycode == 65535)
		delete_world_object(data);
	else if (keycode == 116)
		put_pixel_color(data);
	else if (keycode == 121)
		put_pixel_color_debug(data);
	else if (keycode == 99)
		select_camera(data);
	return (0);
}
