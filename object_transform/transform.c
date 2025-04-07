/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:44:03 by safandri          #+#    #+#             */
/*   Updated: 2025/03/29 11:03:10 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	rotate_x(t_data *data, float theta)
{
	t_object	*obj;

	obj = data->seleced_object;
	if (!obj)
		return ;
	obj->direction.y = obj->direction.y * cos(theta)
		- obj->direction.z * sin(theta);
	obj->direction.z = obj->direction.y * sin(theta)
		+ obj->direction.z * cos(theta);
	obj->direction = vec3_unit(obj->direction);
}

void	rotate_y(t_data *data, float theta)
{
	t_object	*obj;

	obj = data->seleced_object;
	if (!obj)
		return ;
	obj->direction.x = obj->direction.x * cos(theta)
		+ obj->direction.z * sin(theta);
	obj->direction.z = -obj->direction.x * sin(theta)
		+ obj->direction.z * cos(theta);
	obj->direction = vec3_unit(obj->direction);
}

void	rotate_z(t_data *data, float theta)
{
	t_object	*obj;

	obj = data->seleced_object;
	if (!obj)
		return ;
	obj->direction.x = obj->direction.x * cos(theta)
		- obj->direction.y * sin(theta);
	obj->direction.y = obj->direction.x * sin(theta)
		+ obj->direction.y * cos(theta);
	obj->direction = vec3_unit(obj->direction);
}

void	translate_object(t_data *data, t_vec3 translation)
{
	t_object	*obj;

	obj = data->seleced_object;
	if (!obj)
		return ;
	obj->center = vec3_add(obj->center, translation);
	if (obj->shape == CAMERA)
		update_camera(data, obj->center, data->cam.direction, data->cam.fov);
	else
		compute_objects_hits_debug(data);
	put_pixel_color_debug(data);
}
