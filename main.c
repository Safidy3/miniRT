/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/03/05 14:31:35 by safandri         ###   ########.fr       */
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
	printf("size %d\n", ft_lstsize(t));
	while (t)
	{
		int iter_val = 	(int)((t_object *)(t->content))->id;
		switch (iter_val)
		{
			case 0:
				printf("SPHERE\n");
				break;
			case 1:
				printf("RECTANGLE\n");
				break;
			case 2:
				printf("PLANE\n");
				break;
			case 3:
				printf("INF_CYLINDRE\n");
				break;
			default:
				break;
		}
		// printf("id : %d\n", iter_val);
		t = t->next;
	}
	printf("\n");
}

/*******************************************************************************/

void	add_cornell_box(t_list **world)
{
	t_proprieties white_lamb = create_proprieties(create_vec3(1, 1, 1), LAMBERTIAN, 0, 0);
	// t_proprieties red_lamb = create_proprieties(create_vec3(1, 0, 0), LAMBERTIAN, 0, 0);
	// t_proprieties green_lamb = create_proprieties(create_vec3(0, 1, 0), LAMBERTIAN, 0, 0);

	// t_object *up = create_plane(
	// 	create_vec3(-2, 1.5, 0),
	// 	create_vec3(2, 1.5, 0),
	// 	create_vec3(-2, 1.5, -2),
	// 	create_vec3(2, 1.5, -2)
	// );
	// scene_add_obj(world, up, white_lamb);

	// t_object *down = create_plane(
	// 	create_vec3(-2, -1.5, 0),
	// 	create_vec3(2, -1.5, 0),
	// 	create_vec3(-2, -1.5, -2),
	// 	create_vec3(2, -1.5, -2)
	// );
	// scene_add_obj(world, down, white_lamb);

	t_object *fw = create_plane(
		create_vec3(-2, 0, -2),
		create_vec3(2, 0, -2),
		create_vec3(-2, 2, -2),
		create_vec3(2, 2, -2)
	);
	scene_add_obj(world, fw, white_lamb);

	// t_object *left = create_plane(
	// 	create_vec3(-2, 0, 0),
	// 	create_vec3(-2, 0, -2),
	// 	create_vec3(-2, 2, 0),
	// 	create_vec3(-2, 2, -2)
	// );
	// scene_add_obj(world, left, red_lamb);

	// t_object *right = create_plane(
	// 	create_vec3(2, 0, 0),
	// 	create_vec3(2, 0, -2),
	// 	create_vec3(2, 2, 0),
	// 	create_vec3(2, 2, -2)
	// );
	// scene_add_obj(world, right, green_lamb);

	// t_object *back = create_plane(
	// 	create_vec3(-2, 0, 1),
	// 	create_vec3(2, 0, 1),
	// 	create_vec3(-2, 2, 1),
	// 	create_vec3(2, 2, 1)
	// );
	// scene_add_obj(world, back, white_lamb);
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

	// add_cornell_box(&data.world);

	t_proprieties p_white_light = create_proprieties(create_vec3(1, 1, 1), LIGHT, 0, 0);
	t_proprieties white_lamb = create_proprieties(create_vec3(1, 1, 1), LAMBERTIAN, 0, 0);
	// t_proprieties Blue_lamb = create_proprieties(create_vec3(0.1, 0.2, 0.5), LAMBERTIAN, 0, 0);

	t_object *shpere_light = create_sphere(create_vec3(-1, 0.5, -0.5), 0.5);
	scene_add_obj(&data.world, shpere_light, p_white_light);

	t_object *shpere = create_sphere(create_vec3(1, 0.5, 0), 0.5);
	scene_add_obj(&data.world, shpere, white_lamb);

	t_object *cylinder = create_cylinder(create_vec3(0.3, 0, -1), create_vec3(0, 1, 0), 0.5);
	scene_add_obj(&data.world, cylinder, white_lamb);

	printT(data.world);
	if (data.AA_sample == 0)
		put_pixel_color_debug(data);
	else
		put_pixel_color(data);

	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
