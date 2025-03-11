/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:24:37 by safandri          #+#    #+#             */
/*   Updated: 2025/03/11 16:24:37 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (t_vec3) {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

t_vec3	vec3_normalize(t_vec3 v)
{
	float	len;

	len = vec3_len(v);
	return (t_vec3){v.x / len, v.y / len, v.z / len};
}

t_vec3	vec3_unit(t_vec3 v)
{
	return (vec3_div_float(v, vec3_len(v)));
}

t_vec3	vec3_random_in_unit_object()
{
	t_vec3	p;
	t_vec3	tmp;

	do
	{
		tmp = vec3_mult_float(create_vec3(drand48(), drand48(), drand48()), 2.0) ;
		p = vec3_sub(tmp, create_vec3(1, 1, 1));
	}
	while (vec3_squared_len(p) >= 1.0);
	return (p);	
}
