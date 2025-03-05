
#include "../miniRT.h"

t_vec3	color_debug(const t_ray r, t_list *world)
{
	t_hit_object	*first_hit_obj;

	first_hit_obj = get_first_hit_obj(r, world);
	if (first_hit_obj)
		return (first_hit_obj->hit_record.color);
	return create_vec3(0, 0, 0);
}

void	put_pixel_color_debug(t_data data)
{
	t_vec3	pix_pos;
	t_vec3	pix_col;
	t_ray	r;
	float	i;
	float	j;
	int		x, y;

	printf("Backing ...\n");
	for (x = 0; x < WIDTH; x++)
	{
		for (y = HEIGHT - 1; y >= 0; y--)
		{
			i = (float)x / (float)WIDTH;
			j = (float)(HEIGHT - y) / (float)HEIGHT;
			pix_pos = vec3_add3(data.cam.lower_L, vec3_mult_float(data.cam.horizintal, i), vec3_mult_float(data.cam.vertical, j));
			r = create_ray(data.cam.origin, vec3_sub(pix_pos, data.cam.origin));
			pix_col = color_debug(r, data.world);
			my_mlx_pixel_put(&data, x, y, pix_col);
		}
		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	}
	printf("Finished.\n");
}
