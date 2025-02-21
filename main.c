/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/02/22 16:40:55 by safandri         ###   ########.fr       */
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
		// hit_rec->color = vec3_mult_float(create_vec3(hit_rec->normal.x + 1, hit_rec->normal.y + 1, hit_rec->normal.z + 1), 0.5);
		return (1);
	}

	t = (-b + sqrt(delta)) / (2.0 * a);
	if (t > MIN_T && t < MAX_T)
	{
		hit_rec->t = t;
		hit_rec->hit_point = ray_point_at(r, t);
		hit_rec->normal = vec3_div_float(vec3_sub(hit_rec->hit_point, obj->center), obj->radius);
		// hit_rec->color = vec3_mult_float(create_vec3(hit_rec->normal.x + 1, hit_rec->normal.y + 1, hit_rec->normal.z + 1), 0.5);
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

t_vec3	vec3_random_in_unit_object()
{
	t_vec3	p;
	t_vec3	tmp;

	do
	{
		tmp = vec3_mult_float(create_vec3(drand48(), drand48(), drand48()), 2.0) ;
		p = vec3_sub(tmp, create_vec3(1, 1, 1));
	}
	while (vec3_squared_len(p) >= 1.0);
	return (p);	
}


t_vec3 color(const t_ray r, t_list *world, int depth)
{
	printf("%d\n", depth);
	t_hit_shpere	*obj;
	t_hit_shpere	*first_hit_obj;
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
	if (is_hiting)
	{
		t_ray	scattered;
		t_vec3	attenuation;

		if (depth < 50 && first_hit_obj->use_metal && metal_scatter_ray(r, first_hit, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(color(scattered, world, depth+1), attenuation));
		else if (depth < 50 && !first_hit_obj->use_metal && lamberian_scatter_ray(r, first_hit, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(color(scattered, world, depth+1), attenuation));
		else
			return (create_vec3(0, 0, 0));
	}
	return bg_color(r);
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

	scene_add_sphere(&data.world, create_vec3(0, 0, -1), 0.5, create_vec3(0.8,0.3,0.3), 0, 0);
	scene_add_sphere(&data.world, create_vec3(0, -100.5, -1), 100, create_vec3(0.8,0.3,0.3), 0, 0);
	scene_add_sphere(&data.world, create_vec3(1, 0, -1), 0.5, create_vec3(0.8,0.3,0.3), 1, 1);
	scene_add_sphere(&data.world, create_vec3(-1, 0, -1), 0.5, create_vec3(0.8,0.3,0.3), 1, 0);

	cam.lower_L = create_vec3(-2.0, -1.0, -1.0);
	cam.horizintal = create_vec3(4.0, 0.0, 0.0);
	cam.vertical = create_vec3(0.0, 2.0, 0.0);
	cam.origin = create_vec3(0.0, 0.0, 0.0);

	t_vec3	pixel_pos;
	t_ray	r;
	t_vec3	r_col;
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
				r_col = vec3_add(r_col, color(r, data.world, 0));
			}
			t_rgb	v;
			r_col = vec3_div_float(r_col, ns);
			r_col = create_vec3(sqrt(r_col.x), sqrt(r_col.y), sqrt(r_col.z));
			v.r = (int)(255.99 * r_col.x);
			v.g = (int)(255.99 * r_col.y);
			v.b = (int)(255.99 * r_col.z);
			int color = ((int)v.r << 16) | ((int)v.g << 8) | (int)v.b;
			my_mlx_pixel_put(&data, x, y, color);
		}
	}

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
