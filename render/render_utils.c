/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:32:34 by safandri          #+#    #+#             */
/*   Updated: 2025/03/14 12:40:10 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void my_mlx_pixel_put(t_data *data, int x, int y, t_vec3 r_col)
{
	t_rgb	v;
	int		color;
	char	*dst;

	v.r = (int)(255.99 * r_col.x);
	v.g = (int)(255.99 * r_col.y);
	v.b = (int)(255.99 * r_col.z);
	color = ((int)v.r << 16) | ((int)v.g << 8) | (int)v.b;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

t_object	*get_safe_hit_obj(const t_ray r, t_list *world)
{
	t_object	*first_hit_obj;

	first_hit_obj = get_first_hit_obj(r, world);
	if (first_hit_obj && first_hit_obj->proprieties.material != LIGHT)
		return (first_hit_obj);
	else if (first_hit_obj && first_hit_obj->proprieties.material == LIGHT)
	{
		while (first_hit_obj && first_hit_obj->proprieties.material == LIGHT)
		{
			t_ray	continued_ray = create_ray(first_hit_obj->hit_record.hit_point, r.direction);
			first_hit_obj = get_first_hit_obj(continued_ray, world);
		}
		if (first_hit_obj)
			return (first_hit_obj);
	}
	return (NULL);
}

int	isVoid(float x, float y, t_data data)
{
	t_object *c;

	c = get_safe_hit_obj
	(
		create_ray
		(
			data.cam.origin,
			vec3_sub
			(
				vec3_add3
				(
					data.cam.lower_L, 
					vec3_mult_float(data.cam.horizintal, (float)x / (float)WIDTH),
					vec3_mult_float(data.cam.vertical, (float)(HEIGHT - y) / (float)HEIGHT)
				),
				data.cam.origin
			)
		),
		data.world
	);
	if (c == NULL || (c && c->proprieties.material == LIGHT))
		return (1);
	return (0);
}

t_object	*get_first_hit_obj(const t_ray r, t_list *world)
{
	t_object	*obj;
	t_object	*first_hit_obj;
	float		closest_t;
	int			is_hiting;

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
