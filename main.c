/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/02/13 15:16:07 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void	*exit(t_data *img)
// {
// 	printf("Hello World");
// }

// int	frame_loop(void *param)
// {
// 	t_data *img = (t_data *) param;
// 	t_camera cam = {
// 		.pos = {0, 0, -5}, 
// 		.target = {0, 0, 0}, 
// 		.up = {0, 1, 0}
// 	};

// 	mlx_clear_window(img->mlx, img->win);
// 	t_mat4	view = mat4_look_at(cam.pos, cam.target, cam.up);
// 	t_mat4	proj = mat4_perspective(FOV, (float)WIDTH / HEIGHT, NEAR, FAR);

// 	render_triangle(img, view, proj);
// 	render_cube(img, view, proj);

// 	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
// 	return 0;
// }

int	frame_loop(void *param)
{
	int	x;
	int	y;
	t_data	*img;

	img = (t_data *)param;
	x = -1;
	y = -1;
	while (++x < WIDTH)
		while (++y < HEIGHT)
			my_mlx_pixel_put(img, x, y, 0x00FF0000);

	return (0);
}


// v.r = (int)(255.99 * ((double)x / (double)WIDTH));
// v.g = (int)(255.99 * ((double)y / (double)HEIGHT));
// v.b = (int)(255.99 * 0.2);
// int color = ((int)v.r << 16) | ((int)v.g << 8) | (int)v.b;

t_vec3	color(const t_ray r)
{
	t_vec3	unit_dir;
	t_vec3	white;
	t_vec3	blue;
	float	t;

	unit_dir = unit_vector(r.direction);
	t = 0.5 * (unit_dir.y + 1.0);
	white = create_vec3(1.0, 1.0, 1.0);
	blue = create_vec3(0.5, 0.7, 1.0);
	return (vec3_add(vec3_mult_float(white, (1.0 - t)), vec3_mult_float(blue, t)));
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_cam	cam;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	cam.lower_L = create_vec3(-2.0, -1.0, -1.0);
	cam.horizintal = create_vec3(4.0, 0.0, 0.0);
	cam.vertical = create_vec3(0.0, 2.0, 0.0);
	cam.origin = create_vec3(0.0, 0.0, 0.0);
	
	t_vec3	pixel_pos;
	for (int y = HEIGHT - 1; y >= 0; y--)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			t_rgb	v;

			double	i = (double)x / (double)WIDTH;
			double	j = (double)(HEIGHT - y) / (double)HEIGHT;

			pixel_pos = vec3_add3(cam.lower_L, vec3_mult_float(cam.horizintal, i), vec3_mult_float(cam.vertical, j));
			t_ray	r = create_ray(cam.origin, vec3_sub(pixel_pos, cam.origin));
			t_vec3	r_col = color(r);
			
			v.r = (int)(255.99 * r_col.x);
			v.g = (int)(255.99 * r_col.y);
			v.b = (int)(255.99 * r_col.z);
			
			int color = ((int)v.r << 16) | ((int)v.g << 8) | (int)v.b;
			my_mlx_pixel_put(&img, x, y, color);
		}
	}
	print_vec3(pixel_pos, "pixel_pos");


	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
