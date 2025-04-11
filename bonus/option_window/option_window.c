/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:32:30 by safandri          #+#    #+#             */
/*   Updated: 2025/04/08 17:36:28 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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

void	put_spetific_data(t_data *data, t_object *object, t_put_vec3 *p)
{
	if (object->shape == CAMERA)
		put_float(data, object->radius, "FOV : ", p);
	else
	{
		put_float(data, object->radius, "Radius : ", p);
		put_vector3(data, object->proprieties.color, "Color : ", p);
	}
	if (object->proprieties.material == LIGHT)
		put_float(data, object->proprieties.parameter, "Brightness : ", p);
	else
		put_float(data, object->proprieties.parameter, "Metalness : ", p);
}

void	option_window(t_data *data, t_object *object)
{
	t_put_vec3	p;

	p.px = 7;
	p.py = 10;
	p.padding = 20;
	erase_opt_screen(data);
	if (object == NULL)
		return ;
	put_obj_type(object, data, &p);
	put_vector3(data, object->center, "Center : ", &p);
	put_vector3(data, object->direction, "Direction : ", &p);
	put_spetific_data(data, object, &p);
	if (object->shape == CYLINDRE || object->shape == CONE)
		put_float(data, object->height, "Height : ", &p);
	put_float(data, object->proprieties.use_texture, "Textured : ", &p);
	p.py += 15;
}
