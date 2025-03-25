/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:23:11 by safandri          #+#    #+#             */
/*   Updated: 2025/03/21 00:35:26 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	create_camera(t_data *data, t_vec3 origin, t_vec3 look_at, float fov)
{
	t_vec3	w;

	w = vec3_unit(vec3_sub(origin, look_at));
	update_camera(data, origin, look_at, fov);
	scene_add_obj(&data->world, create_obj_cam(origin, w, fov), create_proprieties(create_nullvec(), 0, 0, 0));
}

void	update_camera(t_data *data, t_vec3 origin, t_vec3 look_at, float fov)
{
	t_vec3	u, v, w;
	float	theta;
	float	half_height;
	float	half_width;
	t_vec3	up;

	up = create_vec3(0, 1, 0);
	theta = fov * M_PI / 180.0;
	half_height = tan(theta / 2);
	half_width = ((float)WIDTH / (float)HEIGHT) * half_height;

	data->cam.fov = fov;
	data->cam.origin = origin;
	data->cam.direction = look_at;

	w = vec3_unit(vec3_sub(origin, look_at));
	u = vec3_unit(vec3_cross(up, w));
	v = vec3_cross(w, u);

	data->cam.horizintal = vec3_mult_float(u, 2 * half_width);
	data->cam.vertical = vec3_mult_float(v, 2 * half_height);
	data->cam.lower_L = vec3_sub3(origin, vec3_div_float(data->cam.horizintal, 2), vec3_div_float(data->cam.vertical, 2));
	data->cam.lower_L = vec3_sub(data->cam.lower_L, w);
}

t_cam	dup_camera(t_cam cam)
{
	t_cam	new_cam;

	new_cam.horizintal = cam.horizintal;
	new_cam.lower_L = cam.lower_L;
	new_cam.origin = cam.origin;
	new_cam.vertical = cam.vertical;
	return (new_cam);
}

t_object	*create_obj_cam(t_vec3 origin, t_vec3 direction, float fov)
{
	t_object	*cam;

	cam = (t_object *)malloc(sizeof(t_object));
	cam->shape = CAMERA;
	cam->center = origin;
	cam->radius = fov;
	cam->direction = direction;
	cam->plane[0] = create_nullvec();
	cam->plane[1] = create_nullvec();
	cam->plane[2] = create_nullvec();
	cam->plane[3] = create_nullvec();
	cam->proprieties.color = create_nullvec();
	cam->proprieties.material = 0;
	cam->proprieties.material_parameter = 0;
	cam->proprieties.use_texture = 0;
	return (cam);
}

t_object	*create_sphere(t_vec3 center, float diameter)
{
	t_object	*shpere;

	shpere = (t_object *)malloc(sizeof(t_object));;
	shpere->shape = SPHERE;
	shpere->center = center;
	shpere->radius = diameter / 2;
	shpere->plane[0] = create_nullvec();
	shpere->plane[1] = create_nullvec();
	shpere->plane[2] = create_nullvec();
	shpere->plane[3] = create_nullvec();
	shpere->direction = create_nullvec();
	return (shpere);
}

t_object	*create_plane(t_vec3 center, t_vec3 direction)
{
	t_object	*res;

	res = (t_object *)malloc(sizeof(t_object));
	res->shape = PLANE;
	res->center = center;
	res->direction = direction;
	res->radius = 0;
	res->plane[0] = create_nullvec();
	res->plane[1] = create_nullvec();
	res->plane[2] = create_nullvec();
	res->plane[3] = create_nullvec();
	return (res);
}

t_object	*create_rectangle(t_vec3 x0, t_vec3 x1, t_vec3 y0, t_vec3 y1)
{
	t_object	*res;

	res = (t_object *)malloc(sizeof(t_object));
	res->shape = PLANE;
	res->center = create_nullvec();
	res->direction = create_nullvec();
	res->radius = 0;
	res->plane[0] = x0;
	res->plane[1] = x1;
	res->plane[2] = y0;
	res->plane[3] = y1;
	res->shape = RECTANGLE;
	return (res);
}

t_object	*create_inf_cylinder(t_vec3 center, t_vec3 direction, float diameter)
{
	t_object	*cylinder;

	cylinder = (t_object *)malloc(sizeof(t_object));
	cylinder->shape = INF_CYLINDRE;
	cylinder->center = center;
	cylinder->radius = diameter / 2;
	cylinder->direction = direction;
	cylinder->plane[0] = create_nullvec();
	cylinder->plane[1] = create_nullvec();
	cylinder->plane[2] = create_nullvec();
	cylinder->plane[3] = create_nullvec();
	return (cylinder);
}

t_object	*create_cylinder(t_vec3 center, t_vec3 direction, float diameter, float height)
{
	t_object	*cylinder;

	cylinder = (t_object *)malloc(sizeof(t_object));
	cylinder->shape = CYLINDRE;
	cylinder->center = center;
	cylinder->radius = diameter / 2;
	cylinder->height = height;
	cylinder->direction = direction;
	cylinder->plane[0] = create_nullvec();
	cylinder->plane[1] = create_nullvec();
	cylinder->plane[2] = create_nullvec();
	cylinder->plane[3] = create_nullvec();
	return (cylinder);
}

t_object	*create_point_light(t_vec3 center, t_vec3 color, float brightness)
{
	t_object		*pl;
	t_proprieties	prts;

	pl = (t_object *)malloc(sizeof(t_object));
	pl->shape = POINT_LIGHT;
	pl->center = center;
	pl->radius = 0;
	pl->direction = create_nullvec();
	pl->plane[0] = create_nullvec();
	pl->plane[1] = create_nullvec();
	pl->plane[2] = create_nullvec();
	pl->plane[3] = create_nullvec();
	prts.color = vec3_mult_float(color, brightness);
	prts.material = 0;
	prts.material_parameter = brightness;
	prts.use_texture = 0;
	pl->proprieties = prts;
	return (pl);
}

t_object	*create_ambient(t_vec3 color, float brightness)
{
	t_object		*pl;
	t_proprieties	prts;

	pl = (t_object *)malloc(sizeof(t_object));
	pl->shape = AMBIENT_LIGHT;
	pl->center = create_nullvec();
	pl->radius = 0;
	pl->direction = create_nullvec();
	pl->plane[0] = create_nullvec();
	pl->plane[1] = create_nullvec();
	pl->plane[2] = create_nullvec();
	pl->plane[3] = create_nullvec();
	prts.color = vec3_mult_float(color, brightness);
	prts.material = 0;
	prts.material_parameter = brightness;
	prts.use_texture = 0;
	pl->proprieties = prts;
	return (pl);
}

void	scene_add_obj(t_list **world, t_object *obj, t_proprieties prts)
{
	t_list	*new_obj;

	if (!obj)
		return;
	new_obj = ft_lstnew((void *)obj);
	obj->id = ft_lstsize(*world);
	obj->hit_record.t = -1;
	obj->hit_record.hit_point = create_vec3(0, 0, 0);
	obj->hit_record.normal = create_vec3(0, 0, 0);
	obj->hit_record.color = prts.color;
	if (obj->shape != POINT_LIGHT && obj->shape != AMBIENT_LIGHT && obj->shape != CAMERA)
	{
		obj->proprieties.color = vec3_safe_mult_float(prts.color, 1);
		obj->proprieties.use_texture = prts.use_texture;
		obj->proprieties.material = prts.material;
		obj->proprieties.material_parameter = (prts.material == METAL) ? fmin(prts.material_parameter, 1.0) : prts.material_parameter;
	}
	ft_lstadd_back(world, new_obj);
}

t_list	*deep_copy_world(t_list *world)
{
	t_list		*new_world;
	t_object	*obj;
	t_object	*new_obj;

	new_world = NULL;
	while (world)
	{
		obj = make_obj(world);
		if (obj->shape == SPHERE)
			new_obj = create_sphere(obj->center, obj->radius * 2);
		else if (obj->shape == RECTANGLE)
			new_obj = create_rectangle(obj->plane[0], obj->plane[1], obj->plane[2], obj->plane[3]);
		else if (obj->shape == PLANE)
			new_obj = create_plane(obj->center, obj->direction);
		else if (obj->shape == INF_CYLINDRE)
			new_obj = create_inf_cylinder(obj->center, obj->direction, obj->radius * 2);
		else if (obj->shape == CYLINDRE)
			new_obj = create_cylinder(obj->center, obj->direction, obj->radius * 2, obj->height);
		else if (obj->shape == POINT_LIGHT)
			new_obj = create_point_light(obj->center, obj->proprieties.color, obj->proprieties.material_parameter);
		else if (obj->shape == AMBIENT_LIGHT)
			new_obj = create_ambient(obj->proprieties.color, obj->proprieties.material_parameter);
		else if (obj->shape == CAMERA)
			new_obj = create_obj_cam(obj->center, obj->direction, obj->radius);

		new_obj->id = ft_lstsize(world);
		new_obj->hit_record.t = -1;
		new_obj->hit_record.hit_point = create_vec3(0, 0, 0);
		new_obj->hit_record.normal = create_vec3(0, 0, 0);
		new_obj->hit_record.color = obj->proprieties.color;
		if (new_obj->shape != POINT_LIGHT && new_obj->shape != AMBIENT_LIGHT)
		{
			new_obj->proprieties.color = vec3_safe_mult_float(obj->proprieties.color, 1);
			new_obj->proprieties.use_texture = obj->proprieties.use_texture;
			new_obj->proprieties.material = obj->proprieties.material;
			new_obj->proprieties.material_parameter = (obj->proprieties.material == METAL) ? fmin(obj->proprieties.material_parameter, 1.0) : obj->proprieties.material_parameter;
		}

		ft_lstadd_back(&new_world, ft_lstnew((void *)new_obj));
		world = world->next;
	}
	return (new_world);
}
