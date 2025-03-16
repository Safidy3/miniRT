/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:15:23 by safandri          #+#    #+#             */
/*   Updated: 2025/03/16 17:55:31 by safandri         ###   ########.fr       */
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

t_vec3	path_traced_color(const t_ray r, t_list *world, int depth, t_object	*src_obj)
{
	t_object		*first_hit_obj;
	t_ray			scattered;
	t_vec3			attenuation;
	t_proprieties	prts;

	if (depth == 0)
		first_hit_obj = get_safe_hit_obj(r, world);
	else
		first_hit_obj = get_first_hit_obj(r, world);
	if (first_hit_obj && depth < MAX_RECURS_DEPTH)
	{
		prts = first_hit_obj->proprieties;
		if (prts.material == METAL && metal_scatter_ray(r, first_hit_obj->hit_record, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(path_traced_color(scattered, world, depth+1, first_hit_obj), attenuation));
		else if (prts.material == LAMBERTIAN && lamberian_scatter_ray(r, first_hit_obj->hit_record, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(path_traced_color(scattered, world, depth+1, first_hit_obj), attenuation));
		else if (prts.material == DIELECTRIC && dielectric_scatter_ray(r, first_hit_obj->hit_record, &attenuation, &scattered, *first_hit_obj))
			return (vec3_mult(path_traced_color(scattered, world, depth+1, first_hit_obj), attenuation));
		else if (prts.material == LIGHT && depth != 0)
			return (vec3_mult(src_obj->proprieties.color, prts.color));
	}
	return (create_nullvec());
}

t_vec3	ray_casted_color(t_data *data, int x, int y)
{
	t_vec3	pix_pos;
	float	i, j;
	t_vec3	point_light = create_vec3(2, 2, 1);
	t_vec3	ambient_light = create_vec3(1, 1, 1);
	float	intensity;
	t_vec3	result;

	i = (float)(x) / (float)WIDTH;
	j = (float)(HEIGHT - y) / (float)HEIGHT;
	pix_pos = vec3_add3(data->cam.lower_L, vec3_mult_float(data->cam.horizintal, i), vec3_mult_float(data->cam.vertical, j));

	t_ray		r = create_ray(data->cam.origin, vec3_sub(pix_pos, data->cam.origin));
	t_object	*first_hit_obj = get_safe_hit_obj(r, data->world);

	if (!first_hit_obj)
		return (create_nullvec());

	intensity = 0.2;
	ambient_light = vec3_mult_float(ambient_light, intensity);

	t_vec3		sh_direction = vec3_normalize(vec3_sub(point_light, first_hit_obj->hit_record.hit_point));
	t_ray		shadow_ray = create_ray(first_hit_obj->hit_record.hit_point, sh_direction);
	t_object	*sec_hit_obj = get_safe_hit_obj(shadow_ray, data->world);

	if (sec_hit_obj)
	{
		result = vec3_mult(first_hit_obj->proprieties.color, ambient_light);
		return (result);
	}
	else
	{
		// if (first_hit_obj->shape == PLANE)
		// {
		// 	sh_direction = vec3_normalize(vec3_sub(pix_pos, point_light));
		// 	shadow_ray = create_ray(first_hit_obj->hit_record.hit_point, sh_direction);
		// 	sec_hit_obj = get_safe_hit_obj(shadow_ray, data->world);
		// 	if (sec_hit_obj)
		// 		return (vec3_mult(first_hit_obj->proprieties.color, ambient_light));
		// }
		float n = fmax(intensity, vec3_dot(first_hit_obj->hit_record.normal, shadow_ray.direction));
		result = vec3_mult_float(first_hit_obj->proprieties.color, n);
		return (result);
	}
}

t_vec3	compute_path_traced_color(t_data *data, int x, int y)
{
	t_vec3	pix_pos, pix_col;
	float	i, j;
	int		s;
	t_ray	r;

	pix_col = create_vec3(0, 0, 0);
	if (isVoid(x, y, *data))
		return (create_nullvec());
	for (s = 0; s < data->AA_sample; s++)
	{
		i = (float)(x + drand48()) / (float)WIDTH;
		j = (float)(HEIGHT - y + drand48()) / (float)HEIGHT;
		pix_pos = vec3_add3(data->cam.lower_L, vec3_mult_float(data->cam.horizintal, i), vec3_mult_float(data->cam.vertical, j));
		r = create_ray(data->cam.origin, vec3_sub(pix_pos, data->cam.origin));
		pix_col = vec3_add(pix_col, path_traced_color(r, data->world, 0, NULL));
	}
	pix_col = vec3_div_float(pix_col, data->AA_sample);
	pix_col = create_vec3(sqrt(pix_col.x), sqrt(pix_col.y), sqrt(pix_col.z));
	return (pix_col);
}

void	put_pixel_color(t_data *data)
{
	t_vec3	pix_col;
	int		x, y;

	printf("Loading ...\n");
	for (x = 0; x < WIDTH; x++)
	{
		for (y = HEIGHT - 1; y >= 0; y--)
		{
			// pix_col = compute_path_traced_color(data, x, y);
			pix_col = ray_casted_color(data, x, y);
			my_mlx_pixel_put(data, x, y, pix_col);
		}
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	printf("Finished.\n");
}
