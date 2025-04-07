/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/04/06 10:47:01 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_data(t_data *data, t_threads *thread)
{
	int	i;

	i = -1;
	data->mlx = mlx_init();
	data->option_win = mlx_new_window(data->mlx, HEIGHT, WIDTH, "Options");
	data->option_img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	data->option_addr = mlx_get_data_addr(data->option_img,
			&data->o_bits_per_pixel, &data->o_line_length, &data->o_endian);
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
	thread->data = data;
	pthread_mutex_init(&thread->lock, NULL);
	data->thread = thread;
}

void	create_obj(t_list *tmp, t_data *data)
{
	t_object		*new_obj;
	t_obj			*obj;
	t_proprieties	prt;
	int				material;

	new_obj = NULL;
	obj = (t_obj *)tmp->content;
	if (obj->shape == CAMERA)
		create_camera(data, obj->center, obj->normal_vector, obj->diameter);
	else
	{
		if (obj->metalness == 0)
			material = LAMBERTIAN;
		else
			material = METAL;
		prt = create_proprieties(obj->color, material, obj->metalness, obj->use_texture);
		if (obj->shape == SPHERE)
			new_obj = create_sphere(obj->center, obj->diameter);
		else if (obj->shape == PLANE)
			new_obj = create_plane(obj->center, obj->normal_vector);
		else if (obj->shape == CYLINDRE)
			new_obj = create_cylinder(obj->center, obj->normal_vector,
					obj->diameter, obj->height);
		else if (obj->shape == POINT_LIGHT)
		{
			t_proprieties p_white_light = create_proprieties(obj->color, LIGHT, obj->brightness, 0);
			new_obj = create_sphere(obj->center, obj->diameter);
			scene_add_obj(&data->world, new_obj, p_white_light);
			new_obj = create_pl(obj->center, obj->color, obj->brightness);
		}
		else if (obj->shape == AMBIENT_LIGHT)
			new_obj = create_al(obj->color, obj->brightness);
		if (new_obj != NULL)
			scene_add_obj(&data->world, new_obj, prt);
	}
}

void	init_sceen(t_data *data, int argc, char **argv)
{
	t_list	*tmp;
	t_scene	pars;

	get_pars(&pars, argc, argv);
	tmp = pars.obj_lst;
	while (tmp)
	{
		create_obj(tmp, data);
		tmp = tmp->next;
	}
	clear_p_scene(&pars);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_threads	thread;

	data.aa_sample = 100;
	init_data(&data, &thread);
	init_sceen(&data, argc, argv);
	printT(data.world);
	compute_objects_hits_debug(&data);
	put_pixel_color_debug(&data);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
