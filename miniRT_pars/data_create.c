/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:37:16 by safandri          #+#    #+#             */
/*   Updated: 2025/04/09 18:53:01 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_vec3	create_3d(float x, float y, float z)
{
	t_vec3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vec3	create_3dnull(void)
{
	t_vec3	res;

	res.x = 0.0;
	res.y = 0.0;
	res.z = 0.0;
	return (res);
}

t_vec3	create_rgb(float x, float y, float z)
{
	t_vec3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vec3	make_color(t_vec3 a)
{
	t_vec3	res;

	res.x = a.x / 255.0f;
	res.y = a.y / 255.0f;
	res.z = a.z / 255.0f;
	return (res);
}

int	check_normilized(t_vec3 v)
{
	float	res;

	res = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (res < 0.8 || res > 1.2)
		return (0);
	return (1);
}
