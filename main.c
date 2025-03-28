/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/03/28 23:43:37 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_data(t_data *data)
{
	int	i;

	i = -1;
	data->mlx = mlx_init();
	data->option_win = mlx_new_window(data->mlx, HEIGHT, WIDTH, "Options");
	data->option_img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	data->option_addr = mlx_get_data_addr(data->option_img,
			&data->o_bits_per_pixel, &data->o_line_length, &data->o_endian);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->world = NULL;
	data->seleced_object = NULL;
	data->camera_rays = (t_ray **)malloc(sizeof(t_ray *) * WIDTH);
	while (++i < WIDTH)
		data->camera_rays[i] = (t_ray *)malloc(sizeof(t_ray) * HEIGHT);
	data->hit_objects = (t_object ***)malloc(sizeof(t_object **) * WIDTH);
	i = -1;
	while (++i < WIDTH)
		data->hit_objects[i] = (t_object **)malloc(sizeof(t_object *) * HEIGHT);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_threads	thread;

	if (argc > 1)
	{
		if (!ft_isNumber(argv[1]))
			return (ft_putstr_fd("Usage: ./miniRT OR ./miniRT [AA_sample]\n", 1), 1);
		data.AA_sample = ft_atoi(argv[1]);
	}
	else
		data.AA_sample = 1;
	init_data(&data);
	thread.data = &data;
	pthread_mutex_init(&thread.lock, NULL);
	data.thread = &thread;
	add_sceen(&data);
	printT(data.world);
	// put_pixel_color(&data);
	put_pixel_color_debug(&data);
	// put_pixel_color_thread(&thread);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
