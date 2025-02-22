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

t_vec3	ray_reflected(const t_vec3 v, const t_vec3 n)
{
	t_vec3	dot;

	dot = vec3_mult_float(n, (vec3_dot(v, n) * 2));
	return (vec3_sub(v, dot));
}

int	lamberian_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_shpere obj)
{
	t_vec3	target;
	t_vec3	albedo;
	(void)r_in;

	albedo = obj.albedo;
	target = vec3_add3(rec.hit_point, rec.normal, vec3_random_in_unit_object());
	*scattered = create_ray(rec.hit_point, vec3_sub(target, rec.hit_point));
	*attenuation = albedo;
	return (1);
}

int	metal_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_shpere obj)
{
	t_vec3	reflected;
	t_vec3	ray_dir;
	t_vec3	albedo;

	albedo = obj.albedo;
	reflected = ray_reflected(vec3_unit(r_in.direction), rec.normal);
	ray_dir = vec3_add(reflected, vec3_mult_float(vec3_random_in_unit_object(), obj.metal_fuzz));
	*scattered = create_ray(rec.hit_point, ray_dir);
	*attenuation = albedo;
	if (vec3_dot(scattered->direction, rec.normal) > 0)
		return (1);
	return (0);
}


/*############################################### MATERIAL ###############################################*/


t_material	create_material(t_vec3 albedo, t_vec3 metal, t_vec3 lambertian, int use_metal)
{
	t_material	res;

	res.albedo = albedo;
	res.metal = metal;
	res.lambertian = lambertian;
	res.use_metal = use_metal;
	return (res);
}




/*############################################### HITABLE ###############################################*/

/********************* sphere **********************/

t_hit_shpere	create_sphere(t_vec3 center, float radius)
{
	t_hit_shpere res;
	res.center = center;
	res.radius = radius;
	res.id = 0;
	return (res);
}

void	scene_add_sphere(t_list **world, t_vec3 center, float radius, t_vec3 albedo, int use_metal, int metal_fuzz)
{
	t_hit_shpere	*shpere = (t_hit_shpere *)malloc(sizeof(t_hit_shpere));
	shpere->id = 0;
	shpere->center = center;
	shpere->radius = radius;

	shpere->albedo = albedo;
	shpere->use_metal = use_metal;
	if (metal_fuzz < 1)
		shpere->metal_fuzz = metal_fuzz;
	else
		shpere->metal_fuzz = 1;

	shpere->hit_record.t = -1;
	shpere->hit_record.hit_point = create_vec3(0, 0, 0);
	shpere->hit_record.normal = create_vec3(0, 0, 0);
	shpere->hit_record.color = create_vec3(0, 0, 0);
	t_list *obj = ft_lstnew((void *)shpere);

	ft_lstadd_back(world, obj);
}

void	delete_obj(void *obj)
{
	free(obj);
}

void	clear_sceen(t_list **world)
{
	if (world && *world)
	{
		ft_lstclear(world, &delete_obj);
		*world = NULL;
	}
}

t_hit_shpere	*make_obj(t_list *obj)
{
	if (obj)
		return ((t_hit_shpere *)obj->content);
	else
		return (NULL);
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
