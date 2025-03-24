/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/03/21 06:47:20 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	erase_main_screen(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	for (x = 0; x < WIDTH; x++)
	{
		for (y = HEIGHT - 1; y >= 0; y--)
			my_mlx_pixel_put(data, x, y, create_nullvec());
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
}

int	handle_key(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	printf("keycode : %d\n", keycode);
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 119)
		translate_object(data, create_vec3(0, 0, -0.1));
	else if (keycode == 115)
		translate_object(data, create_vec3(0, 0, 0.1));
	else if (keycode == 97)
		translate_object(data, create_vec3(-0.1, 0, 0));
	else if (keycode == 100)
		translate_object(data, create_vec3(0.1, 0, 0));
	else if (keycode == 101)
		translate_object(data, create_vec3(0, 0.1, 0));
	else if (keycode == 113)
		translate_object(data, create_vec3(0, -0.1, 0));
	else if (keycode == 65535)
	{
		t_list	*tmp;
		t_list	*prev;

		tmp = data->world;
		prev = NULL;
		while (tmp)
		{
			if (((t_object *)(tmp->content))->id == data->seleced_object->id)
			{
				if (!prev)
					data->world = tmp->next;
				else
				{
					prev->next = tmp->next;
					ft_lstdelone(tmp, free);
					break;
				}
			}
			prev = tmp;
			tmp = tmp->next;
		}
		compute_objects_hits(data);
		data->seleced_object = NULL;
		put_pixel_color_debug(data);
	}
	else if (keycode == 114)
		put_pixel_color_thread(data->thread);
	else if (keycode == 116)
		put_pixel_color(data);
	else if (keycode == 121)
		put_pixel_color_debug(data);
	else if (keycode == 99)
	{
		t_list	*tmp;

		tmp = data->world;
		while (tmp)
		{
			if (((t_object *)(tmp->content))->shape == CAMERA)
			{
				data->seleced_object = (t_object *)(tmp->content);
				break;
			}
			tmp = tmp->next;
		}
	}
	option_window(data, data->seleced_object);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, void *param)
{
	t_data		*data;
	float		i, j;
	t_vec3		pix_pos;
	t_ray		r;
	t_object	*first_hit_obj;

	data = (t_data *)param;
	if (keycode == 1)
	{
		i = (float)(x) / (float)WIDTH;
		j = (float)(HEIGHT - y) / (float)HEIGHT;
		pix_pos = vec3_add3(data->cam.lower_L, vec3_mult_float(data->cam.horizintal, i), vec3_mult_float(data->cam.vertical, j));
		r = create_ray(data->cam.origin, vec3_sub(pix_pos, data->cam.origin));
		first_hit_obj = get_safe_hit_obj(r, data->world);
		data->seleced_object = first_hit_obj;
		option_window(data, first_hit_obj);
	}
	return (0);
}

void	printT(t_list *t)
{
	printf("size %d\n", ft_lstsize(t));
	while (t)
	{
		int iter_val = 	(int)((t_object *)(t->content))->shape;
		switch (iter_val)
		{
			case 0:
				printf("SPHERE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case 1:
				printf("RECTANGLE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case 2:
				printf("PLANE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case 3:
				printf("INF_CYLINDRE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case 4:
				printf("CYLINDRE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case 5:
				printf("POINT_LIGHT : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case 6:
				printf("AMBIENT_LIGHT : %d\n", (int)((t_object *)(t->content))->id);
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
	t_proprieties red_lamb = create_proprieties(create_vec3(1, 0, 0), LAMBERTIAN, 0, 0);
	t_proprieties green_lamb = create_proprieties(create_vec3(0, 1, 0), LAMBERTIAN, 0, 0);

	t_object *up = create_plane(
		create_vec3(0, 2, 0),
		create_vec3(0, -1, 0)
	);
	scene_add_obj(world, up, white_lamb);

	t_object *down = create_plane(
		create_vec3(0, -2, 0),
		create_vec3(0, 1, 0)
	);
	scene_add_obj(world, down, white_lamb);

	t_object *fw = create_plane(
		create_vec3(0, 0, -2),
		create_vec3(0, 0, 1)
	);
	scene_add_obj(world, fw, white_lamb);

	t_object *left = create_plane(
		create_vec3(-2, 0, 0),
		create_vec3(1, 0, 0)
	);
	scene_add_obj(world, left, red_lamb);

	t_object *right = create_plane(
		create_vec3(2, 0, 0),
		create_vec3(-1, 0, 0)
	);
	scene_add_obj(world, right, green_lamb);

	t_object *back = create_plane(
		create_vec3(0, 0, 2),
		create_vec3(0, 0, -1)
	);
	scene_add_obj(world, back, white_lamb);
}

void	add_sceen(t_data *data)
{

	// t_proprieties green_lamb = create_proprieties(create_vec3(0, 1, 0), LAMBERTIAN, 0, 0);
	// t_proprieties white_lamb = create_proprieties(create_vec3(1, 1, 1), LAMBERTIAN, 0, 0);
	t_proprieties Blue_lamb = create_proprieties(create_vec3(0, 0, 1), LAMBERTIAN, 0, 0);
	t_proprieties purple = create_proprieties(create_vec3(0.490196078, 0, 1), LAMBERTIAN, 0, 0);

	t_object *shpere = create_sphere(create_vec3(1, 0, -1), 1.0);
	scene_add_obj(&data->world, shpere, Blue_lamb);

	t_object *cylinder = create_cylinder(create_vec3(-0, 1, -1), create_vec3(0, 1, 0), 0.6, 1.5);
	scene_add_obj(&data->world, cylinder, purple);

	// t_object *point_light = create_point_light(create_vec3(-1, 0, -0.5), create_vec3(1, 1, 1), 1);
	// scene_add_obj(&data->world, point_light, green_lamb);
	// t_object *ambent_light = create_ambient(create_vec3(1, 1, 1), 0.2);
	// scene_add_obj(&data->world, ambent_light, green_lamb);

	t_proprieties p_white_light = create_proprieties(create_vec3(1, 1, 1), LIGHT, 0, 0);
	t_object *shpere_light = create_sphere(create_vec3(-1, 0, -0.5), 1);
	scene_add_obj(&data->world, shpere_light, p_white_light);

	add_cornell_box(&data->world);

	create_camera(data, create_vec3(0, 0, 1), create_vec3(0, 0, -1), 90);
	compute_camera_rays(data);
}

void	translate_object(t_data *data, t_vec3 translation)
{
	t_object	*obj;

	obj = data->seleced_object;
	if (!obj)
		return;
	obj->center = vec3_add(obj->center, translation);
	if (obj->shape == CAMERA)
	{
		obj->direction = vec3_add(obj->direction, translation);
		data->cam.origin = obj->center;
		data->cam.direction = obj->direction;
		compute_camera_rays(data);
	}
	else
		compute_objects_hits(data);
	put_pixel_color_debug(data);
	// put_pixel_color_thread(data->thread);
	// put_pixel_color(data);
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

	data.option_win = mlx_new_window(data.mlx, HEIGHT, WIDTH, "Options");
	data.option_img = mlx_new_image(data.mlx, HEIGHT, WIDTH);
	data.option_addr = mlx_get_data_addr(data.option_img, &data.o_bits_per_pixel, &data.o_line_length, &data.o_endian);

	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "miniRT");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	data.world = NULL;
	data.seleced_object = NULL;

	data.camera_rays = (t_ray **)malloc(sizeof(t_ray *) * WIDTH);
	for (int i = 0; i < WIDTH; i++)
		data.camera_rays[i] = (t_ray *)malloc(sizeof(t_ray) * HEIGHT);

	data.hit_objects =(t_object ***)malloc(sizeof(t_object **) * WIDTH);
	for (int i = 0; i < WIDTH; i++)
		data.hit_objects[i] = (t_object **)malloc(sizeof(t_object *) * HEIGHT);

	t_threads	thread;
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
