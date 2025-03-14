/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:32:29 by safandri          #+#    #+#             */
/*   Updated: 2025/03/14 15:09:18 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	*thread_routing(void *param)
{
	t_threads	*thread;
	t_data	*og_data;
	t_data	data;
	t_vec3	pix_col;
	int		x, y;
	int		thread_id;

	thread = (t_threads *)param;
	og_data = thread->data;
	thread_id = og_data->thread_id;
	data.AA_sample = og_data->AA_sample;
	data.world = NULL;
	add_sceen(&data);

	int begin = thread_id * thread->pix_unit;
	int end = (thread_id + 1) * thread->pix_unit;
	pthread_mutex_lock(&og_data->thread->lock);
	if (thread_id == thread->thread_num - 1)
		end = WIDTH;
	pthread_mutex_unlock(&og_data->thread->lock);
	printf("%d - %d\n", begin, end);

	for (x = begin; x < end; x++)
	{
		for (y = HEIGHT - 1; y >= 0; y--)
		{
			// pix_col = compute_path_traced_color(&data, x, y);
			pix_col = ray_casted_color(&data, x, y);
			my_mlx_pixel_put(og_data, x, y, pix_col);
		}
		pthread_mutex_lock(&og_data->thread->lock);
		mlx_put_image_to_window(og_data->mlx, og_data->win, og_data->img, 0, 0);
		pthread_mutex_unlock(&og_data->thread->lock);
	}
	clear_sceen(&(data.world));
	return (NULL);
}

void	put_pixel_color_thread(t_threads *thread)
{
	char	line[10];
	t_data *data;
    FILE *p;
	p = popen("awk '/^processor/{n+=1}END{print n}' /proc/cpuinfo", "r");
	if( p == NULL)
    {
        puts("Unable to open process");
        return;
    }
	fgets(line, 10, p);
    pclose(p);

	data = thread->data;
	thread->thread_num = ft_atoi(line);
	printf("thread num = %d\n", thread->thread_num);
	thread->pix_unit = WIDTH / thread->thread_num;
	printf("Loading ...\n");
	for (int i = 0; i < thread->thread_num; i++)
	{
		pthread_mutex_lock(&thread->lock);
		data->thread_id = i;
		printf("Thread %d started : ", i);
		pthread_mutex_unlock(&thread->lock);
		pthread_create(&thread->threads[i], NULL, thread_routing, (void *)thread);
		usleep(100);
	}
	for (int i = 0; i < thread->thread_num; i++)
		pthread_join(thread->threads[i], NULL);
	printf("Finished.\n");
}
