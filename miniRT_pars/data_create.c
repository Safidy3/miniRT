/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:37:16 by safandri          #+#    #+#             */
/*   Updated: 2025/04/03 09:41:01 by safandri         ###   ########.fr       */
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

