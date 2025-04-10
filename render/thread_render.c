/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:32:29 by safandri          #+#    #+#             */
/*   Updated: 2025/03/29 07:19:46 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec3	path_traced_color(const t_ray r, t_list *world,
			int depth, t_object	*src_obj)
{
	t_object		*first_hit;
	t_ray			scattered;
	t_vec3			attenuation;
	t_vec3			ambient;
	t_vec3			res;

	res = create_nullvec();
	ambient = get_light(world, AMBIENT_LIGHT)->proprieties.color;
	if (depth == 0)
		first_hit = get_safe_hit_obj(r, world);
	else
		first_hit = get_first_hit_obj(r, world);
	if (first_hit && depth < MAX_RECURS_DEPTH)
	{
		get_scattered_attenuation(&attenuation, &scattered, first_hit, r);
		if (first_hit->proprieties.material == LIGHT && depth != 0)
			res = vec3_mult(src_obj->proprieties.color,
					first_hit->proprieties.color);
		else
			res = vec3_mult(path_traced_color(
						scattered, world, depth + 1, first_hit), attenuation);
		if (!is_null_vec(ambient))
			res = color_add(res, ambient);
	}
	return (res);
}

void	thread_render(t_data *data, t_data *og_data, t_thread_data *thread_data)
{
	t_vec3	pix_col;
	int		x;
	int		y;
	int		end;

	x = thread_data->thread_id * thread_data->thread->pix_unit - 1;
	end = (thread_data->thread_id + 1) * thread_data->thread->pix_unit;
	if (thread_data->thread_id == thread_data->thread->thread_num - 1)
		end = WIDTH;
	while (++x < end)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			pix_col = compute_path_traced_color(data, x, y);
			my_mlx_pixel_put(og_data, x, y, pix_col);
		}
		pthread_mutex_lock(&og_data->thread->lock);
		mlx_put_image_to_window(og_data->mlx, og_data->win, og_data->img, 0, 0);
		mlx_do_sync(og_data->mlx);
		pthread_mutex_unlock(&og_data->thread->lock);
	}
	clear_sceen(&(data->world));
}

void	*thread_routing(void *param)
{
	t_thread_data	*thread_data;
	t_threads		*thread;
	t_data			*og_data;
	t_data			data;
	int				i;

	i = -1;
	thread_data = (t_thread_data *)param;
	thread = thread_data->thread;
	og_data = thread->data;
	intit_thread_data(&data, og_data);
	compute_camera_rays(&data);
	thread_render(&data, og_data, thread_data);
	while (++i < WIDTH)
	{
		free(data.camera_rays[i]);
		free(data.hit_objects[i]);
	}
	return (free(data.camera_rays), free(data.hit_objects), NULL);
}

void	start_thread(t_threads *thread, t_list *thread_data_list)
{
	t_thread_data	*thread_data;
	t_list			*tmp;
	int				i;

	i = -1;
	ft_putstr("rendering ...\n");
	tmp = thread_data_list;
	while (tmp)
	{
		thread_data = (t_thread_data *)tmp->content;
		pthread_create(&thread->threads[thread_data->thread_id], NULL,
			thread_routing, (void *)thread_data);
		tmp = tmp->next;
	}
	while (++i < thread->thread_num)
		pthread_join(thread->threads[i], NULL);
	ft_putstr("Finished.\n");
}

void	put_pixel_color_thread(t_threads *thread)
{
	t_data			*data;
	t_list			*thread_data_list;
	t_thread_data	*thread_data;
	char			thread_num[10];
	int				i;

	i = -1;
	thread_data_list = NULL;
	data = thread->data;
	get_cpu_thread_num(thread, thread_num);
	while (++i < thread->thread_num)
	{
		thread_data = (t_thread_data *)malloc(sizeof(t_thread_data));
		thread_data->thread_id = i;
		thread_data->thread = thread;
		thread_data->data = data;
		ft_lstadd_back(&thread_data_list, ft_lstnew(thread_data));
	}
	erase_main_screen(data);
	start_thread(thread, thread_data_list);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	ft_lstclear(&thread_data_list, free);
}
