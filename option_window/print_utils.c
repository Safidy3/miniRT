/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:26:06 by safandri          #+#    #+#             */
/*   Updated: 2025/03/29 08:20:36 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*join_and_free(char *s1, char *s2)
{
	char	*res;
	char	*tmp;

	tmp = s1;
	res = ft_strjoin(s1, s2);
	return (free(tmp), res);
}

void	put_vector3(t_data *data, t_vec3 center, char *str, t_put_vec3 *p)
{
	char	*final;

	mlx_string_put(data->mlx, data->option_win,
		p->px + p->padding, p->py, 0xFFFFFF, str);
	sprintf(p->x, "%.5f", center.x);
	sprintf(p->y, "%.5f", center.y);
	sprintf(p->z, "%.5f", center.z);
	final = ft_strjoin("(", p->x);
	final = join_and_free(final, ", ");
	final = join_and_free(final, p->y);
	final = join_and_free(final, ", ");
	final = join_and_free(final, p->z);
	final = join_and_free(final, ")");
	mlx_string_put(data->mlx, data->option_win,
		ft_strlen(str) * p->px + p->padding, p->py, 0xFFFFFF, final);
	free(final);
	p->py += 15;
}

void	put_obj_type(t_object *obj, t_data *data, t_put_vec3 *p)
{
	char	*tmp;
	char	*id;
	char	*shape;
	char	*final;

	id = ft_itoa(obj->id);
	shape = obj_type(obj->shape);
	final = ft_strjoin(id, " : ");
	tmp = final;
	final = ft_strjoin(final, shape);
	mlx_string_put(data->mlx, data->option_win, p->px, p->py, 0xFFFFFF, final);
	p->py += 15;
	return (free(id), free(final), free(tmp));
}

void	put_float(t_data *data, float value, char *str, t_put_vec3 *p)
{
	sprintf(p->f, "%.5f", value);
	mlx_string_put(data->mlx, data->option_win,
		p->px + p->padding, p->py, 0xFFFFFF, str);
	mlx_string_put(data->mlx, data->option_win,
		ft_strlen(str) * p->px + p->padding, p->py, 0xFFFFFF, p->f);
	p->py += 15;
}

void	black_pixel_put(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->option_addr
		+ (y * data->o_line_length + x * (data->o_bits_per_pixel / 8));
	*(unsigned int *) dst = 0xFFFFFF;
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
	mlx_put_image_to_window(data->mlx, data->option_win,
		data->option_img, 0, 0);
}

void	option_window(t_data *data, t_object *object)
{
	t_put_vec3	p;

	p.px = 7;
	p.py = 10;
	p.padding = 20;
	erase_screen(data);
	if (object == NULL)
		return ;
	put_obj_type(object, data, &p);
	put_vector3(data, object->center, "Center : ", &p);
	put_vector3(data, object->direction, "Direction : ", &p);
	if (object->shape == CYLINDRE)
		put_float(data, object->height, "Height : ", &p);
	if (object->shape == CAMERA)
		put_float(data, object->radius, "FOV : ", &p);
	else
	{
		put_float(data, object->radius, "Radius : ", &p);
		put_vector3(data, object->proprieties.color, "Color : ", &p);
	}
	p.py += 15;
}
