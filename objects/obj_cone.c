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
	cone->direction = direction;
	return (cone);
}

int is_valid_hit(t_object *cone, const t_ray r, float t)
{
    t_vec3 hit_point = ray_point_at(r, t);
    t_vec3 axis = vec3_normalize(cone->direction);
    float height = vec3_dot(vec3_sub(hit_point, cone->center), axis);
    return (height >= 0 && height <= cone->height);
}

int hit_cone(t_object *cone, const t_ray r, t_hit_record *rec)
{
    t_vec3 co = vec3_sub(r.origin, cone->center);
	// t_vec3 apex = vec3_add(cone->center, vec3_mult_float(cone->direction, cone->height));

    float k = (cone->radius / cone->height);
    float k_squared = k * k;
    float dv = vec3_dot(r.direction, cone->direction);
    float co_v = vec3_dot(co, cone->direction);

    float a = vec3_dot(r.direction, r.direction) - (1 + k_squared) * dv * dv;
    float b = 2 * (vec3_dot(r.direction, co) - (1 + k_squared) * dv * co_v);
    float c = vec3_dot(co, co) - (1 + k_squared) * co_v * co_v;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (0);

    float sqrt_disc = sqrt(discriminant);
    float t0 = (-b - sqrt_disc) / (2 * a);
    float t1 = (-b + sqrt_disc) / (2 * a);

    float t = t0;
    if (t < 0 || !is_valid_hit(cone, r, t)) {
        t = t1;
        if (t < 0 || !is_valid_hit(cone, r, t))
            return (0);
    }

    t_vec3 hit_point = ray_point_at(r, t);
    float hit_height = vec3_dot(vec3_sub(hit_point, cone->center), cone->direction);

    if (hit_height < 0 || hit_height > cone->height)
        return (0);

    // Calculate normal
    t_vec3 cp = vec3_sub(hit_point, cone->center);
    float projection = vec3_dot(cp, cone->direction);
    t_vec3 normal = vec3_normalize(vec3_sub(cp, vec3_mult_float(cone->direction, projection * (1 + k_squared))));

    // Fill hit record
    rec->t = t;
    rec->hit_point = hit_point;
    rec->normal = normal;
    return (1);
}

// int hit_cone(t_object *cone, const t_ray r, t_hit_record *rec)
// {
// 	t_vec3 apex = vec3_add(cone->center, vec3_mult_float(cone->direction, cone->height));
// 	t_vec3 co = vec3_sub(r.origin, apex);
// 	float radius = cone->radius;
// 	float height = cone->height;
// 	float k = radius / height;
// 	float k2 = k * k;

// 	float dv = vec3_dot(r.direction, cone->direction);
// 	float co_v = vec3_dot(co, cone->direction);

// 	float A = vec3_dot(r.direction, r.direction) - (1 + k2) * dv * dv;
// 	float B = 2 * (vec3_dot(r.direction, co) - (1 + k2) * dv * co_v);
// 	float C = vec3_dot(co, co) - (1 + k2) * co_v * co_v;

// 	float discriminant = B * B - 4 * A * C;
// 	if (discriminant < 0)
// 		return (0);

// 	float t = (-B - sqrt(discriminant)) / (2 * A);
// 	t_vec3 hit_point = vec3_add(r.origin, vec3_mult_float(r.direction, t));

// 	// height check
// 	float hit_height = vec3_dot(vec3_sub(hit_point, apex), cone->direction);
// 	if (hit_height < 0 || hit_height > height)
// 		return (0);

// 	// fill hit_record
// 	rec->t = t;
// 	rec->hit_point = hit_point;
// 	// compute normal, etc...

// 	return (1);
// }
