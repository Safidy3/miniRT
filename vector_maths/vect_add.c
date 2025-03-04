#include "../miniRT.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3	vec3_add3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return (t_vec3){a.x + b.x + c.x, a.y + b.y + c.y, a.z + b.z + c.z};
}

t_vec3	vec3_add_float(t_vec3 a, float f)
{
	return ((t_vec3){a.x + f, a.y + f, a.z + f});
}
