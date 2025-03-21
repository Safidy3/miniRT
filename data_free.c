/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:50:26 by safandri          #+#    #+#             */
/*   Updated: 2025/03/19 14:33:29 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_data(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->option_win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_image(data->mlx, data->option_img);
	mlx_destroy_display(data->mlx);
	for (int i = 0; i < WIDTH; i++)
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

void	free_2d_array(void **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

t_object	*make_obj(t_list *obj)
{
	if (obj)
		return ((t_object *)obj->content);
	else
		return (NULL);
}

void	list_swapp(t_list *a, t_list *b)
{
	void *tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

void	sortlist(t_list **t)
{
	t_list	*iter;
	t_list	*iter2;
	t_list	*head;
	int		iter_val;
	int		iter2_val;

	head = *t;
	iter = head;
	while (iter)
	{
		iter2 = iter->next;
		while (iter2)
		{
			iter_val = 	(int)((t_object *)(iter->content))->hit_record.t;
			iter2_val = (int)((t_object *)(iter2->content))->hit_record.t;
			if (iter_val > iter2_val)
				list_swapp(iter, iter2);
			iter2 = iter2->next;
		}
		iter = iter->next;
	}
}
