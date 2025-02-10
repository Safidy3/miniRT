/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/02/10 09:31:29 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	*exit(t_data *img)
{
	printf("Hello World");
}

int	frame_loop(void *param)
{
    t_data *img = (t_data *) param;
	t_camera cam = {
        .pos = {0, 0, -5}, 
        .target = {0, 0, 0}, 
        .up = {0, 1, 0}
    };

    mlx_clear_window(img->mlx, img->win);
    t_mat4	view = mat4_look_at(cam.pos, cam.target, cam.up);
    t_mat4	proj = mat4_perspective(FOV, (float)WIDTH / HEIGHT, NEAR, FAR);

    render_triangle(img, view, proj);
    // render_cube(img, view, proj);

    mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
    return 0;
}

int main(void)
{
	void    *mlx;
	void    *win;
	t_data  img;

	mlx = mlx_init();
	printf("hello world\n");
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "3D Cube");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	img.mlx = mlx;
	img.win = win;


	mlx_hook(img.win, 2, 1L<<0, exit, &img);
	mlx_loop_hook(mlx, frame_loop, &img);
	mlx_loop(mlx);
	return 0;
}
