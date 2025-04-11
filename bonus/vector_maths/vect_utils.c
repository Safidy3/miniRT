/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:24:47 by safandri          #+#    #+#             */
/*   Updated: 2025/03/28 22:42:03 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec3	create_vec3(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	create_nullvec(void)
{
	return ((t_vec3){0, 0, 0});
}

t_vec3	vec3_inverse(t_vec3 v)
{
	return ((t_vec3){-v.x, -v.y, -v.z});
}

float	vec3_len(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

float	vec3_squared_len(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
