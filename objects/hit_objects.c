/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:52:43 by safandri          #+#    #+#             */
/*   Updated: 2025/03/29 10:59:03 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static int	hit_sphere(t_object *obj, const t_ray r, t_hit_record *hit_rec)
{
	t_hit_equation	eq;
	t_vec3			oc;
	float			t;

	oc = vec3_sub(r.origin, obj->center);
	eq.a = vec3_dot(r.direction, r.direction);
	eq.b = 2.0 * vec3_dot(oc, r.direction);
	eq.c = vec3_dot(oc, oc) - obj->radius * obj->radius;
	eq.delta = eq.b * eq.b - 4.0 * eq.a * eq.c;
	if (eq.delta < 0)
		return (0);
	eq.t = (-eq.b - sqrt(eq.delta)) / (2.0 * eq.a);
	eq.t2 = (-eq.b + sqrt(eq.delta)) / (2.0 * eq.a);
	if (eq.t > MIN_T && eq.t < MAX_T)
		t = eq.t;
	else if (eq.t2 > MIN_T && eq.t2 < MAX_T)
		t = eq.t2;
	else
		return (0);
	hit_rec->t = t;
	hit_rec->hit_point = ray_point_at(r, t);
	hit_rec->normal = vec3_div_float(
			vec3_sub(hit_rec->hit_point, obj->center), obj->radius);
	return (1);
}

static int	hit_plane(t_object *obj, const t_ray r, t_hit_record *hit_rec)
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
	if (denom > 0)
		hit_rec->normal = vec3_mult_float(obj->direction, -1);
	else
		hit_rec->normal = obj->direction;
	return (1);
}

void	compute_cyl_hit_param(t_object *cylinder,
			const t_ray r, t_hit_equation *eq)
{
	t_vec3	a1;
	t_vec3	a2;

	a1 = vec3_cross(cylinder->direction, vec3_sub(r.origin, cylinder->center));
	a2 = vec3_cross(cylinder->direction, r.direction);
	a1 = vec3_cross(a1, cylinder->direction);
	a2 = vec3_cross(a2, cylinder->direction);
	eq->a = vec3_dot(a2, a2);
	eq->b = vec3_dot(a1, a2) * 2;
	eq->c = vec3_dot(a1, a1) - cylinder->radius * cylinder->radius;
	eq->delta = eq->b * eq->b - 4 * eq->a * eq->c;
	eq->t = (-eq->b - sqrt(eq->delta)) / (2.0 * eq->a);
	eq->t2 = (-eq->b + sqrt(eq->delta)) / (2.0 * eq->a);
	if (eq->t > MIN_T && eq->t < MAX_T)
		;
	else if (eq->t2 > MIN_T && eq->t2 < MAX_T)
		eq->t = eq->t2;
}

static int	hit_inf_cylindre(t_object *cylinder,
		const t_ray r, t_hit_record *hit_rec)
{
	t_hit_equation	eq;
	float			m;

	compute_cyl_hit_param(cylinder, r, &eq);
	if (eq.delta < 0 || (eq.t < MIN_T && eq.t > MAX_T))
		return (0);
	hit_rec->t = eq.t;
	hit_rec->hit_point = ray_point_at(r, eq.t);
	m = vec3_dot(cylinder->direction,
			vec3_sub(hit_rec->hit_point, cylinder->center))
		/ vec3_dot(cylinder->direction, cylinder->direction);
	hit_rec->normal = vec3_sub(
			vec3_sub(hit_rec->hit_point, cylinder->center),
			vec3_mult_float(cylinder->direction, m));
	hit_rec->normal = vec3_normalize(hit_rec->normal);
	return (1);
}

static int	hit_cylindre(t_object *cylinder,
		const t_ray r, t_hit_record *rec)
{
	t_hit_equation	eq;
	t_vec3			top;
	t_vec3			bottom;
	float			m;

	compute_cyl_hit_param(cylinder, r, &eq);
	if (eq.delta < 0 || (eq.t < MIN_T && eq.t > MAX_T))
		return (0);
	rec->t = eq.t;
	rec->hit_point = ray_point_at(r, eq.t);
	top = vec3_add(cylinder->center,
			vec3_mult_float(cylinder->direction, cylinder->height / 2));
	bottom = vec3_sub(cylinder->center,
			vec3_mult_float(cylinder->direction, cylinder->height / 2));
	m = vec3_dot(cylinder->direction,
			vec3_sub(rec->hit_point, cylinder->center))
		/ vec3_dot(cylinder->direction, cylinder->direction);
	rec->normal = vec3_sub(
			vec3_sub(rec->hit_point, cylinder->center),
			vec3_mult_float(cylinder->direction, m));
	rec->normal = vec3_normalize(rec->normal);
	if (vec3_dot(cylinder->direction, vec3_sub(rec->hit_point, bottom)) > 0)
		if (vec3_dot(cylinder->direction, vec3_sub(rec->hit_point, top)) < 0)
			return (1);
	return (0);
}

int	hit_obj(t_object *obj, const t_ray r, t_hit_record *hit_rec)
{
	if (obj->shape == SPHERE)
		return (hit_sphere(obj, r, hit_rec));
	else if (obj->shape == PLANE)
		return (hit_plane(obj, r, hit_rec));
	else if (obj->shape == INF_CYLINDRE)
		return (hit_inf_cylindre(obj, r, hit_rec));
	else if (obj->shape == CYLINDRE)
		return (hit_cylindre(obj, r, hit_rec));
	return (0);
}
