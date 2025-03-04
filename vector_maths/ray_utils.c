#include "../miniRT.h"

t_ray	create_ray(t_vec3 origin, t_vec3 dir)
{
	t_ray	res;

	res.origin = origin;
	res.direction = dir;
	return (res);
}

t_vec3	ray_point_at(t_ray ray, float t)
{
	return (vec3_add(ray.origin, vec3_mult_float(ray.direction, t)));
}
