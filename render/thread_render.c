/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:32:29 by safandri          #+#    #+#             */
/*   Updated: 2025/03/11 11:33:16 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	add_sceen(t_data *data)
{
	data->cam = create_camera(create_vec3(0, 0, 1), create_vec3(0, 0, -1));
	add_cornell_box(&data->world);

	t_proprieties p_white_light = create_proprieties(create_vec3(1, 1, 1), LIGHT, 0, 0);
	t_proprieties white_lamb = create_proprieties(create_vec3(1, 1, 1), LAMBERTIAN, 0, 0);
	t_proprieties Blue_lamb = create_proprieties(create_vec3(0.1, 0.2, 0.5), LAMBERTIAN, 0, 0);

	t_object *shpere_light = create_sphere(create_vec3(-1, 0.5, -0.5), 0.5);
	scene_add_obj(&data->world, shpere_light, p_white_light);

	t_object *shpere = create_sphere(create_vec3(1, 0.5, 0), 0.5);
	scene_add_obj(&data->world, shpere, white_lamb);

	t_object *cylinder = create_cylinder(create_vec3(0.3, 0, -1), create_vec3(0, 1, 0), 0.5);
	scene_add_obj(&data->world, cylinder, Blue_lamb);
}


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
	for (x = thread_id * PIX_UNIT; x < (thread_id + 1) * PIX_UNIT; x++)
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
		printf("Thread %d started\n", i);
		pthread_mutex_unlock(&data->thread->lock);
		pthread_create(&data->thread->threads[i], NULL, thread_routing, (void *)data);
		usleep(10000);
	}
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(data->thread->threads[i], NULL);
	printf("Finished.\n");
}
