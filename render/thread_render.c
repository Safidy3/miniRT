/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:32:29 by safandri          #+#    #+#             */
/*   Updated: 2025/03/11 14:53:37 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	*thread_routing(void *param)
{
	t_data	*og_data;
	t_data	data;
	t_vec3	pix_pos, pix_col;
	t_ray	r;
	float	i, j;
	int		x, y, s;
	int		thread_id;

	og_data = (t_data *)param;
	thread_id = og_data->thread_id;
	data.AA_sample = og_data->AA_sample;
	data.world = NULL;
	add_sceen(&data);

	int begin = thread_id * PIX_UNIT;
	int end = (thread_id + 1) * PIX_UNIT;
	if (thread_id == NUM_THREADS - 1)
		end = WIDTH;
	printf("%d - %d\n", begin, end);

	for (x = begin; x < end; x++)
	{
		for (y = HEIGHT - 1; y >= 0; y--)
		{
			pix_col = create_vec3(0, 0, 0);
			if (isVoid(x, y, data))
				continue;
			for (s = 0; s < og_data->AA_sample; s++)
			{
				i = (float)(x + drand48()) / (float)WIDTH;
				j = (float)(HEIGHT - y + drand48()) / (float)HEIGHT;
				pix_pos = vec3_add3(data.cam.lower_L, vec3_mult_float(data.cam.horizintal, i), vec3_mult_float(data.cam.vertical, j));
				r = create_ray(data.cam.origin, vec3_sub(pix_pos, data.cam.origin));
				pix_col = vec3_add(pix_col, color(r, data.world, 0, NULL));
			}
			pix_col = vec3_div_float(pix_col, data.AA_sample);
			pix_col = create_vec3(sqrt(pix_col.x), sqrt(pix_col.y), sqrt(pix_col.z));
			my_mlx_pixel_put(og_data, x, y, pix_col);
		}
		pthread_mutex_lock(&og_data->thread->lock);
		mlx_put_image_to_window(og_data->mlx, og_data->win, og_data->img, 0, 0);
		pthread_mutex_unlock(&og_data->thread->lock);
	}
	clear_sceen(&(data.world));
	return (NULL);
}

void	put_pixel_color_thread(t_data *data)
{
	printf("Loading ...\n");
	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_mutex_lock(&data->thread->lock);
		data->thread_id = i;
		printf("Thread %d started : ", i);
		pthread_mutex_unlock(&data->thread->lock);
		pthread_create(&data->thread->threads[i], NULL, thread_routing, (void *)data);
		usleep(10000);
	}
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(data->thread->threads[i], NULL);
	printf("Finished.\n");
}
