/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:24:23 by safandri          #+#    #+#             */
/*   Updated: 2025/04/06 10:28:03 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	lamberian_scatter_ray(const t_ray r_in, t_vec3 *attenuation,
		t_ray *scattered, t_object *obj)
{
	t_vec3	target;

	(void)r_in;
	target = vec3_add3(obj->hit_record.hit_point,
			obj->hit_record.normal,
			vec3_random_in_unit_object());
	*scattered = create_ray(obj->hit_record.hit_point,
			vec3_sub(target, obj->hit_record.hit_point));
	if (obj->proprieties.use_texture)
		*attenuation = texture_checker(obj->hit_record.hit_point,
				obj->proprieties.color, create_vec3(0.12, 0.12, 0.12));
	else
		*attenuation = obj->proprieties.color;
	return (1);
}

int	metal_scatter_ray(const t_ray r_in, t_vec3 *attenuation,
	t_ray *scattered, t_object *obj)
{
	t_vec3	reflected;
	t_vec3	ray_dir;

	reflected = ray_reflected(vec3_unit(r_in.direction),
			obj->hit_record.normal);
	ray_dir = vec3_add(reflected, vec3_mult_float(
				vec3_random_in_unit_object(), 1 - obj->proprieties.parameter));
	*scattered = create_ray(obj->hit_record.hit_point, ray_dir);
	if (obj->proprieties.use_texture)
		*attenuation = texture_checker(obj->hit_record.hit_point,
				obj->proprieties.color, create_vec3(0.12, 0.12, 0.12));
	else
		*attenuation = obj->proprieties.color;
	if (vec3_dot(scattered->direction, obj->hit_record.normal) > 0)
		return (1);
	return (0);
}

int	light_scatter_ray(const t_ray r_in, t_vec3 *attenuation,
		t_ray *scattered, t_object *obj)
{
	t_vec3	target;

	(void)r_in;
	target = vec3_add3(obj->hit_record.hit_point,
			obj->hit_record.normal, vec3_random_in_unit_object());
	*scattered = create_ray(obj->hit_record.hit_point,
			vec3_sub(target, obj->hit_record.hit_point));
	*attenuation = obj->proprieties.color;
	return (1);
}

void	compute_refraction_direction(const t_ray r_in,
		t_object *obj, t_dielectric *d)
{
	if (vec3_dot(r_in.direction, obj->hit_record.normal) > 0)
	{
		d->outward_normal = vec3_mult_float(obj->hit_record.normal, -1);
		d->ni_over_nt = obj->proprieties.parameter;
		d->cosine = obj->proprieties.parameter
			* vec3_dot(r_in.direction, obj->hit_record.normal)
			/ vec3_len(r_in.direction);
	}
	else
	{
		d->outward_normal = obj->hit_record.normal;
		d->ni_over_nt = 1.0 / obj->proprieties.parameter;
		d->cosine = -vec3_dot(r_in.direction, obj->hit_record.normal)
			/ vec3_len(r_in.direction);
	}
}

int	dielectric_scatter_ray(const t_ray r_in, t_vec3 *attenuation,
		t_ray *scattered, t_object *obj)
{
	t_dielectric	d;

	*attenuation = create_vec3(1.0, 1.0, 1.0);
	d.reflected = ray_reflected(r_in.direction, obj->hit_record.normal);
	compute_refraction_direction(r_in, obj, &d);
	if (refract(r_in.direction, d.outward_normal, d.ni_over_nt, &d.refracted))
		d.reflect_prob = schlick_approx(d.cosine, obj->proprieties.parameter);
	else
	{
		*scattered = create_ray(obj->hit_record.hit_point, d.reflected);
		d.reflect_prob = 1.0;
	}
	if (drand48() < d.reflect_prob)
		*scattered = create_ray(obj->hit_record.hit_point, d.reflected);
	else
		*scattered = create_ray(obj->hit_record.hit_point, d.refracted);
	return (1);
}
