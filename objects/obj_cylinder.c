#include "../miniRT.h"

t_object	*create_inf_cylinder(t_vec3 center,
	t_vec3 direction, float diameter)
{
	t_object	*cylinder;

	cylinder = (t_object *)malloc(sizeof(t_object));
	cylinder->shape = INF_CYLINDRE;
	cylinder->center = center;
	cylinder->radius = diameter / 2;
	cylinder->direction = direction;
	cylinder->plane[0] = create_nullvec();
	cylinder->plane[1] = create_nullvec();
	cylinder->plane[2] = create_nullvec();
	cylinder->plane[3] = create_nullvec();
	return (cylinder);
}

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
	cylinder->plane[0] = create_nullvec();
	cylinder->plane[1] = create_nullvec();
	cylinder->plane[2] = create_nullvec();
	cylinder->plane[3] = create_nullvec();
	return (cylinder);
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

int	hit_inf_cylindre(t_object *cylinder,
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

int	hit_cylindre(t_object *cylinder,
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
