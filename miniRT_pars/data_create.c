/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:37:16 by safandri          #+#    #+#             */
/*   Updated: 2025/04/03 06:24:00 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_3dcoord	create_3d(float x, float y, float z)
{
	t_3dcoord	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_3dcoord	create_3dnull(void)
{
	t_3dcoord	res;

	res.x = 0.0;
	res.y = 0.0;
	res.z = 0.0;
	return (res);
}

t_rgb	create_rgb(float x, float y, float z)
{
	t_rgb	res;

	res.r = x;
	res.g = y;
	res.b = z;
	return (res);
}

t_rgb	create_rgbnull(void)
{
	t_rgb	res;

	res.r = 0.0;
	res.g = 0.0;
	res.b = 0.0;
	return (res);
}
