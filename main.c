/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/02/20 13:34:55 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_data(t_data *data)
{
	t_list	*world;

	world = data->world;
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);

	clear_sceen(&(data->world));
}

int	close_window(void *param)
{
	printf("exit\n");
	t_data	*data;

	data = (t_data *)param;
	free_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}

int	handle_key(int keycode, void *param)
{
	t_data	*data;
	
	// printf("Key pressed: %d\n", keycode);
	data = (t_data *)param;
	if (keycode == 65307)
		close_window(data);
	return (0);
}

/*******************************************************************************/

float	hit_sphere(t_hit_shpere *obj, const t_ray r)
{
	t_vec3	oc = vec3_sub(r.origin, obj->center);
	float	a = vec3_dot(r.direction, r.direction);
	float	b = 2 * vec3_dot(oc, r.direction);
	float	c = vec3_dot(oc, oc) - obj->radius * obj->radius;
	float	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (-1.0);
	return ((-b -sqrt(delta)/ (2 * a)));
}

t_vec3	color(const t_ray r, t_list *world)
{
	t_vec3	unit_dir;
	t_vec3	begin;
	t_vec3	end;
	float	t;

	t_hit_shpere	*shpere = make_obj(world);
	// t_hit_shpere	shpere = create_sphere(create_vec3(0,0,-1), 0.5);

	t = hit_sphere(shpere, r);
	if (t > 0)
	{
		t_vec3 N = vec3_unit(vec3_sub(ray_point_at(r, t), create_vec3(0,0,-1)));
		return (vec3_mult_float(create_vec3(N.x + 1,N.y + 1,N.z + 1), 0.5));
	}

	unit_dir = vec3_unit(r.direction);
	t = 0.5 * (unit_dir.y + 1.0);
	begin = create_vec3(1.0, 1.0, 1.0);
	end = create_vec3(0.5, 0.7, 1.0);
	return (vec3_add(vec3_mult_float(begin, (1.0 - t)), vec3_mult_float(end, t)));
}

int	main(void)
{
	t_data	data;
	t_cam	cam;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "miniRT");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.world = NULL;
	scene_add_sphere(&data.world, create_vec3(0,0,-1), 0.5);

	cam.lower_L = create_vec3(-2.0, -1.0, -1.0);
	cam.horizintal = create_vec3(4.0, 0.0, 0.0);
	cam.vertical = create_vec3(0.0, 2.0, 0.0);
	cam.origin = create_vec3(0.0, 0.0, 0.0);

	t_vec3	pixel_pos;
	for (int y = HEIGHT - 1; y >= 0; y--)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			t_rgb	v;

			double	i = (double)x / (double)WIDTH;
			double	j = (double)(HEIGHT - y) / (double)HEIGHT;

			pixel_pos = vec3_add3(cam.lower_L, vec3_mult_float(cam.horizintal, i), vec3_mult_float(cam.vertical, j));
			t_ray	r = create_ray(cam.origin, vec3_sub(pixel_pos, cam.origin));
			t_vec3	r_col = color(r, data.world);

			v.r = (int)(255.99 * r_col.x);
			v.g = (int)(255.99 * r_col.y);
			v.b = (int)(255.99 * r_col.z);

			int color = ((int)v.r << 16) | ((int)v.g << 8) | (int)v.b;
			my_mlx_pixel_put(&data, x, y, color);
		}
	}
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data); // Key press event
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	return (0);
}


// int main()
// {
// 	t_list	*world = NULL;
// 	t_list	*tmp_list;
// 	t_hit_shpere	*tmp;

// 	scene_add_sphere(&world, create_vec3(2.6, 8.1, 3.2), 10);
// 	scene_add_sphere(&world, create_vec3(5.4, 2.3, 1.9), 0.5);

// 	printf("..................\n");
// 	tmp_list = world;
// 	while (tmp_list)
// 	{
// 		tmp = make_obj(tmp_list);
// 		print_vec3(tmp->center, NULL);
// 		printf("..................\n");
// 		tmp_list = tmp_list->next;
// 	}
// 	clear_sceen(&world);
// 	return (0);
// }

