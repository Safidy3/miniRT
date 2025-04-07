/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:26:06 by safandri          #+#    #+#             */
/*   Updated: 2025/03/29 08:20:36 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

char	*obj_type(int shape)
{
	if (shape == SPHERE)
		return ("SPHERE");
	else if (shape == PLANE)
		return ("PLANE");
	else if (shape == CYLINDRE)
		return ("CYLINDRE");
	else if (shape == CONE)
		return ("CONE");
	else if (shape == POINT_LIGHT)
		return ("POINT_LIGHT");
	else if (shape == AMBIENT_LIGHT)
		return ("AMBIENT_LIGHT");
	else if (shape == CAMERA)
		return ("CAMERA");
	return ("UNKNOWN");
}

char	*join_and_free(char *s1, char *s2)
{
	char	*res;
	char	*tmp;

	tmp = s1;
	res = ft_strjoin(s1, s2);
	return (free(tmp), res);
}

void	black_pixel_put(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->option_addr
		+ (y * data->o_line_length + x * (data->o_bits_per_pixel / 8));
	*(unsigned int *) dst = 0xFFFFFF;
}

void	erase_opt_screen(t_data *data)
{
	int	x;
	int	y;

	x = HEIGHT;
	y = WIDTH;
	while (--y > 0)
		while (--x > 0)
			black_pixel_put(data, x, y);
	mlx_put_image_to_window(data->mlx, data->option_win,
		data->option_img, 0, 0);
}
