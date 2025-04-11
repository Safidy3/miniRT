/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:24:43 by safandri          #+#    #+#             */
/*   Updated: 2025/03/28 22:42:11 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	vec3_sub3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return ((t_vec3){a.x - b.x - c.x, a.y - b.y - c.y, a.z - b.z - c.z});
}

t_vec3	vec3_sub_float(t_vec3 a, float f)
{
	return ((t_vec3){a.x - f, a.y - f, a.z - f});
}

int	is_null_vec(t_vec3 v)
{
	if (v.x == 0 && v.x == 0 && v.z == 0)
		return (1);
	return (0);
}
