/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:50:44 by safandri          #+#    #+#             */
/*   Updated: 2025/01/28 15:56:17 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "stdio.h"
#include "unistd.h"
#include <math.h>

#define UNIT 5

typedef struct s_camera
{
	float	x;
	float	y;
	float	zoom;
}			t_camera;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	render_circle(t_data *img, int o_x, int o_y, int r);
void	render_square(t_data *img, int o_x, int o_y, int side);