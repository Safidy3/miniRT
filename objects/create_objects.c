/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:23:11 by safandri          #+#    #+#             */
/*   Updated: 2025/03/19 11:53:17 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_cam	create_camera(t_vec3 origin, t_vec3 look_at)
{
	t_cam	cam;
	t_vec3	u, v, w;
	float	theta;
	float	half_height;
	float	half_width;
	t_vec3	up;

	up = create_vec3(0, 1, 0);
	theta = FOV * M_PI / 180.0;
	half_height = tan(theta / 2);
	half_width = ((float)WIDTH / (float)HEIGHT) * half_height;

	w = vec3_unit(vec3_sub(origin, look_at));
	u = vec3_unit(vec3_cross(up, w));
	v = vec3_cross(w, u);

	cam.origin = origin;
	cam.horizintal = vec3_mult_float(u, 2 * half_width);
	cam.vertical = vec3_mult_float(v, 2 * half_height);

	cam.lower_L = vec3_sub3(origin, vec3_div_float(cam.horizintal, 2), vec3_div_float(cam.vertical, 2));
	cam.lower_L = vec3_sub(cam.lower_L, w);

	return (cam);
}

t_object	*create_sphere(t_vec3 center, float radius)
{
	t_object	*shpere;

	shpere = (t_object *)malloc(sizeof(t_object));;
	shpere->shape = SPHERE;
	shpere->center = center;
	shpere->center2 = create_nullvec();
	shpere->radius = radius;
	shpere->plane[0] = create_nullvec();
	shpere->plane[1] = create_nullvec();
	shpere->plane[2] = create_nullvec();
	shpere->plane[3] = create_nullvec();
	shpere->direction = create_nullvec();
	return (shpere);
}

t_object	*create_plane(t_vec3 x0, t_vec3 x1, t_vec3 y0, t_vec3 y1)
{
	t_object	*res;

	res = (t_object *)malloc(sizeof(t_object));
	res->shape = PLANE;
	res->center = create_nullvec();
	res->center2 = create_nullvec();
	res->direction = create_nullvec();
	res->radius = 0;
	res->plane[0] = x0;
	res->plane[1] = x1;
	res->plane[2] = y0;
	res->plane[3] = y1;
	return (res);
}

t_object	*create_rectangle(t_vec3 x0, t_vec3 x1, t_vec3 y0, t_vec3 y1)
{
	t_object	*res;

	res = create_plane(x0, x1, y0, y1);
	res->center2 = create_nullvec();
	res->shape = RECTANGLE;
	return (res);
}

t_object	*create_inf_cylinder(t_vec3 center, t_vec3 direction, float radius)
{
	t_object	*cylinder;

	cylinder = (t_object *)malloc(sizeof(t_object));
	cylinder->shape = INF_CYLINDRE;
	cylinder->center = center;
	cylinder->center2 = create_nullvec();
	cylinder->radius = radius;
	cylinder->direction = direction;
	cylinder->plane[0] = create_nullvec();
	cylinder->plane[1] = create_nullvec();
	cylinder->plane[2] = create_nullvec();
	cylinder->plane[3] = create_nullvec();
	return (cylinder);
}

t_object	*create_cylinder(t_vec3 center, t_vec3 center2, float radius)
{
	t_object	*cylinder;
	t_vec3		tmp;

	tmp = vec3_sub(center2, center);
	cylinder = (t_object *)malloc(sizeof(t_object));
	cylinder->shape = CYLINDRE;
	cylinder->center = center;
	cylinder->center2 = center2;
	cylinder->radius = radius;
	cylinder->direction = vec3_div_float(tmp, vec3_len(tmp));
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
	pl->center2 = create_nullvec();
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
	pl->center2 = create_nullvec();
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
	if (!new_obj)
		return (free(obj));
	obj->id = ft_lstsize(*world);
	obj->hit_record.t = -1;
	obj->hit_record.hit_point = create_vec3(0, 0, 0);
	obj->hit_record.normal = create_vec3(0, 0, 0);
	obj->hit_record.color = prts.color;
	if (obj->shape != POINT_LIGHT && obj->shape != AMBIENT_LIGHT)
	{
		obj->proprieties.color = vec3_safe_mult_float(prts.color, 1);
		obj->proprieties.use_texture = prts.use_texture;
		obj->proprieties.material = prts.material;
		obj->proprieties.material_parameter = (prts.material == METAL) ? fmin(prts.material_parameter, 1.0) : prts.material_parameter;
	}
	ft_lstadd_back(world, new_obj);
}
