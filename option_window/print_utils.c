#include "../miniRT.h"

char	*obj_type(int shape)
{
	if (shape == SPHERE)
		return ("SPHERE");
	else if (shape == RECTANGLE)
		return ("RECTANGLE");
	else if (shape == PLANE)
		return ("PLANE");
	else if (shape == INF_CYLINDRE)
		return ("INF_CYLINDRE");
	else if (shape == CYLINDRE)
		return ("CYLINDRE");
	else if (shape == POINT_LIGHT)
		return ("POINT_LIGHT");
	else if (shape == AMBIENT_LIGHT)
		return ("AMBIENT_LIGHT");
	else if (shape == CAMERA)
		return ("CAMERA");
	return ("UNKNOWN");
}

void	put_vector3(t_data *data, t_vec3 center, char *str, int px, int *py)
{
	int padding = 20;
	mlx_string_put(data->mlx, data->option_win, px + padding, *py, 0xFFFFFF, str);
    char x[20];
    char y[20];
    char z[20];
	char *final;
	char *tmp;

	sprintf(x, "%.5f", center.x);
	sprintf(y, "%.5f", center.y);
	sprintf(z, "%.5f", center.z);
	final = ft_strjoin("(", x);
	tmp = final;
	final = ft_strjoin(final, ", ");
	free(tmp);
	tmp = final;
	final = ft_strjoin(final, y);
	free(tmp);
	tmp = final;
	final = ft_strjoin(final, ", ");
	free(tmp);
	tmp = final;
	final = ft_strjoin(final, z);
	free(tmp);
	tmp = final;
	final = ft_strjoin(final, ")");
	mlx_string_put(data->mlx, data->option_win, ft_strlen(str) * px + padding, *py, 0xFFFFFF, final);
	free(tmp);
	free(final);
	*py += 15;
}

void	put_obj_type(t_object *obj, t_data *data, int px, int *py)
{
	char *tmp;
	char *id = ft_itoa(obj->id);
	char *shape = obj_type(obj->shape);

	char *final = ft_strjoin(id, " : ");
	tmp = final;
	final = ft_strjoin(final, shape);
	mlx_string_put(data->mlx, data->option_win, px, *py, 0xFFFFFF, final);
	*py += 15;
	return (free(id), free(final), free(tmp));
}

void	put_float(t_data *data, float value, char *str, int px, int *py)
{
	char v[20];
	int padding = 20;

	sprintf(v, "%.5f", value);
	mlx_string_put(data->mlx, data->option_win, px + padding, *py, 0xFFFFFF, str);
	mlx_string_put(data->mlx, data->option_win, ft_strlen(str) * px + padding, *py, 0xFFFFFF, v);
	*py += 15;
}

void	black_pixel_put(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->option_addr + (y * data->o_line_length + x * (data->o_bits_per_pixel / 8));
	*(unsigned int*)dst = 0xFFFFFF;
}

void	erase_screen(t_data *data)
{
	int	x;
	int	y;

	x = HEIGHT;
	y = WIDTH;
	while (--y > 0)
		while (--x > 0)
			black_pixel_put(data, x, y);
	mlx_put_image_to_window(data->mlx, data->option_win, data->option_img, 0, 0);
}

void option_window(t_data *data, t_object *object)
{
    int x = 7;
	int y = 10;
	t_list	*tmp;
	t_object *obj;

	erase_screen(data);
	if (object == NULL)
	{
		tmp = data->world;
		while (tmp)
		{
			obj = (t_object *)tmp->content;
			put_obj_type(obj, data, x, &y);
			put_vector3(data, obj->center, "Center : ", x, &y);
			put_float(data, obj->radius, "Radius : ", x, &y);
			y += 15;
			tmp = tmp->next;
		}
	}
	else
	{
		put_obj_type(object, data, x, &y);
		put_vector3(data, object->center, "Center : ", x, &y);
		put_vector3(data, object->direction, "Direction : ", x, &y);
		if (object->shape == CAMERA)
			put_float(data, object->radius, "FOV : ", x, &y);
		else
		{
			put_float(data, object->radius, "Radius : ", x, &y);
			printf("radius : %f\n", object->radius);
			put_vector3(data, object->proprieties.color, "Color : ", x, &y);
		}
		
		y += 15;
	}
}
