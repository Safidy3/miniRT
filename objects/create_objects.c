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

t_hit_object	*create_sphere(t_vec3 center, float radius)
{
	t_hit_object	*shpere;

	shpere = (t_hit_object *)malloc(sizeof(t_hit_object));;
	shpere->shape = SPHERE;
	shpere->center = center;
	shpere->radius = radius;
	shpere->plane[0] = create_nullvec();
	shpere->plane[1] = create_nullvec();
	shpere->plane[2] = create_nullvec();
	shpere->plane[3] = create_nullvec();
	shpere->direction = create_nullvec();
	return (shpere);
}

t_hit_object	*create_plane(t_vec3 x0, t_vec3 x1, t_vec3 y0, t_vec3 y1)
{
	t_hit_object	*res;

	res = (t_hit_object *)malloc(sizeof(t_hit_object));
	res->shape = PLANE;
	res->center = create_nullvec();
	res->direction = create_nullvec();
	res->radius = 0;
	res->plane[0] = x0;
	res->plane[1] = x1;
	res->plane[2] = y0;
	res->plane[3] = y1;
	return (res);
}

t_hit_object	*create_rectangle(t_vec3 x0, t_vec3 x1, t_vec3 y0, t_vec3 y1)
{
	t_hit_object	*res;

	res = create_plane(x0, x1, y0, y1);
	res->shape = RECTANGLE;
	return (res);
}

t_hit_object	*create_cylinder(t_vec3 center, t_vec3 direction, float radius)
{
	t_hit_object	*cylinder;

	cylinder = (t_hit_object *)malloc(sizeof(t_hit_object));
	cylinder->shape = INF_CYLINDRE;
	cylinder->center = center;
	cylinder->radius = radius;
	cylinder->direction = direction;
	cylinder->plane[0] = create_nullvec();
	cylinder->plane[1] = create_nullvec();
	cylinder->plane[2] = create_nullvec();
	cylinder->plane[3] = create_nullvec();
	return (cylinder);
}

void	scene_add_obj(t_list **world, t_hit_object *obj, t_vec3 color, int use_texture, float material_parameter, int material)
{
	t_list	*new_obj;

	if (!obj)
		return;
	new_obj = ft_lstnew((void *)obj);
	if (!new_obj)
		return free(obj);
	obj->color = vec3_safe_mult_float(color, 1);
	obj->use_texture = use_texture;
	obj->material = material;
	obj->material_parameter = (material == METAL) ? fmin(material_parameter, 1.0) : material_parameter;
	obj->hit_record.t = -1;
	obj->hit_record.hit_point = create_vec3(0, 0, 0);
	obj->hit_record.normal = create_vec3(0, 0, 0);
	obj->hit_record.color = color;
	ft_lstadd_back(world, new_obj);
	obj->id = ft_lstsize(*world) - 1;
}
