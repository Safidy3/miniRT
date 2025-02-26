/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/02/26 17:30:12 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	handle_key(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65307)
		close_window(data);
	return (0);
}

/*******************************************************************************/

t_vec3	bg_color(const t_ray r)
{
	t_vec3	unit_dir, begin, end, result;
	float	t;
	unit_dir = vec3_unit(r.direction);
	t = 0.5 * (unit_dir.y + 1.0);
	begin = create_vec3(1.0, 1.0, 1.0);
	end = create_vec3(0.5, 0.7, 1.0);
	result = vec3_add(vec3_mult_float(begin, (1.0 - t)), vec3_mult_float(end, t));

	return (result);
}

t_vec3 color(const t_ray r, t_list *world, int depth, int *hit_something)
{
	if (depth >= MAX_RECURS_DEPTH) 
		return create_vec3(0, 0, 0); 

	t_hit_object	*obj;
	t_hit_object	*first_hit_obj;
	t_hit_record	first_hit;
	t_list			*world_tmp;
	float			closest_t;
	int				is_hiting;

	closest_t = MAX_T;
	is_hiting = 0;
	world_tmp = world;
	while (world_tmp)
	{
		obj = make_obj(world_tmp);
		if (hit_sphere(obj, r, &(obj->hit_record)))
		{
			is_hiting = 1;
			if (obj->hit_record.t < closest_t)
			{
				first_hit_obj = obj;
				closest_t = obj->hit_record.t;
				first_hit = obj->hit_record;
			}
		}
		world_tmp = world_tmp->next;
	}
	if (is_hiting && depth < MAX_RECURS_DEPTH)
	{
		t_ray	scattered;
		t_vec3	attenuation;

		if (first_hit_obj->material == METAL && metal_scatter_ray(r, first_hit, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(color(scattered, world, depth+1, hit_something), attenuation));
		else if (first_hit_obj->material == LAMBERTIAN && lamberian_scatter_ray(r, first_hit, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(color(scattered, world, depth+1, hit_something), attenuation));
		else if (first_hit_obj->material == DIELECTRIC && dielectric_scatter_ray(r, first_hit, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(color(scattered, world, depth+1, hit_something), attenuation));
		else if (first_hit_obj->material == LIGHT && depth != 0)
		{
			float	intensity = 1;
			return (vec3_mult_float(first_hit_obj->color, intensity));
		}
		else if (first_hit_obj->material == LIGHT && depth == 0)
			return (vec3_mult(color(r, world_tmp, depth+1, hit_something), attenuation));
		else
			return (vec3_mult_float(first_hit.color, 0.2));
	}
	else if (depth == 0 && !is_hiting)
		*hit_something = 0;
	return create_vec3(0, 0, 0);
	// return bg_color(r);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_cam	cam;
	int		AA_sample;

	if (argc > 1)
	{
		if (!ft_isNumber(argv[1]))
		{
			printf("Usage: ./miniRT OR ./miniRT [AA_sample]\n");
			return (1);
		}
		AA_sample = ft_atoi(argv[1]);
	}
	else
		AA_sample = 1;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "miniRT");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.world = NULL;

	cam = create_camera(create_vec3(0, 0.5, 1), create_vec3(0, 0, -1));

	scene_add_sphere(&data.world, create_vec3(0, 0, -1), 0.5, create_vec3(0.1,0.2,0.5), 0, 0.5, METAL);
	scene_add_sphere(&data.world, create_vec3(0, 1, -1), 0.5, create_vec3(1, 1, 1), 0, 0, LIGHT);
	scene_add_sphere(&data.world, create_vec3(0, -100.5, -1), 100, create_vec3(0.8,0.8,0.0), 1, 0, LAMBERTIAN);
	// scene_add_sphere(&data.world, create_vec3(1, 0, -1), 0.5, create_vec3(0.8,0.6,0.2), 0, METAL);
	// scene_add_sphere(&data.world, create_vec3(-1, 0, -1), 0.5, create_vec3(0.0,0.0,0.0), 1.5, DIELECTRIC);

	t_vec3	pixel_pos;
	t_vec3	r_col;
	t_ray	r;
	float	i;
	float	j;

	printf("Backing ...\n");
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = HEIGHT - 1; y >= 0; y--)
		{
			int dept = 0;
			int	hit_something = 1;
			r_col = create_vec3(0, 0, 0);
			for (int s = 0; s < AA_sample; s++)
			{
				i = (float)(x + drand48()) / (float)WIDTH;
				j = (float)(HEIGHT - y + drand48()) / (float)HEIGHT;
				pixel_pos = vec3_add3(cam.lower_L, vec3_mult_float(cam.horizintal, i), vec3_mult_float(cam.vertical, j));
				r = create_ray(cam.origin, vec3_sub(pixel_pos, cam.origin));
				r_col = vec3_add(r_col, color(r, data.world, dept, &hit_something));
				if (!hit_something)
					break;
			}
			r_col = vec3_div_float(r_col, AA_sample);
			r_col = create_vec3(sqrt(r_col.x), sqrt(r_col.y), sqrt(r_col.z));
			my_mlx_pixel_put(&data, x, y, r_col);
		}
		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	}
	printf("Finished.\n");

	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}

// int	main()
// {
// 	t_data	data;

// 	data.mlx = mlx_init();
// 	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "miniRT");
// 	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
// 	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
// 	data.world = NULL;

// 	t_vec3	col;
	
// 	// t_vec3	white = create_vec3(255, 255, 255);
// 	t_vec3	r_col_1 = create_vec3(0, 255, 50);
// 	t_vec3	r_col_2 = create_vec3(0, 70, 255);

// 	// attenuation
// 	col = vec3_mult(r_col_1, r_col_2);
// 	col = vec3_div_float(col, 255);

// 	// accumulation
// 	// col = vec3_add(r_col_1, r_col_2);
// 	// col = vec3_div_float(col, 2);

// 	print_vec3(col, NULL);
// 	for (int x = 0; x < WIDTH; x++)
// 		for (int y = HEIGHT - 1; y >= 0; y--)
// 			my_mlx_pixel_put(&data, x, y, col);
	

// 	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
// 	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
// 	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
// 	mlx_loop(data.mlx);
// 	return (0);
// }
