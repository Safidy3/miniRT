/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_drawer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:15:23 by safandri          #+#    #+#             */
/*   Updated: 2025/02/13 10:49:19 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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
	t_ray			scattered;
	t_vec3			attenuation;
	t_ray			continued_ray;

	if (depth >= MAX_RECURS_DEPTH)
		return (create_vec3(0, 0, 0)); 
	first_hit_obj = get_first_hit_obj(r, world);
	if (first_hit_obj && depth < MAX_RECURS_DEPTH)
	{
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

void	put_pixel_color(t_data data)
{
	t_vec3	pix_pos;
	t_vec3	pix_col;
	t_ray	r;
	float	i;
	float	j;
	int		x, y, s;

	printf("Backing ...\n");
	for (x = 0; x < WIDTH; x++)
	{
		for (y = HEIGHT - 1; y >= 0; y--)
		{
			pix_col = create_vec3(0, 0, 0);
			for (s = 0; s < data.AA_sample; s++)
			{
				i = (float)(x + drand48()) / (float)WIDTH;
				j = (float)(HEIGHT - y + drand48()) / (float)HEIGHT;
				pix_pos = vec3_add3(data.cam.lower_L, vec3_mult_float(data.cam.horizintal, i), vec3_mult_float(data.cam.vertical, j));
				r = create_ray(data.cam.origin, vec3_sub(pix_pos, data.cam.origin));
				pix_col = vec3_add(pix_col, color(r, data.world, 0, NULL));
			}
			pix_col = vec3_div_float(pix_col, data.AA_sample);
			pix_col = create_vec3(sqrt(pix_col.x), sqrt(pix_col.y), sqrt(pix_col.z));
			my_mlx_pixel_put(&data, x, y, pix_col);
		}
		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	}
	printf("Finished.\n");
}
