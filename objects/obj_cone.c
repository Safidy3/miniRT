#include "../miniRT.h"
t_object	*create_cone(t_vec3 center, t_vec3 direction,
	float diameter, float height)
{
	t_object	*cone;

	cone = (t_object *)malloc(sizeof(t_object));
	cone->shape = CONE;
	cone->center = center;
	cone->radius = diameter / 2;
	cone->height = height;
	cone->direction = vec3_normalize(direction);
	return (cone);
}

int	determine_hit_rec(t_object *cone, const t_ray r,
	t_hit_record *rec, float t)
{
	t_vec3	hit_point;
	t_vec3	apex_to_hit;
	float	projection;
	t_vec3	apex;
	float	k2;

	hit_point = ray_point_at(r, t);
	apex_to_hit = vec3_sub(hit_point, cone->center);
	projection = vec3_dot(apex_to_hit, cone->direction);
	if (projection >= 0 && projection <= cone->height)
	{
		rec->hit_point = ray_point_at(r, t);
		apex = vec3_add(cone->center, vec3_mult_float(cone->direction, cone->height));
		k2 = (cone->radius / cone->height) * (cone->radius / cone->height);
		apex_to_hit = vec3_sub(rec->hit_point, apex);
		projection = vec3_dot(apex_to_hit, cone->direction);
		rec->normal = vec3_normalize(vec3_sub(apex_to_hit,
					vec3_mult_float(cone->direction, projection * (1 + k2))));
		rec->t = t;
		return (1);
	}
	return (0);
}

void	compute_hit_param(t_object *cone,
	const t_ray r, t_hit_equation *eq)
{
	t_vec3	apex;
	t_vec3	co;
	float	k2;
	float	dv;
	float	co_v;

	apex = vec3_add(cone->center, vec3_mult_float(cone->direction, cone->height));
	co = vec3_sub(r.origin, apex);
	k2 = (cone->radius / cone->height) * (cone->radius / cone->height);
	dv = vec3_dot(r.direction, cone->direction);
	co_v = vec3_dot(co, cone->direction);
	eq->a = vec3_dot(r.direction, r.direction) - (1 + k2) * dv * dv;
	eq->b = 2 * (vec3_dot(r.direction, co) - (1 + k2) * dv * co_v);
	eq->c = vec3_dot(co, co) - (1 + k2) * co_v * co_v;
	eq->delta = eq->b * eq->b - 4 * eq->a * eq->c;
	if (eq->delta < 0)
		return ;
	eq->t = (-eq->b - sqrt(eq->delta)) / (2 * eq->a);
	eq->t2 = (-eq->b + sqrt(eq->delta)) / (2 * eq->a);
	if (eq->t > MIN_T && eq->t < MAX_T)
		;
	else if (eq->t2 > MIN_T && eq->t2 < MAX_T)
		eq->t = eq->t2;
}

int hit_cone(t_object *cone, const t_ray r, t_hit_record *rec)
{
	t_hit_equation	eq;
	float			t;
	
	compute_hit_param(cone, r, &eq);
	if (eq.delta < 0 || (eq.t < MIN_T && eq.t > MAX_T))
		return (0);
	t = eq.t;
	if (t < MIN_T || t > MAX_T || !determine_hit_rec(cone, r, rec, t))
		return (0);
	t = eq.t2;
	if (t < MIN_T || t > MAX_T || !determine_hit_rec(cone, r, rec, t))
		return (0);
	return (1);
}
