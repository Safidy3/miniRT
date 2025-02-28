/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/02/28 17:25:43 by safandri         ###   ########.fr       */
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
		int iter_val = 	(int)((t_hit_object *)(t->content))->hit_record.t;
		printf("%d, ", iter_val);
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

t_vec3 color(const t_ray r, t_list *world, int depth)
{
	if (depth >= MAX_RECURS_DEPTH) 
		return (create_vec3(0, 0, 0)); 

	t_hit_object	*obj;
	t_hit_object	*first_hit_obj;
	t_hit_record	first_hit;
	t_list			*world_tmp;
	t_list			*first_hit_world;
	t_list			*tmp_obj;
	float			closest_t;
	int				is_hiting;

	closest_t = MAX_T;
	is_hiting = 0;
	tmp_obj = world;

	world_tmp = world;
	while (world_tmp)
	{
		obj = make_obj(world_tmp);
		hit_obj(obj, r, &(obj->hit_record));
		world_tmp = world_tmp->next;
	}

	sortlist(&world);

	world_tmp = world;
	while (world_tmp)
	{
		obj = make_obj(world_tmp);
		if (hit_obj(obj, r, &(obj->hit_record)))
		{
			is_hiting = 1;
			if (obj->hit_record.t < closest_t)
			{
				first_hit_obj = obj;
				closest_t = obj->hit_record.t;
				first_hit = obj->hit_record;
				first_hit_world = world_tmp;
			}
		}
		world_tmp = world_tmp->next;
	}

	if (is_hiting && depth < MAX_RECURS_DEPTH)
	{
		t_ray	scattered;
		t_vec3	attenuation;

		if (first_hit_obj->material == METAL && metal_scatter_ray(r, first_hit, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(color(scattered, world, depth+1), attenuation));
		else if (first_hit_obj->material == LAMBERTIAN && lamberian_scatter_ray(r, first_hit, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(color(scattered, world, depth+1), attenuation));
		else if (first_hit_obj->material == DIELECTRIC && dielectric_scatter_ray(r, first_hit, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(color(scattered, world, depth+1), attenuation));
		// else if (first_hit_obj->material == LIGHT && depth != 0)
		// 	return (vec3_mult_float(first_hit_obj->color, 1.2));
		else if (first_hit_obj->material == LIGHT)
			return (vec3_mult_float(first_hit_obj->color, 1.2));

		// else if (first_hit_obj->material == LIGHT && depth == 0)
		// {
		// 	// Skip this object and trace to the next object behind it
		// 	t_list *next_obj = first_hit_world->next;
		// 	while (next_obj && ((t_hit_object *)(next_obj->content))->material == LIGHT)
		// 		next_obj = next_obj->next;

		// 	// If there's another object behind the light, return its color
		// 	if (next_obj)
		// 		return color(r, next_obj, depth + 1);
			
		// 	// Otherwise, return black (or a small ambient light if desired)
		// 	return create_vec3(0, 0, 0);
		// }

		// else if (first_hit_obj->material == LIGHT && depth == 0)
		// {
		// 	obj = make_obj(first_hit_world->next);
		// 	t_vec3 col = color(r, first_hit_world->next, depth+1);
		// 	return (col);
		// }
		else
			return (vec3_mult_float(first_hit.color, 0.2));
	}
	return create_vec3(0, 0, 0);
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

	printf("%d\n", LAMBERTIAN);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "miniRT");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.world = NULL;

	cam = create_camera(create_vec3(0, 5, 1), create_vec3(0, 0, -1));

	
	// t_hit_object *shpere = create_sphere(create_vec3(0, 0, -1), 0.5);
	// scene_add_obj(&data.world, shpere, create_vec3(0.1,0.2,0.5), 0, 0.5, METAL);

	t_hit_object *shpere_light = create_sphere(create_vec3(0, 1, -1), 0.5);
	scene_add_obj(&data.world, shpere_light, create_vec3(1, 1, 1), 0, 0, LIGHT);

	t_hit_object *rectangle = create_rectangle(
		create_vec3(-2, 0, -2),
		create_vec3(2, 0, -2),
		create_vec3(-2, 2, -2),
		create_vec3(2, 2, -2)
	);
	scene_add_obj(&data.world, rectangle, create_vec3(1, 1, 1), 0, 1, LAMBERTIAN);

	t_hit_object *sphere_base = create_sphere(create_vec3(0, -100.5, -1), 100);
	scene_add_obj(&data.world, sphere_base, create_vec3(0.8,0.8,0.0), 1, 0, LAMBERTIAN);
	// scene_add_obj(&data.world, create_vec3(1, 0, -1), 0.5, create_vec3(0.8,0.6,0.2), 0, METAL);
	// scene_add_obj(&data.world, create_vec3(-1, 0, -1), 0.5, create_vec3(0.0,0.0,0.0), 1.5, DIELECTRIC);

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
			r_col = create_vec3(0, 0, 0);
			for (int s = 0; s < AA_sample; s++)
			{
				i = (float)(x + drand48()) / (float)WIDTH;
				j = (float)(HEIGHT - y + drand48()) / (float)HEIGHT;
				pixel_pos = vec3_add3(cam.lower_L, vec3_mult_float(cam.horizintal, i), vec3_mult_float(cam.vertical, j));
				r = create_ray(cam.origin, vec3_sub(pixel_pos, cam.origin));
				r_col = vec3_add(r_col, color(r, data.world, dept));
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


// int	main()
// {
// 	t_list	*tmp = malloc(sizeof(t_list));
// 	int *val;

// 	int i = 9;
// 	tmp = ft_lstnew((void *) &i);
// 	val = tmp->content;


// 	int j = 8;
// 	ft_lstadd_content_back(&tmp, (void *) &j);
// 	val = tmp->content;


// 	int k = 4;
// 	ft_lstadd_content_back(&tmp, (void *) &k);
// 	val = tmp->content;


// 	int l = 6;
// 	ft_lstadd_content_back(&tmp, (void *) &l);
// 	val = tmp->content;


// 	int m = 1;
// 	ft_lstadd_content_back(&tmp, (void *) &m);
// 	val = tmp->content;


// 	int n = 7;
// 	ft_lstadd_content_back(&tmp, (void *) &n);
// 	val = tmp->content;


// 	printT(tmp);
// 	sortlist(&tmp);
// }
