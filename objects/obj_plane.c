#include "../miniRT.h"

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

int	hit_plane(t_object *obj, const t_ray r, t_hit_record *hit_rec)
{
	float	t;
	float	denom;

	denom = vec3_dot(obj->direction, r.direction);
	if (fabs(denom) < 1e-6)
		return (0);
	t = vec3_dot(vec3_sub(obj->center, r.origin), obj->direction) / denom;
	if (t < MIN_T || t > MAX_T)
		return (0);
	hit_rec->t = t;
	hit_rec->hit_point = ray_point_at(r, t);
	if (denom > 0)
		hit_rec->normal = vec3_mult_float(obj->direction, -1);
	else
		hit_rec->normal = obj->direction;
	return (1);
}
