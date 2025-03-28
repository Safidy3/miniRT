/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:24:23 by safandri          #+#    #+#             */
/*   Updated: 2025/03/29 08:55:30 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int dielectric_scatter_ray(const t_ray r_in, t_vec3 *attenuation, t_ray *scattered, t_object *obj)
{
	t_vec3	outward_normal;
	t_vec3	refracted;
	t_vec3	reflected;
	float	ni_over_nt;
	float	reflect_prob;
	float	cosine;

	*attenuation = create_vec3(1.0, 1.0, 1.0);
	reflected = ray_reflected(r_in.direction, obj->hit_record.normal);
	if (vec3_dot(r_in.direction, obj->hit_record.normal) > 0) 
	{
		outward_normal = vec3_mult_float(obj->hit_record.normal, -1);
		ni_over_nt = obj->proprieties.parameter;
		cosine = obj->proprieties.parameter * vec3_dot(r_in.direction, obj->hit_record.normal) / vec3_len(r_in.direction);
	}
	else
	{
		outward_normal = obj->hit_record.normal;
		ni_over_nt = 1.0 / obj->proprieties.parameter;
		cosine = -vec3_dot(r_in.direction, obj->hit_record.normal) / vec3_len(r_in.direction);
	}

	if (refract(r_in.direction, outward_normal, ni_over_nt, &refracted))
		reflect_prob = schlick_approx(cosine, obj->proprieties.parameter);
	else
	{
		*scattered = create_ray(obj->hit_record.hit_point, reflected);
		reflect_prob = 1.0;
	}

	if (drand48() < reflect_prob)
		*scattered = create_ray(obj->hit_record.hit_point, reflected);
	else
		*scattered = create_ray(obj->hit_record.hit_point, refracted);

	return (1);
}

int	lamberian_scatter_ray(const t_ray r_in, t_vec3 *attenuation, t_ray *scattered, t_object *obj)
{
	t_vec3	target;
	(void)r_in;

	target = vec3_add3(obj->hit_record.hit_point, obj->hit_record.normal, vec3_random_in_unit_object());
	*scattered = create_ray(obj->hit_record.hit_point, vec3_sub(target, obj->hit_record.hit_point));
	if (obj->proprieties.use_texture)
		*attenuation = texture_checker(obj->hit_record.hit_point, obj->proprieties.color, create_vec3(0.12, 0.12, 0.12));
	else
		*attenuation = obj->proprieties.color;
	return (1);
}

int	metal_scatter_ray(const t_ray r_in, t_vec3 *attenuation, t_ray *scattered, t_object *obj)
{
	t_vec3	reflected;
	t_vec3	ray_dir;

	reflected = ray_reflected(vec3_unit(r_in.direction), obj->hit_record.normal);
	ray_dir = vec3_add(reflected, vec3_mult_float(vec3_random_in_unit_object(), obj->proprieties.parameter));
	*scattered = create_ray(obj->hit_record.hit_point, ray_dir);
	if (obj->proprieties.use_texture)
		*attenuation = texture_checker(obj->hit_record.hit_point, obj->proprieties.color, create_vec3(0.12, 0.12, 0.12));
	else
		*attenuation = obj->proprieties.color;
	if (vec3_dot(scattered->direction, obj->hit_record.normal) > 0)
		return (1);
	return (0);
}

int	light_scatter_ray(const t_ray r_in, t_vec3 *attenuation, t_ray *scattered, t_object *obj)
{
	t_vec3	target;
	(void)r_in;

	target = vec3_add3(obj->hit_record.hit_point, obj->hit_record.normal, vec3_random_in_unit_object());
	*scattered = create_ray(obj->hit_record.hit_point, vec3_sub(target, obj->hit_record.hit_point));
	*attenuation = obj->proprieties.color;
	return (1);
}

t_proprieties	create_proprieties(t_vec3 color, int material, float parameter, int use_texture)
{
	t_proprieties	prts;

	prts.color = color;
	prts.parameter = parameter;
	prts.material = material;
	prts.use_texture = use_texture;
	return (prts);
}