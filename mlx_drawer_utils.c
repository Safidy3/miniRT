/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_drawer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:15:23 by safandri          #+#    #+#             */
/*   Updated: 2025/02/13 10:49:19 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void draw_line(t_data *img, t_vec3 p0, t_vec3 p1, int color)
{
	int dx = abs((int)p1.x - (int)p0.x);
	int dy = abs((int)p1.y - (int)p0.y);
	int sx = p0.x < p1.x ? 1 : -1;
	int sy = p0.y < p1.y ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		my_mlx_pixel_put(img, (int)p0.x, (int)p0.y, color);
		if ((int)p0.x == (int)p1.x && (int)p0.y == (int)p1.y) break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			p0.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			p0.y += sy;
		}
	}
}