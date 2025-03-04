/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/03/02 17:56:06 by safandri         ###   ########.fr       */
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

void	printT(t_list *t)
{
	while (t)
	{
		int iter_val = 	(int)((t_hit_object *)(t->content))->material;
		switch (iter_val)
		{
			case 0:
				printf("LAMERTIAN\n");
				break;
			case 1:
				printf("METAL\n");
				break;
			case 2:
				printf("DIELECTRIC\n");
				break;
			case 3:
				printf("LIGHT\n");
				break;
			default:
				break;
		}
		t = t->next;
	}
	printf("\n");
}

/*******************************************************************************/

void	add_cornell_box(t_list **world)
{
	t_vec3 white = create_vec3(1, 1, 1);
	t_vec3 red = create_vec3(1, 0, 0);
	t_vec3 green = create_vec3(0, 1, 0);

	t_hit_object *shpere_light = create_sphere(create_vec3(0, 1.2, -0.5), 0.5);
	scene_add_obj(world, shpere_light, create_vec3(1,1,1), 0, 0, LIGHT);

	t_hit_object *up = create_plane(
		create_vec3(-2, 1.5, 0),
		create_vec3(2, 1.5, 0),
		create_vec3(-2, 1.5, -2),
		create_vec3(2, 1.5, -2)
	);
	scene_add_obj(world, up, white, 0, 0.5, LAMBERTIAN);

	t_hit_object *down = create_plane(
		create_vec3(-2, -1.5, 0),
		create_vec3(2, -1.5, 0),
		create_vec3(-2, -1.5, -2),
		create_vec3(2, -1.5, -2)
	);
	scene_add_obj(world, down, white, 0, 0.5, LAMBERTIAN);

	t_hit_object *fw = create_plane(
		create_vec3(-2, 0, -2),
		create_vec3(2, 0, -2),
		create_vec3(-2, 2, -2),
		create_vec3(2, 2, -2)
	);
	scene_add_obj(world, fw, white, 0, 0.5, LAMBERTIAN);

	t_hit_object *left = create_plane(
		create_vec3(-2, 0, 0),
		create_vec3(-2, 0, -2),
		create_vec3(-2, 2, 0),
		create_vec3(-2, 2, -2)
	);
	scene_add_obj(world, left, red, 0, 0.5, LAMBERTIAN);

	t_hit_object *right = create_plane(
		create_vec3(2, 0, 0),
		create_vec3(2, 0, -2),
		create_vec3(2, 2, 0),
		create_vec3(2, 2, -2)
	);
	scene_add_obj(world, right, green, 0, 0.5, LAMBERTIAN);

	t_hit_object *back = create_plane(
		create_vec3(-2, 0, 1),
		create_vec3(2, 0, 1),
		create_vec3(-2, 2, 1),
		create_vec3(2, 2, 1)
	);
	scene_add_obj(world, back, white, 0, 0.5, LAMBERTIAN);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc > 1)
	{
		if (!ft_isNumber(argv[1]))
		{
			printf("Usage: ./miniRT OR ./miniRT [AA_sample]\n");
			return (1);
		}
		data.AA_sample = ft_atoi(argv[1]);
	}
	else
		data.AA_sample = 1;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "miniRT");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.world = NULL;
	data.cam = create_camera(create_vec3(0, 0, 1), create_vec3(0, 0, -1));


	add_cornell_box(&data.world);

	t_hit_object *shpere = create_sphere(create_vec3(0, 0, -1), 0.5);
	scene_add_obj(&data.world, shpere, create_vec3(0.1,0.2,0.5), 0, 0, METAL);
	// t_hit_object *sphere_base = create_sphere(create_vec3(0, -100.5, -1), 100);
	// scene_add_obj(&data.world, sphere_base, create_vec3(0.8,0.8,0.0), 1, 0, LAMBERTIAN);
	// scene_add_obj(&data.world, create_vec3(1, 0, -1), 0.5, create_vec3(0.8,0.6,0.2), 0, METAL);
	// scene_add_obj(&data.world, create_vec3(-1, 0, -1), 0.5, create_vec3(0.0,0.0,0.0), 1.5, DIELECTRIC);

	printT(data.world);
	put_pixel_color(data);

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
