/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:32:43 by safandri          #+#    #+#             */
/*   Updated: 2025/03/20 23:17:11 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	isSame(t_object *obj, t_object *obj2, t_object *obj3, t_object *obj4, t_object *obj5)
{
	if (!obj || !obj2 || !obj3 || !obj4 || !obj5)
		return (0);
	if (obj->id != obj2->id)
		return (0);
	if (obj->id != obj3->id)
		return (0);
	if (obj->id != obj4->id)
		return (0);
	if (obj->id != obj5->id)
		return (0);
	return (1);
}

t_vec3	color_debug(t_data *data, int x, int y)
{
	if (isVoid(x, y, data) || x > WIDTH - 2)
		return (create_nullvec());
	t_object *obj = data->hit_objects[x][y];
	t_object *R_obj = data->hit_objects[x + 1][y];
	t_object *L_obj = data->hit_objects[x - 1][y];
	t_object *D_obj = data->hit_objects[x][y + 1];
	t_object *U_obj = data->hit_objects[x][y - 1];
	if (isSame(R_obj, D_obj, L_obj, U_obj, obj))
		return (obj->hit_record.color);
	else
		return (create_vec3(0.627, 0.125, 0.941));
}

void	compute_objects_hits(t_data *data)
{
	int		x, y;

	for (x = 0; x < WIDTH; x++)
		for (y = 0; y < HEIGHT; y++)
			data->hit_objects[x][y] = get_safe_hit_obj(data->camera_rays[x][y], data->world);
}

void	compute_objects_hits_debug(t_data *data)
{
	int		x, y;

	for (x = 0; x < WIDTH; x++)
		for (y = 0; y < HEIGHT; y++)
			data->hit_objects[x][y] = get_first_hit_obj(data->camera_rays[x][y], data->world);
}

void	compute_camera_rays(t_data *data)
{
	t_vec3	pix_pos;
	t_ray	r;
	float	i, j;
	int		x, y;

	for (x = 0; x < WIDTH; x++)
	{
		i = (float)x / (float)WIDTH;
		for (y = HEIGHT - 1; y >= 0; y--)
		{
			j = (float)(HEIGHT - y) / (float)HEIGHT;
			pix_pos = vec3_add3(data->cam.lower_L, vec3_mult_float(data->cam.horizintal, i), vec3_mult_float(data->cam.vertical, j));
			r = create_ray(data->cam.origin, vec3_sub(pix_pos, data->cam.origin));
			data->camera_rays[x][y] = r;
			data->hit_objects[x][y] = get_safe_hit_obj(r, data->world);
		}
	}
}

void	put_pixel_color_debug(t_data *data)
{
	t_vec3	pix_col;
	int		x, y;

	erase_main_screen(data);
	for (x = 1; x < WIDTH - 2; x++)
	{
		for (y = 1; y < HEIGHT - 2; y++)
		{
			pix_col = color_debug(data, x, y);
			my_mlx_pixel_put(data, x, y, pix_col);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
