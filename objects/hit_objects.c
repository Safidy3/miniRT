/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_renderer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:52:43 by safandri          #+#    #+#             */
/*   Updated: 2025/02/10 09:15:47 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	hit_sphere(t_hit_object *obj, const t_ray r, t_hit_record *hit_rec)
{
	t_vec3	oc = vec3_sub(r.origin, obj->center);
	float	a = vec3_dot(r.direction, r.direction);
	float	b = 2.0 * vec3_dot(oc, r.direction);
	float	c = vec3_dot(oc, oc) - obj->radius * obj->radius;
	float	delta = b * b - 4.0 * a * c;

	if (delta < 0)
		return (0);

	float t = (-b - sqrt(delta)) / (2.0 * a);
	if (t > MIN_T && t < MAX_T)
	{
		hit_rec->t = t;
		hit_rec->hit_point = ray_point_at(r, t);
		hit_rec->normal = vec3_div_float(vec3_sub(hit_rec->hit_point, obj->center), obj->radius);
		return (1);
	}

	t = (-b + sqrt(delta)) / (2.0 * a);
	if (t > MIN_T && t < MAX_T)
	{
		hit_rec->t = t;
		hit_rec->hit_point = ray_point_at(r, t);
		hit_rec->normal = vec3_div_float(vec3_sub(hit_rec->hit_point, obj->center), obj->radius);
		return (1);
	}
	return (0);
}

int hit_plane(t_hit_object *p, const t_ray r, t_hit_record *hit_rec)
{
	float	t;
	float	denom;
	t_vec3	normal;

	normal = vec3_unit(vec3_cross(
		vec3_sub(p->plane[1], p->plane[0]), 
		vec3_sub(p->plane[3], p->plane[0])
	));

	denom = vec3_dot(normal, r.direction);
	if (fabs(denom) < 1e-6)
		return (0);
	t = vec3_dot(vec3_sub(p->plane[0], r.origin), normal) / denom;
	if (t < MIN_T || t > MAX_T)
		return (0);
	hit_rec->t = t;
	hit_rec->hit_point = ray_point_at(r, t);
	hit_rec->normal = (denom > 0) ? vec3_mult_float(normal, -1) : normal;
	return (1);
}

// int	p_inside_rect(t_vec3 p, t_vec3 x0, t_vec3 x1, t_vec3 y0)
// {
// 	return (1);
// }

int hit_rectangle(t_hit_object *p, const t_ray r, t_hit_record *hit_rec)
{
	float	t;
	float	denom;
    t_vec3	normal;

	normal = vec3_unit(vec3_cross(
        vec3_sub(p->plane[1], p->plane[0]), 
        vec3_sub(p->plane[3], p->plane[0])
    ));

    denom = vec3_dot(normal, r.direction);
    if (fabs(denom) < 1e-6)
        return (0);
    t = vec3_dot(vec3_sub(p->plane[0], r.origin), normal) / denom;
    if (t < MIN_T || t > MAX_T)
        return (0);
	
    hit_rec->t = t;
    hit_rec->hit_point = ray_point_at(r, t);
    hit_rec->normal = (denom > 0) ? vec3_mult_float(normal, -1) : normal;;
	// if (p_inside_rect(hit_rec->hit_point, p->plane[0], p->plane[1], p->plane[3]))
	// 	return (1);

    return (0);
}

int	hit_obj(t_hit_object *obj, const t_ray r, t_hit_record *hit_rec)
{
	if (obj->id == SPHERE)
		return (hit_sphere(obj, r, hit_rec));
	else if (obj->id == PLANE)
		return (hit_plane(obj, r, hit_rec));
	else if (obj->id == RECTANGLE)
		return (hit_rectangle(obj, r, hit_rec));
	return (0);
}
