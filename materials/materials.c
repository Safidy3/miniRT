#include "../miniRT.h"

t_vec3	texture_checker(const t_vec3 point, t_vec3 color1, t_vec3 color2)
{
	float	sines;
	int		checker_size = 3;

	sines = sin(checker_size * point.x) * sin(checker_size * point.y) * sin(checker_size * point.z);
	if (sines < 0)
		return (color1);
	return (color2);
}

t_vec3	ray_reflected(const t_vec3 v, const t_vec3 n)
{
	t_vec3	dot;

	dot = vec3_mult_float(n, (vec3_dot(v, n) * 2));
	return (vec3_sub(v, dot));
}

int refract(const t_vec3 v, const t_vec3 n, float ni_over_nt, t_vec3 *refracted)
{
	t_vec3 uv = vec3_unit(v);
	float dt = vec3_dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);

	if (discriminant > 0)
	{
		*refracted = vec3_sub(vec3_mult_float(vec3_sub(uv, vec3_mult_float(n, dt)), ni_over_nt), 
							  vec3_mult_float(n, sqrt(discriminant)));
		return (1);
	}
	return (0);
}

float schlick_approx(float cosine, float ref_idx)
{
	float	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

int dielectric_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_object obj)
{
	t_vec3	outward_normal;
	t_vec3	refracted;
	t_vec3	reflected;
	float	ni_over_nt;
	float	reflect_prob;
	float	cosine;

	*attenuation = create_vec3(1.0, 1.0, 1.0);  // Glass is transparent
	reflected = ray_reflected(r_in.direction, rec.normal);
	if (vec3_dot(r_in.direction, rec.normal) > 0) 
	{
		outward_normal = vec3_mult_float(rec.normal, -1);
		ni_over_nt = obj.material_parameter;
		// cosine = sqrt(1 - ni_over_nt * ni_over_nt * (1 - vec3_dot(r_in.direction, rec.normal) * vec3_dot(r_in.direction, rec.normal)));
		cosine = obj.material_parameter * vec3_dot(r_in.direction, rec.normal) / vec3_len(r_in.direction);
	}
	else
	{
		outward_normal = rec.normal;
		ni_over_nt = 1.0 / obj.material_parameter;
		// cosine = -vec3_dot(r_in.direction, rec.normal);
		cosine = -vec3_dot(r_in.direction, rec.normal) / vec3_len(r_in.direction);
	}

	if (refract(r_in.direction, outward_normal, ni_over_nt, &refracted))
		reflect_prob = schlick_approx(cosine, obj.material_parameter);
	else
	{
		*scattered = create_ray(rec.hit_point, reflected);
		reflect_prob = 1.0;
	}

	if (drand48() < reflect_prob)
		*scattered = create_ray(rec.hit_point, reflected);
	else
		*scattered = create_ray(rec.hit_point, refracted);

	return (1);
}

int	lamberian_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_object obj)
{
	t_vec3	target;
	(void)r_in;

	target = vec3_add3(rec.hit_point, rec.normal, vec3_random_in_unit_object());
	*scattered = create_ray(rec.hit_point, vec3_sub(target, rec.hit_point));
	if (obj.use_texture)
		*attenuation = texture_checker(rec.hit_point, obj.color, create_vec3(0.12, 0.12, 0.12));
	else
		*attenuation = obj.color;
	return (1);
}

int	metal_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_object obj)
{
	t_vec3	reflected;
	t_vec3	ray_dir;

	reflected = ray_reflected(vec3_unit(r_in.direction), rec.normal);
	ray_dir = vec3_add(reflected, vec3_mult_float(vec3_random_in_unit_object(), obj.material_parameter));
	*scattered = create_ray(rec.hit_point, ray_dir);
	if (obj.use_texture)
		*attenuation = texture_checker(rec.hit_point, obj.color, create_vec3(0.12, 0.12, 0.12));
	else
		*attenuation = obj.color;
	if (vec3_dot(scattered->direction, rec.normal) > 0)
		return (1);
	return (0);
}

int	light_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_object obj)
{
	t_vec3	target;
	(void)r_in;

	target = vec3_add3(rec.hit_point, rec.normal, vec3_random_in_unit_object());
	*scattered = create_ray(rec.hit_point, vec3_sub(target, rec.hit_point));
	*attenuation = obj.color;
	return (1);
}
