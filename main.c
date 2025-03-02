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


/*******************************************************************************/

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

void	list_swapp(t_list *a, t_list *b)
{
	void *tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

void	sortlist(t_list **t)
{
	t_list	*iter;
	t_list	*iter2;
	t_list	*head;
	int		iter_val;
	int		iter2_val;

	head = *t;
	iter = head;
	while (iter)
	{
		iter2 = iter->next;
		while (iter2)
		{
			iter_val = 	(int)((t_hit_object *)(iter->content))->hit_record.t;
			iter2_val = (int)((t_hit_object *)(iter2->content))->hit_record.t;
			if (iter_val > iter2_val)
				list_swapp(iter, iter2);
			iter2 = iter2->next;
		}
		iter = iter->next;
	}
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


t_hit_object	*get_first_hit_obj(const t_ray r, t_list *world)
{
	t_hit_object	*obj;
	t_hit_object	*first_hit_obj;
	float			closest_t;
	int				is_hiting;

	closest_t = MAX_T;
	is_hiting = 0;

	while (world)
	{
		obj = make_obj(world);
		if (hit_obj(obj, r, &(obj->hit_record)))
		{
			is_hiting = 1;
			if (obj->hit_record.t < closest_t)
			{
				first_hit_obj = obj;
				closest_t = obj->hit_record.t;
			}
		}
		world = world->next;
	}
	if (is_hiting)
		return (first_hit_obj);
	return (NULL);
}

t_vec3	color(const t_ray r, t_list *world, int depth, t_hit_object	*src_obj)
{
	t_hit_object	*first_hit_obj;

	if (depth >= MAX_RECURS_DEPTH) 
		return (create_vec3(0, 0, 0)); 

	first_hit_obj = get_first_hit_obj(r, world);

	if (first_hit_obj && depth < MAX_RECURS_DEPTH)
	{
		t_ray	scattered;
		t_vec3	attenuation;

		if (first_hit_obj->material == METAL && metal_scatter_ray(r, first_hit_obj->hit_record, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(color(scattered, world, depth+1, first_hit_obj), attenuation));
		else if (first_hit_obj->material == LAMBERTIAN && lamberian_scatter_ray(r, first_hit_obj->hit_record, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(color(scattered, world, depth+1, first_hit_obj), attenuation));
		else if (first_hit_obj->material == DIELECTRIC && dielectric_scatter_ray(r, first_hit_obj->hit_record, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(color(scattered, world, depth+1, first_hit_obj), attenuation));
		else if (first_hit_obj->material == LIGHT && depth != 0)
			return (vec3_mult(src_obj->color, first_hit_obj->color));
        else if (first_hit_obj->material == LIGHT && depth == 0)
		{
			t_ray	continued_ray;

			while (first_hit_obj && first_hit_obj->material == LIGHT)
			{
				continued_ray = create_ray(first_hit_obj->hit_record.hit_point, r.direction);
				first_hit_obj = get_first_hit_obj(continued_ray, world);
			}
			if (first_hit_obj)
				return (color(continued_ray, world, depth + 1, first_hit_obj));
        }
	}
	return create_vec3(0, 0, 0);
}

void	add_cornell_box(t_list **world)
{
	t_vec3 white = create_vec3(1, 1, 1);
	t_vec3 red = create_vec3(1, 0, 0);
	t_vec3 green = create_vec3(0, 1, 0);
	// t_vec3 blue = create_vec3(0, 0, 1);

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

	// t_hit_object *back = create_plane(
	// 	create_vec3(-2, 0, 1),
	// 	create_vec3(2, 0, 1),
	// 	create_vec3(-2, 2, 1),
	// 	create_vec3(2, 2, 1)
	// );
	// scene_add_obj(world, back, blue, 0, 0.5, LAMBERTIAN);
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

	cam = create_camera(create_vec3(0, 0, 1), create_vec3(0, 0, -1));


	add_cornell_box(&data.world);

	t_hit_object *shpere = create_sphere(create_vec3(0, 0, -1), 0.5);
	scene_add_obj(&data.world, shpere, create_vec3(0.1,0.2,0.5), 0, 0, METAL);
	// t_hit_object *sphere_base = create_sphere(create_vec3(0, -100.5, -1), 100);
	// scene_add_obj(&data.world, sphere_base, create_vec3(0.8,0.8,0.0), 1, 0, LAMBERTIAN);
	// scene_add_obj(&data.world, create_vec3(1, 0, -1), 0.5, create_vec3(0.8,0.6,0.2), 0, METAL);
	// scene_add_obj(&data.world, create_vec3(-1, 0, -1), 0.5, create_vec3(0.0,0.0,0.0), 1.5, DIELECTRIC);

	t_vec3	pixel_pos;
	t_vec3	r_col;
	t_ray	r;
	float	i;
	float	j;
	
	printT(data.world);
	printf("Backing ...\n");
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = HEIGHT - 1; y >= 0; y--)
		{
			int dept = 0;
			r_col = create_vec3(0, 0, 0);
			for (int s = 0; s < AA_sample; s++)
			{
				i = (float)(x + drand48()) / (float)WIDTH;
				j = (float)(HEIGHT - y + drand48()) / (float)HEIGHT;
				pixel_pos = vec3_add3(cam.lower_L, vec3_mult_float(cam.horizintal, i), vec3_mult_float(cam.vertical, j));
				r = create_ray(cam.origin, vec3_sub(pixel_pos, cam.origin));
				r_col = vec3_add(r_col, color(r, data.world, dept, NULL));
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
