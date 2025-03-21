/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:32:29 by safandri          #+#    #+#             */
/*   Updated: 2025/03/21 06:47:43 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec3	compute_path_traced_color(t_data *data, int x, int y)
{
	t_vec3	pix_col;
	int		s;
	t_ray	r;

	pix_col = create_vec3(0, 0, 0);
	if (isVoid(x, y, data))
		return (create_nullvec());
	for (s = 0; s < data->AA_sample; s++)
	{
		r = data->camera_rays[x][y];
		pix_col = vec3_add(pix_col, path_traced_color(r, data->world, 0, NULL));
	}
	pix_col = vec3_div_float(pix_col, data->AA_sample);
	pix_col = create_vec3(sqrt(pix_col.x), sqrt(pix_col.y), sqrt(pix_col.z));
	return (pix_col);
}

t_vec3	path_traced_color(const t_ray r, t_list *world, int depth, t_object	*src_obj)
{
	t_object		*first_hit_obj;
	t_ray			scattered;
	t_vec3			attenuation;
	t_proprieties	prts;

	if (depth == 0)
		first_hit_obj = get_safe_hit_obj(r, world);
	else
		first_hit_obj = get_first_hit_obj(r, world);
	if (first_hit_obj && depth < MAX_RECURS_DEPTH)
	{
		prts = first_hit_obj->proprieties;
		if (prts.material == METAL && metal_scatter_ray(r, first_hit_obj->hit_record, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(path_traced_color(scattered, world, depth+1, first_hit_obj), attenuation));
		else if (prts.material == LAMBERTIAN && lamberian_scatter_ray(r, first_hit_obj->hit_record, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(path_traced_color(scattered, world, depth+1, first_hit_obj), attenuation));
		else if (prts.material == DIELECTRIC && dielectric_scatter_ray(r, first_hit_obj->hit_record, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(path_traced_color(scattered, world, depth+1, first_hit_obj), attenuation));
		else if (prts.material == LIGHT && depth != 0)
			return (vec3_mult(src_obj->proprieties.color, prts.color));
	}
	return (create_nullvec());
}

void	thread_render(t_data *data, t_data *og_data, int begin, int end)
{
	int			x, y;
	t_vec3		pix_col;

	for (x = begin; x < end; x++)
	{
		for (y = HEIGHT - 1; y >= 0; y--)
		{
			if (isVoid(x, y, og_data))
				continue;
			pix_col = compute_path_traced_color(data, x, y);
			my_mlx_pixel_put(og_data, x, y, pix_col);
		}
		// if (x % 100 == 0)
		// {
			pthread_mutex_lock(&og_data->thread->lock);
			mlx_put_image_to_window(og_data->mlx, og_data->win, og_data->img, 0, 0);
			mlx_do_sync(og_data->mlx);
			pthread_mutex_unlock(&og_data->thread->lock);
		// }
	}
	// pthread_mutex_lock(&og_data->thread->lock);
	// mlx_put_image_to_window(og_data->mlx, og_data->win, og_data->img, 0, 0);
	// pthread_mutex_unlock(&og_data->thread->lock);
	clear_sceen(&(data->world));
}

void	*thread_routing(void *param)
{
	t_threads	*thread;
	t_data		*og_data;
	t_data		data;

	thread = (t_threads *)param;
	og_data = thread->data;
	data.AA_sample = og_data->AA_sample;
	data.cam = dup_camera(og_data->cam);
	data.world = deep_copy_world(og_data->world);
	data.seleced_object = og_data->seleced_object;
	data.camera_rays = malloc(sizeof(t_ray *) * WIDTH);
	for (int i = 0; i < WIDTH; i++)
		data.camera_rays[i] = malloc(sizeof(t_ray) * HEIGHT);

	compute_camera_rays(&data);

	int thread_id = og_data->thread_id;
	int begin = thread_id * thread->pix_unit;
	int end = (thread_id + 1) * thread->pix_unit;
	if (thread_id == thread->thread_num - 1)
		end = WIDTH;

	thread_render(&data, og_data, begin, end);
	for (int i = 0; i < WIDTH; i++)
		free(data.camera_rays[i]);
	free(data.camera_rays);
	printf("Thread %d Finished.\n", thread_id);
	return (NULL);
}

void	put_pixel_color_thread(t_threads *thread)
{
	t_data	*data;
	char	line[10];
    FILE	*p;

	p = popen("awk '/^processor/{n+=1}END{print n}' /proc/cpuinfo", "r");
	fgets(line, 10, p);
    pclose(p);

	data = thread->data;
	erase_main_screen(data);

	thread->thread_num = ft_atoi(line);
	thread->pix_unit = WIDTH / thread->thread_num;
	printf("rendering ...\n");
	for (int i = 0; i < thread->thread_num; i++)
	{
		pthread_mutex_lock(&thread->lock);
		data->thread_id = i;
		pthread_mutex_unlock(&thread->lock);
		printf("Thread %d started\n", data->thread_id);
		pthread_create(&thread->threads[i], NULL, thread_routing, (void *)thread);
		usleep(30000);
	}
	for (int i = 0; i < thread->thread_num; i++)
		pthread_join(thread->threads[i], NULL);
	printf("Finished.\n");
}
