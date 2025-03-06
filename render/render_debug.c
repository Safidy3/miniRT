
#include "../miniRT.h"

t_vec3	color_debug(const t_ray r, t_list *world)
{
	t_object	*first_hit_obj;

	first_hit_obj = get_first_hit_obj(r, world);
	if (first_hit_obj)
		return (first_hit_obj->hit_record.color);
	return create_vec3(0, 0, 0);
}

int	isSame(t_object *obj, t_object *obj2)
{
	if (!obj)
		return (0);
	if (obj->id != obj2->id)
		return (0);
	return (1);
}

void	put_pixel_color_debug(t_data data)
{
	t_vec3	pix_pos;
	t_vec3	pix_col;
	t_ray	r;
	float	i;
	float	j;
	int		x, y;

	t_object *hit_objects[WIDTH][HEIGHT];
	for (x = 0; x < WIDTH; x++)
	{
		i = (float)x / (float)WIDTH;
		for (y = HEIGHT - 1; y >= 0; y--)
		{
			j = (float)(HEIGHT - y) / (float)HEIGHT;
			pix_pos = vec3_add3(data.cam.lower_L, vec3_mult_float(data.cam.horizintal, i), vec3_mult_float(data.cam.vertical, j));
			r = create_ray(data.cam.origin, vec3_sub(pix_pos, data.cam.origin));
			pix_col = color_debug(r, data.world);
			my_mlx_pixel_put(&data, x, y, pix_col);
			hit_objects[x][y] = get_first_hit_obj(r, data.world);
		}
	}

	for (x = 0; x < WIDTH - 1; x++)
	{
		i = (float)x / (float)WIDTH;
		if (x == 0 || x == WIDTH - 1)
			continue;
		for (y = HEIGHT - 1; y >= 0; y--)
		{
			j = (float)(HEIGHT - y) / (float)HEIGHT;
			t_object *obj = hit_objects[x][y];
			if (!obj)
				continue;
			t_object *R_obj = hit_objects[x+1][y];
			t_object *L_obj = hit_objects[x-1][y];
			t_object *D_obj = hit_objects[x][y+1];
			t_object *U_obj = hit_objects[x][y-1];
			if (isSame(R_obj, obj) && isSame(L_obj, obj) && isSame(D_obj, obj) && isSame(U_obj, obj))
				continue;
			else
				my_mlx_pixel_put(&data, x, y, create_vec3(0.627, 0.125, 0.941));
		}
	}
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
}
