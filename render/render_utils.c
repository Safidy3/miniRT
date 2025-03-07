
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
		// pthread_mutex_lock(&data->lock);
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
		// pthread_mutex_unlock(&data->lock);
	}
}
