/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/04/03 09:41:51 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_data(t_data *data)
{
	int	i;

	i = -1;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->world = NULL;
	data->seleced_object = NULL;
	data->camera_rays = (t_ray **)malloc(sizeof(t_ray *) * WIDTH);
	while (++i < WIDTH)
		data->camera_rays[i] = (t_ray *)malloc(sizeof(t_ray) * HEIGHT);
	data->hit_objects = (t_object ***)malloc(sizeof(t_object **) * WIDTH);
	i = -1;
	while (++i < WIDTH)
		data->hit_objects[i] = (t_object **)malloc(sizeof(t_object *) * HEIGHT);
}

// void	init_sceen(t_data *data, int argc, char **argv)
// {
// 	t_scene			pars;
// 	t_list			*tmp;
// 	t_obj			*obj;
// 	t_proprieties	prt;

// 	get_pars(&pars, argc, argv);
// 	tmp = pars.obj_lst;
// 	while (tmp)
// 	{
// 		obj = (t_obj *)(tmp->content);
// 		prt = create_proprieties(obj->color, LAMBERTIAN, 0, 0);
// 		if (obj->shape == POINT_LIGHT)
// 		{
			
// 		}
// 		else if (obj->shape == AMBIENT_LIGHT)
// 		{
			
// 		}
// 		else if (obj->shape == CAMERA)
// 		{
			
// 		}
// 		else if (obj->shape == CYLINDRE)
// 		{
			
// 		}
// 		else if (obj->shape == PLANE)
// 		{
			
// 		}
// 		else if (obj->shape == SPHERE)
// 		{
			
// 		}
// 		print_cylinder(obj);
// 		tmp = tmp->next;
// 	}

	
	
// 	clear_p_scene(&pars);
// }

int	main(int argc, char **argv)
{
	t_data		data;
	(void)argc;
	(void)argv;
	
	init_data(&data);

	// init_sceen(&data, argc, argv);

	add_sceen(&data);
	printT(data.world);
	// put_pixel_color(&data);
	put_pixel_color_debug(&data);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
