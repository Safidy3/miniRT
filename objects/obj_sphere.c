/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:50:02 by safandri          #+#    #+#             */
/*   Updated: 2025/04/09 22:50:02 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_object	*create_sphere(t_vec3 center, float diameter)
{
	t_object	*shpere;

	shpere = (t_object *)malloc(sizeof(t_object));
	shpere->shape = SPHERE;
	shpere->center = center;
	shpere->radius = diameter / 2;
	shpere->direction = create_nullvec();
	shpere->height = 0;
	return (shpere);
}

int	hit_sphere(t_object *obj, const t_ray r, t_hit_record *hit_rec)
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
