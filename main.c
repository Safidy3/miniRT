/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/02/20 16:20:49 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

int	hit_sphere(t_hit_shpere *obj, const t_ray r, t_hit_record *hit_rec)
{
	t_vec3	oc = vec3_sub(r.origin, obj->center);
	float	a = vec3_dot(r.direction, r.direction);
	float	b = 2.0 * vec3_dot(oc, r.direction);
	float	c = vec3_dot(oc, oc) - obj->radius * obj->radius;
	float	delta = b * b - 4.0 * a * c;

	if (delta < 0)
		return (0);

	float t = (-b - sqrt(delta)) / (2.0 * a);
	if (t > MIN_T && t < MAX_T)
	{
		hit_rec->t = t;
		hit_rec->hit_point = ray_point_at(r, t);
		hit_rec->normal = vec3_div_float(vec3_sub(hit_rec->hit_point, obj->center), obj->radius);
		hit_rec->color = vec3_mult_float(create_vec3(hit_rec->normal.x + 1, hit_rec->normal.y + 1, hit_rec->normal.z + 1), 0.5);
		return (1);
	}

	t = (-b + sqrt(delta)) / (2.0 * a);
	if (t > MIN_T && t < MAX_T)
	{
		hit_rec->t = t;
		hit_rec->hit_point = ray_point_at(r, t);
		hit_rec->normal = vec3_div_float(vec3_sub(hit_rec->hit_point, obj->center), obj->radius);
		hit_rec->color = vec3_mult_float(create_vec3(hit_rec->normal.x + 1, hit_rec->normal.y + 1, hit_rec->normal.z + 1), 0.5);
		return (1);
	}
	return (0);
}

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



t_vec3	color(const t_ray r, t_list *world)
{
	int	obj_num = ft_lstsize(world);

	t_hit_shpere	*obj;
	t_hit_record	first_hit;

	float	closest_t = MAX_T;
	int		is_hiting = 0;
	int	i;
	

	i = -1;
	while (++i < obj_num)
	{
		obj = make_obj(world);
		if (hit_sphere(obj, r, &(obj->hit_record)))
		{
			is_hiting = 1;
			if (obj->hit_record.t < closest_t)
			{
				closest_t = obj->hit_record.t;
				first_hit = obj->hit_record;
			}
		}
		world = world->next;
	}

	if (is_hiting)
		return (first_hit.color);

	return (bg_color(r));
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

	scene_add_sphere(&data.world, create_vec3(0, 0, -1), 0.5);
	scene_add_sphere(&data.world, create_vec3(0, -100.5, -1), 100);

	printf("%d\n", ft_lstsize(data.world));

	cam.lower_L = create_vec3(-2.0, -1.0, -1.0);
	cam.horizintal = create_vec3(4.0, 0.0, 0.0);
	cam.vertical = create_vec3(0.0, 2.0, 0.0);
	cam.origin = create_vec3(0.0, 0.0, 0.0);

	t_vec3	pixel_pos;
	t_ray	r;
	t_vec3	r_col;
	// int		nx = 200;
	// int		ny = 100;
	int		ns = 100;
	for (int y = HEIGHT - 1; y >= 0; y--)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			r_col = create_vec3(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				
				float	i = (float)(x + drand48()) / (float)WIDTH;
				float	j = (float)(HEIGHT - y + drand48()) / (float)HEIGHT;
				pixel_pos = vec3_add3(cam.lower_L, vec3_mult_float(cam.horizintal, i), vec3_mult_float(cam.vertical, j));
				r = create_ray(cam.origin, vec3_sub(pixel_pos, cam.origin));
				
				r_col = vec3_add(r_col, color(r, data.world));

			}
			t_rgb	v;
			r_col = vec3_div_float(r_col, ns);
			
			v.r = (int)(255.99 * r_col.x);
			v.g = (int)(255.99 * r_col.y);
			v.b = (int)(255.99 * r_col.z);

			int color = ((int)v.r << 16) | ((int)v.g << 8) | (int)v.b;
			my_mlx_pixel_put(&data, x, y, color);
		}
	}
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
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

