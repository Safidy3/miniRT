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

t_proprieties	det_proprts(t_obj *obj)
{
	t_proprieties	res;
	int				material;
	float			param;

	if (obj->shape != POINT_LIGHT)
	{
		if (obj->metalness == 0)
			material = LAMBERTIAN;
		else
			material = METAL;
		param = obj->metalness;
	}
	else
	{
		material = LIGHT;
		param = obj->brightness;
	}
	res = create_proprieties(obj->color, material, param, obj->use_texture);
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
		create_camera(data, obj->center, obj->normal_vector, obj->diameter);
	else
	{
		prt = det_proprts(obj);
		if (obj->shape == SPHERE || obj->shape == POINT_LIGHT)
			new_obj = create_sphere(obj->center, obj->diameter);
		else if (obj->shape == PLANE)
			new_obj = create_plane(obj->center, obj->normal_vector);
		else if (obj->shape == CYLINDRE)
			new_obj = create_cylinder(obj->center, obj->normal_vector,
					obj->diameter, obj->height);
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


void	bonus_sceen7(t_data *data)
{

	float	side = 5;
	float	ud = 4;
	float	height = 6;
	float	radius = 3;
	float	dept1 = -3.5;
	float	dept2 = -7;

	// t_proprieties purple = create_proprieties(create_vec3(0.490196078, 0, 1), LAMBERTIAN, 0, 0);
	t_proprieties green_lamb = create_proprieties(create_vec3(0, 1, 0), LAMBERTIAN, 0, 0);
	t_proprieties white_lamb = create_proprieties(create_vec3(0.329411765, 0.329411765, 0.329411765), LAMBERTIAN, 0, 0);
	t_proprieties white_metal = create_proprieties(create_vec3(1, 1, 1), METAL, 0.5, 0);
	t_proprieties Blue_lamb = create_proprieties(create_vec3(0, 0, 1), METAL, 0, 0);

	t_object *shpere = create_sphere(create_vec3(0, -2, -4), 2.0);
	scene_add_obj(&data->world, shpere, Blue_lamb);

	t_object *shpere1 = create_sphere(create_vec3(-side, ud, dept1), radius);
	scene_add_obj(&data->world, shpere1, white_metal);
	t_object *shpere2 = create_sphere(create_vec3(side, ud, dept1), radius);
	scene_add_obj(&data->world, shpere2, white_metal);
	t_object *shpere3 = create_sphere(create_vec3(-side, ud, dept2), radius);
	scene_add_obj(&data->world, shpere3, white_metal);
	t_object *shpere4 = create_sphere(create_vec3(side, ud, dept2), radius);
	scene_add_obj(&data->world, shpere4, white_metal);

	t_object *shpere5 = create_sphere(create_vec3(-side, -ud, dept1), radius);
	scene_add_obj(&data->world, shpere5, white_metal);
	t_object *shpere6 = create_sphere(create_vec3(side, -ud, dept1), radius);
	scene_add_obj(&data->world, shpere6, white_metal);
	t_object *shpere7 = create_sphere(create_vec3(-side, -ud, dept2), radius);
	scene_add_obj(&data->world, shpere7, white_metal);
	t_object *shpere8 = create_sphere(create_vec3(side, -ud, dept2), radius);
	scene_add_obj(&data->world, shpere8, white_metal);

	t_object *cylinder1 = create_cylinder(create_vec3(-side, 0, dept1), create_vec3(0, 1, 0), radius / 2, height);
	scene_add_obj(&data->world, cylinder1, white_metal);
	t_object *cylinder2 = create_cylinder(create_vec3(side, 0, dept1), create_vec3(0, 1, 0), radius / 2, height);
	scene_add_obj(&data->world, cylinder2, white_metal);
	t_object *cylinder3 = create_cylinder(create_vec3(-side, 0, dept2), create_vec3(0, 1, 0), radius / 2, height);
	scene_add_obj(&data->world, cylinder3, white_metal);
	t_object *cylinder4 = create_cylinder(create_vec3(side, 0, dept2), create_vec3(0, 1, 0), radius / 2, height);
	scene_add_obj(&data->world, cylinder4, white_metal);

	t_object *up = create_plane(create_vec3(0, 3.5, 0), create_vec3(0, -1, 0));
	t_object *down = create_plane(create_vec3(0, -3.5, 0), create_vec3(0, 1, 0));
	t_object *forward = create_plane(create_vec3(0, 0, -10), create_vec3(0, 0, -1));
	t_object *back = create_plane(create_vec3(0, 0, 5), create_vec3(0, 0, -1));
	scene_add_obj(&data->world, back, white_lamb);
	scene_add_obj(&data->world, forward, green_lamb);
	scene_add_obj(&data->world, up, white_lamb);
	scene_add_obj(&data->world, down, white_lamb);

	t_proprieties p_pint_light = create_proprieties(create_vec3(1, 0, 1), LIGHT, 0, 0);
	t_proprieties p_blue_light = create_proprieties(create_vec3(0, 0.784313725, 1), LIGHT, 0, 0);
	t_object *shpere_light = create_sphere(create_vec3(-side + 2, 0, -5), 3);
	t_object *shpere_light2 = create_sphere(create_vec3(side - 2, 0, -5), 3);
	scene_add_obj(&data->world, shpere_light, p_pint_light);
	scene_add_obj(&data->world, shpere_light2, p_blue_light);

	t_object *ambent_light = create_al(create_vec3(1, 1, 1), 0.0);
	scene_add_obj(&data->world, ambent_light, white_lamb);

	create_camera(data, create_vec3(0, 0, 1), create_vec3(0, 0, -1), 90);
	compute_camera_rays(data);
}


// int	main()
int	main(int argc, char **argv)
{
	t_data		data;
	t_threads	thread;

	data.aa_sample = ANTIALIASING_SAMPLES;
	init_data(&data, &thread);
	init_sceen(&data, argc, argv);
	// bonus_sceen7(&data);
	printT(data.world);
	compute_objects_hits_debug(&data);
	put_pixel_color_debug(&data);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
