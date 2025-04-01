/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:32:43 by safandri          #+#    #+#             */
/*   Updated: 2025/03/28 23:24:55 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	is_same(t_edge_object *o)
{
	if (!o->obj || !o->obj2 || !o->obj3 || !o->obj4 || !o->obj5)
		return (0);
	if (o->obj->id != o->obj2->id)
		return (0);
	if (o->obj->id != o->obj3->id)
		return (0);
	if (o->obj->id != o->obj4->id)
		return (0);
	if (o->obj->id != o->obj5->id)
		return (0);
	return (1);
}

t_vec3	color_debug(t_data *data, int x, int y)
{
	t_edge_object	o;

	if (is_void(x, y, data) || x > WIDTH - 2)
		return (create_nullvec());
	o.obj = data->hit_objects[x][y];
	o.obj2 = data->hit_objects[x + 1][y];
	o.obj3 = data->hit_objects[x - 1][y];
	o.obj4 = data->hit_objects[x][y + 1];
	o.obj5 = data->hit_objects[x][y - 1];
	if (is_same(&o))
		return (o.obj->hit_record.color);
	else
		return (create_vec3(0.627, 0.125, 0.941));
}

void	compute_objects_hits(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			data->hit_objects[x][y] = get_safe_hit_obj(
					data->camera_rays[x][y], data->world);
	}
}

void	compute_objects_hits_debug(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			data->hit_objects[x][y] = get_first_hit_obj(
					data->camera_rays[x][y], data->world);
	}
}

t_vec3	get_pixel_pos(int x, int y, t_data *data)
{
	t_vec3	pix_pos;
	float	i;
	float	j;

	i = (float)x / (float)WIDTH;
	j = (float)(HEIGHT - y) / (float)HEIGHT;
	pix_pos = vec3_add3(data->cam.lower_L,
			vec3_mult_float(data->cam.horizintal, i),
			vec3_mult_float(data->cam.vertical, j));
	return (pix_pos);
}

void	compute_camera_rays(t_data *data)
{
	t_vec3	pix_pos;
	t_ray	r;
	int		x;
	int		y;

	x = -1;
	while (++x < WIDTH)
	{
		y = HEIGHT;
		while (--y >= 0)
		{
			pix_pos = get_pixel_pos(x, y, data);
			r = create_ray(
					data->cam.origin,
					vec3_sub(pix_pos, data->cam.origin));
			data->camera_rays[x][y] = r;
			data->hit_objects[x][y] = get_safe_hit_obj(r, data->world);
		}
	}
}

void	put_pixel_color_debug(t_data *data)
{
	t_vec3	pix_col;
	int		x;
	int		y;

	x = 1;
	erase_main_screen(data);
	while (++x < (WIDTH - 2))
	{
		y = 1;
		while (++y < (HEIGHT - 2))
		{
			pix_col = color_debug(data, x, y);
			my_mlx_pixel_put(data, x, y, pix_col);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
