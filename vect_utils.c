#include "miniRT.h"

/*############################################### VECTORS ###############################################*/

t_vec3	create_vec3(float x,float y, float z)
{
	return (t_vec3){x, y, z};
}

void	print_vec3(t_vec3 v, char *name)
{
	if (name)
		printf("%s -> ", name);
	printf("x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3	vec3_add3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return (t_vec3){a.x + b.x + c.x, a.y + b.y + c.y, a.z + b.z + c.z};
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec3	vec3_sub3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return (t_vec3){a.x - b.x - c.x, a.y - b.y - c.y, a.z - b.z - c.z};
}

/*********************************/

t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

t_vec3	vec3_mult_float(t_vec3 a, float b)
{
	return (t_vec3){a.x * b, a.y * b, a.z * b};
}

t_vec3	vec3_div(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x / b.x, a.y / b.y, a.z / b.z};
}

t_vec3	vec3_div_float(t_vec3 a, float b)
{
	return (t_vec3){a.x / b, a.y / b, a.z / b};
}

/*********************************/

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

float	vec3_len(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

float	vec3_squared_len(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3	vec3_normalize(t_vec3 v)
{
	float	len;

	len = vec3_len(v);
	return (t_vec3){v.x / len, v.y / len, v.z / len};
}

t_vec3	vec3_unit(t_vec3 v)
{
	return (vec3_div_float(v, vec3_len(v)));
}

/*############################################### RAYS ###############################################*/

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


/*############################################### HITABLE ###############################################*/
/************* SPHERE **************/


// int	hit_sphere(t_vec3 center, float radius, const t_ray r)
// {
// 	t_vec3	oc = vec3_sub(r.origin, center);
// 	float	a = vec3_dot(r.direction, r.direction);
// 	float	b = 2 * vec3_dot(oc, r.direction);
// 	float	c = vec3_dot(oc, oc) - radius * radius;
// 	float	delta = b * b - 4 * a * c;
// 	if (delta < 0)
// 		return (-1.0);
// 	return ((-b - sqrt(delta)) / (2 * a));
// }

// int	hit_sphere(void	*obj, const t_ray r, float tmin, float tmax, t_hit_record *rec)
// {
// 	t_hit_shpere	sphere = *(t_hit_shpere *)obj;
// 	t_vec3	oc = vec3_sub(r.origin, sphere.center);
// 	float	a = vec3_dot(r.direction, r.direction);
// 	float	b = 2.0 * vec3_dot(oc, r.direction);
// 	float	c = vec3_dot(oc, oc) - (sphere.radius * sphere.radius);
// 	float	delta = (b * b) - (4 * a * c);

// 	if (delta > 0)
// 	{
// 		float sqrt_delta = sqrt(delta);
// 		float tmp = (-b - sqrt_delta) / (2.0 * a);  // FIRST ROOT
// 		if (tmp < tmax && tmp > tmin)
// 		{
// 			rec->t = tmp;
// 			rec->p = ray_point_at(r, rec->t);
// 			rec->normal = vec3_div_float(vec3_sub(rec->p, sphere.center), sphere.radius);
// 			return (1);
// 		}

// 		tmp = (-b + sqrt_delta) / (2.0 * a);  // SECOND ROOT
// 		if (tmp < tmax && tmp > tmin)
// 		{
// 			rec->t = tmp;
// 			rec->p = ray_point_at(r, rec->t);
// 			rec->normal = vec3_div_float(vec3_sub(rec->p, sphere.center), sphere.radius);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

int	loop_hit_function(t_hitable_list l, const t_ray r, float tmin, float tmax, t_hit_record *rec)
{
	t_hit_record	tmp_rec;
	int				hit_anything = 0;
	float			closest_so_far = tmax;

	for (int i = 0; i < l.list_size; i++)
	{
		if (l.hit_list[i].hit_function(l.hit_list[i].obj, r, tmin, tmax, rec))
		{
			hit_anything = 1;
			closest_so_far = tmp_rec.t;
			*rec = tmp_rec;
		}
	}
	return (hit_anything);
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
