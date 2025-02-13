#include "miniRT.h"

t_vec3	create_vec3(float x,float y, float z)
{
	return (t_vec3){x, y, z};
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3 res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec3	vec3_add3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	t_vec3 res;

	res.x = a.x + b.x + c.x;
	res.y = a.y + b.y + c.y;
	res.z = a.z + b.z + c.z;
	return (res);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

t_vec3	vec3_div(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x / b.x, a.y / b.y, a.z / b.z};
}

t_vec3	vec3_mult_float(t_vec3 a, float b)
{
	return (t_vec3){a.x * b, a.y * b, a.z * b};
}

t_vec3	vec3_div_float(t_vec3 a, float b)
{
	return (t_vec3){a.x / b, a.y / b, a.z / b};
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (t_vec3) {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

t_vec3	vec3_normalize(t_vec3 v)
{
	float len = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
	return (t_vec3){v.x/len, v.y/len, v.z/len};
}

/****************************************************************************/

t_ray	create_ray(t_vec3 origin, t_vec3 dir)
{
	t_ray	res;

	res.origin = origin;
	res.origin = dir;
	return (res);
}

t_vec3	ray_point_at(t_vec3 origin, t_vec3 dir, float t)
{
	return (vec3_add(origin, vec3_mult_float(dir, t)));
}








/****************************************************************************/








t_mat4	mat4_look_at(t_vec3 pos, t_vec3 target, t_vec3 up)
{
	t_mat4	mat;
	t_vec3	forward = vec3_normalize(vec3_sub(target, pos));
	t_vec3	right = vec3_normalize(vec3_cross(forward, up));
	t_vec3	new_up = vec3_cross(right, forward);

	mat.m[0][0] = right.x;    mat.m[0][1] = new_up.x;    mat.m[0][2] = -forward.x; mat.m[0][3] = 0;
	mat.m[1][0] = right.y;    mat.m[1][1] = new_up.y;    mat.m[1][2] = -forward.y; mat.m[1][3] = 0;
	mat.m[2][0] = right.z;    mat.m[2][1] = new_up.z;    mat.m[2][2] = -forward.z; mat.m[2][3] = 0;
	mat.m[3][0] = -vec3_dot(right, pos);
	mat.m[3][1] = -vec3_dot(new_up, pos);
	mat.m[3][2] = vec3_dot(forward, pos);  mat.m[3][3] = 1;
	return	(mat);
}

t_vec3	mat4_mult_vec3(t_mat4 mat, t_vec3 v)
{
	t_vec3 result;
	result.x = mat.m[0][0] * v.x + mat.m[1][0] * v.y + mat.m[2][0] * v.z + mat.m[3][0];
	result.y = mat.m[0][1] * v.x + mat.m[1][1] * v.y + mat.m[2][1] * v.z + mat.m[3][1];
	result.z = mat.m[0][2] * v.x + mat.m[1][2] * v.y + mat.m[2][2] * v.z + mat.m[3][2];
	float w = mat.m[0][3] * v.x + mat.m[1][3] * v.y + mat.m[2][3] * v.z + mat.m[3][3];
	
	if (w != 0.0)
	{
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}
	return	(result);
}

t_mat4	mat4_perspective(float fov, float aspect, float near, float far)
{
	t_mat4	mat;
	float	tan_half = tanf(fov * 0.5 * M_PI / 180.0);

	mat.m[0][0] = 1.0 / (aspect * tan_half);
	mat.m[1][1] = 1.0 / tan_half;
	mat.m[2][2] = -(far + near) / (far - near);
	mat.m[2][3] = -1.0;
	mat.m[3][2] = -(2.0 * far * near) / (far - near);
	mat.m[3][3] = 0.0;
	return	(mat);
}
