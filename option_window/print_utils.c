#include "../miniRT.h"

char	*obj_type(int shape)
{
	if (shape == 0)
		return ("SPHERE");
	else if (shape == 1)
		return ("RECTANGLE");
	else if (shape == 2)
		return ("PLANE");
	else if (shape == 3)
		return ("INF_CYLINDRE");
	else if (shape == 4)
		return ("CYLINDRE");
	else if (shape == 5)
		return ("POINT_LIGHT");
	else if (shape == 6)
		return ("AMBIENT_LIGHT");
	return ("UNKNOWN");
}

void	put_vector3(t_data *data, t_vec3 center, char *str, int px, int *py)
{
	int padding = 20;
	mlx_string_put(data->mlx, data->option_win, px + padding, *py, 0xFFFFFF, str);
	char *x = ft_itoa(center.x);
	char *y = ft_itoa(center.y);
	char *z = ft_itoa(center.z);
	char *final;
	char *tmp;

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
	free(tmp);
	free(final);
	*py += 15;
}

void	put_int(t_data *data, int value, char *str, int px, int *py)
{
	char *v;
	int padding = 20;

	v = ft_itoa(value);
	mlx_string_put(data->mlx, data->option_win, px + padding, *py, 0xFFFFFF, str);
	mlx_string_put(data->mlx, data->option_win, ft_strlen(str) * px + padding, *py, 0xFFFFFF, v);
	free(v);
	*py += 15;
}

void option_window(t_data *data)
{
    data->option_win = mlx_new_window(data->mlx, HEIGHT, WIDTH, "Options");
	int x = 7;
	int y = 10;
	
	while (data->world)
	{
		t_object *obj = (t_object *)data->world->content;
		put_obj_type(obj, data, x, &y);
		put_vector3(data, obj->center, "Center : ", x, &y);
		put_int(data, obj->radius, "Radius : ", x, &y);
		data->world = data->world->next;
		y += 15;
	}
}
