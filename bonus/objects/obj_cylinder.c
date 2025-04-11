/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:25:13 by safandri          #+#    #+#             */
/*   Updated: 2025/04/08 17:26:39 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_object	*create_cylinder(t_vec3 center, t_vec3 direction,
	float diameter, float height)
{
	t_object	*cylinder;

	cylinder = (t_object *)malloc(sizeof(t_object));
	cylinder->shape = CYLINDRE;
	cylinder->center = center;
	cylinder->radius = diameter / 2;
	cylinder->height = height;
	cylinder->direction = direction;
	return (cylinder);
}

static void	compute_cyl_hit_param(t_object *cylinder,
			const t_ray r, t_hit_equation *eq)
{
	t_vec3	a1;
	t_vec3	a2;

	a1 = vec3_cross(cylinder->direction, vec3_sub(r.origin, cylinder->center));
	a1 = vec3_cross(a1, cylinder->direction);
	a2 = vec3_cross(cylinder->direction, r.direction);
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

static int	determine_hit_rec(t_object *cylinder, const t_ray r,
		t_hit_record *rec, float t)
{
	t_vec3	top;
	t_vec3	bottom;
	float	m;

	top = vec3_add(cylinder->center,
			vec3_mult_float(cylinder->direction, cylinder->height / 2));
	bottom = vec3_sub(cylinder->center,
			vec3_mult_float(cylinder->direction, cylinder->height / 2));
	rec->t = t;
	rec->hit_point = ray_point_at(r, t);
	m = vec3_dot(cylinder->direction,
			vec3_sub(rec->hit_point, cylinder->center))
		/ vec3_dot(cylinder->direction, cylinder->direction);
	rec->normal = vec3_normalize(vec3_sub(
				vec3_sub(rec->hit_point, cylinder->center),
				vec3_mult_float(cylinder->direction, m)));
	if (vec3_dot(cylinder->direction, vec3_sub(rec->hit_point, bottom)) > 0)
		if (vec3_dot(cylinder->direction, vec3_sub(rec->hit_point, top)) < 0)
			return (1);
	return (0);
}

int	hit_cylinder(t_object *cylinder,
		const t_ray r, t_hit_record *rec)
{
	t_hit_equation	eq;

	compute_cyl_hit_param(cylinder, r, &eq);
	if (eq.delta < 0 || (eq.t < MIN_T && eq.t > MAX_T))
		return (0);
	if (eq.t > MIN_T && eq.t < MAX_T)
		if (determine_hit_rec(cylinder, r, rec, eq.t))
			return (1);
	if (eq.t2 > MIN_T && eq.t2 < MAX_T)
		if (determine_hit_rec(cylinder, r, rec, eq.t2))
			return (1);
	return (0);
}
