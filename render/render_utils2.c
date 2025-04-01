#include "../miniRT.h"

void	compute_objects_hits(t_data *data)
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
	pix_pos = vec3_add3(data->cam.lower_l,
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
			data->hit_objects[x][y] = get_first_hit_obj(r, data->world);
		}
	}
}
