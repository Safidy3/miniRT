/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_renderer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:52:43 by safandri          #+#    #+#             */
/*   Updated: 2025/01/28 15:54:53 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_square(t_data *img, int o_x, int o_y, int side)
{
	int x;
	int y;

	x = o_x;
	y = o_y;
	side *= UNIT;
	while (x < side)
		my_mlx_pixel_put(img, x++, y, 0x00FF0000);
	while (y < side)
		my_mlx_pixel_put(img, x, y++, 0x00FF0000);
	x = o_x;
	y = o_y;
	while (y < side)
		my_mlx_pixel_put(img, x, y++, 0x00FF0000);
	while (x < side)
		my_mlx_pixel_put(img, x++, y, 0x00FF0000);
}

void	render_circle(t_data *img, int o_x, int o_y, int r)
{
	int		x;
	int		y;
	float	i;

	x = r + o_x;
	y = r + o_y;

	i = 0.0;
	while (i < 180)
	{
		my_mlx_pixel_put(img, r * cos(i) + x, r * sin(i) + y, 0x00FF0000);
		i += 0.1;
	}
}