/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:52:43 by safandri          #+#    #+#             */
/*   Updated: 2025/03/18 14:10:49 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static int	hit_sphere(t_object *obj, const t_ray r, t_hit_record *hit_rec)
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

static int hit_plane(t_object *obj, const t_ray r, t_hit_record *hit_rec)
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
	hit_rec->normal = (denom > 0) ? vec3_mult_float(obj->direction, -1) : obj->direction;
	return (1);
}

// int	p_inside_rect(t_vec3 p, t_vec3 x0, t_vec3 x1, t_vec3 y0)
// {
// 	return (1);
// }

static int hit_rectangle(t_object *obj, const t_ray r, t_hit_record *hit_rec)
{
	float	t;
	float	denom;
    t_vec3	normal;

	normal = vec3_unit(vec3_cross(
        vec3_sub(obj->plane[1], obj->plane[0]), 
        vec3_sub(obj->plane[3], obj->plane[0])
    ));

    denom = vec3_dot(normal, r.direction);
    if (fabs(denom) < 1e-6)
        return (0);
    t = vec3_dot(vec3_sub(obj->plane[0], r.origin), normal) / denom;
    if (t < MIN_T || t > MAX_T)
        return (0);

    hit_rec->t = t;
    hit_rec->hit_point = ray_point_at(r, t);
    hit_rec->normal = (denom > 0) ? vec3_mult_float(normal, -1) : normal;;
	// if (p_inside_rect(hit_rec->hit_point, obj->plane[0], obj->plane[1], obj->plane[3]))
	// 	return (1);

    return (0);
}

static int	hit_inf_cylindre(t_object *cylinder, const t_ray r, t_hit_record *hit_rec)
{
	t_vec3 a1 = vec3_cross(cylinder->direction, vec3_sub(r.origin, cylinder->center));
	t_vec3 a2 = vec3_cross(cylinder->direction, r.direction);
	a1 = vec3_cross(a1, cylinder->direction);
	a2 = vec3_cross(a2, cylinder->direction);

	float a = vec3_dot(a2, a2);
	float b = vec3_dot(a1, a2) * 2;
	float c = vec3_dot(a1, a1) - cylinder->radius * cylinder->radius;

	float delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);

	float t = (-b - sqrt(delta)) / (2.0 * a);
	if (t > MIN_T && t < MAX_T)
	{
		hit_rec->t = t;
		hit_rec->hit_point = ray_point_at(r, t);
		float m = vec3_dot(cylinder->direction, vec3_sub(hit_rec->hit_point, cylinder->center)) / vec3_dot(cylinder->direction, cylinder->direction);
		hit_rec->normal = vec3_sub(vec3_sub(hit_rec->hit_point, cylinder->center), vec3_mult_float(cylinder->direction, m));
		hit_rec->normal = vec3_normalize(hit_rec->normal);
		return (1);
	}

	t = (-b + sqrt(delta)) / (2.0 * a);
	if (t > MIN_T && t < MAX_T)
	{
		hit_rec->t = t;
		hit_rec->hit_point = ray_point_at(r, t);
		float m = vec3_dot(cylinder->direction, vec3_sub(hit_rec->hit_point, cylinder->center)) / vec3_dot(cylinder->direction, cylinder->direction);
		hit_rec->normal = vec3_sub(vec3_sub(hit_rec->hit_point, cylinder->center), vec3_mult_float(cylinder->direction, m));
		hit_rec->normal = vec3_normalize(hit_rec->normal);
		return (1);
	}
	return (0);
}

static int	hit_cylindre(t_object *cylinder, const t_ray r, t_hit_record *hit_rec)
{
	t_vec3	a1;
	t_vec3	a2;

	a1 = vec3_cross(cylinder->direction, vec3_sub(r.origin, cylinder->center));
	a1 = vec3_cross(a1, cylinder->direction);
	a2 = vec3_cross(cylinder->direction, r.direction);
	a2 = vec3_cross(a2, cylinder->direction);

	float a = vec3_dot(a2, a2);
	float b = vec3_dot(a1, a2) * 2;
	float c = vec3_dot(a1, a1) - cylinder->radius * cylinder->radius;

	float delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);

	t_vec3 top_cap = vec3_add(cylinder->center, vec3_mult_float(cylinder->direction, cylinder->height / 2));
	t_vec3 bottom_cap = vec3_sub(cylinder->center, vec3_mult_float(cylinder->direction, cylinder->height / 2));

	float t = (-b - sqrt(delta)) / (2.0 * a);
	if (t > MIN_T && t < MAX_T)
	{
		hit_rec->t = t;
		hit_rec->hit_point = ray_point_at(r, t);
		float m = vec3_dot(cylinder->direction, vec3_sub(hit_rec->hit_point, cylinder->center)) / vec3_dot(cylinder->direction, cylinder->direction);
		hit_rec->normal = vec3_sub(vec3_sub(hit_rec->hit_point, cylinder->center), vec3_mult_float(cylinder->direction, m));
		hit_rec->normal = vec3_normalize(hit_rec->normal);
		if (vec3_dot(cylinder->direction, vec3_sub(hit_rec->hit_point, bottom_cap)) > 0)
			if (vec3_dot(cylinder->direction, vec3_sub(hit_rec->hit_point, top_cap)) < 0)
				return (1);
	}

	t = (-b + sqrt(delta)) / (2.0 * a);
	if (t > MIN_T && t < MAX_T)
	{
		hit_rec->t = t;
		hit_rec->hit_point = ray_point_at(r, t);
		float m = vec3_dot(cylinder->direction, vec3_sub(hit_rec->hit_point, cylinder->center)) / vec3_dot(cylinder->direction, cylinder->direction);
		hit_rec->normal = vec3_sub(vec3_sub(hit_rec->hit_point, cylinder->center), vec3_mult_float(cylinder->direction, m));
		hit_rec->normal = vec3_normalize(hit_rec->normal);
		if (vec3_dot(cylinder->direction, vec3_sub(hit_rec->hit_point, bottom_cap)) > 0)
			if (vec3_dot(cylinder->direction, vec3_sub(hit_rec->hit_point, top_cap)) < 0)
				return (1);
	}
	return (0);
}

int	hit_obj(t_object *obj, const t_ray r, t_hit_record *hit_rec)
{
	if (obj->shape == SPHERE)
		return (hit_sphere(obj, r, hit_rec));
	else if (obj->shape == PLANE)
		return (hit_plane(obj, r, hit_rec));
	else if (obj->shape == RECTANGLE)
		return (hit_rectangle(obj, r, hit_rec));
	else if (obj->shape == INF_CYLINDRE)
		return (hit_inf_cylindre(obj, r, hit_rec));
	else if (obj->shape == CYLINDRE)
		return (hit_cylindre(obj, r, hit_rec));
	return (0);
}
