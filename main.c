/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/04/09 22:00:24 by safandri         ###   ########.fr       */
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

t_proprieties	det_proprts(t_obj *obj)
{
	t_proprieties	res;
	int				material;

	if (obj->shape != POINT_LIGHT)
	{
		if (obj->metalness == 0)
			material = LAMBERTIAN;
		else
			material = METAL;
		res = create_proprieties(obj->color, material,
				obj->metalness, obj->use_texture);
	}
	else
		res = create_proprieties(
				vec3_mult_float(obj->color, obj->brightness),
				LIGHT, obj->brightness, obj->use_texture);
	return (res);
}

void	create_obj(t_list *tmp, t_data *data)
{
	t_object		*new_obj;
	t_obj			*obj;
	t_proprieties	prt;

	new_obj = NULL;
	obj = (t_obj *)tmp->content;
	if (obj->shape == CAMERA)
		create_camera(data, obj->center, vec3_normalize(obj->normal_vector), obj->diameter);
	else
	{
		prt = det_proprts(obj);
		if (obj->shape == SPHERE || obj->shape == POINT_LIGHT)
			new_obj = create_sphere(obj->center, obj->diameter);
		else if (obj->shape == PLANE)
			new_obj = create_plane(obj->center, vec3_normalize(obj->normal_vector));
		else if (obj->shape == CYLINDRE)
			new_obj = create_cylinder(obj->center, vec3_normalize(obj->normal_vector),
					obj->diameter, obj->height);
		else if (obj->shape == CONE)
			new_obj = create_cone(obj->center, vec3_normalize(obj->normal_vector),
					obj->diameter, obj->height);
		else if (obj->shape == AMBIENT_LIGHT)
			new_obj = create_al(obj->color, obj->brightness);
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

	data.aa_sample = ANTIALIASING_SAMPLES;
	init_data(&data, &thread);
	init_sceen(&data, argc, argv);
	compute_objects_hits_debug(&data);
	put_pixel_color_debug(&data);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
