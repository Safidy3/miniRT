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

int is_valid_hit(t_object *cone, const t_ray r, float t)
{
    t_vec3 hit_point = ray_point_at(r, t);
    t_vec3 apex_to_hit = vec3_sub(hit_point, cone->center);
    float projection = vec3_dot(apex_to_hit, cone->direction);

    // Check if hit is between base and apex
    return (projection >= 0 && projection <= cone->height);
}

int hit_cone(t_object *cone, const t_ray r, t_hit_record *rec)
{
    t_vec3 apex = vec3_add(cone->center, vec3_mult_float(cone->direction, cone->height));
    t_vec3 co = vec3_sub(r.origin, apex);

    float k = cone->radius / cone->height;
    float k2 = k * k;

    float dv = vec3_dot(r.direction, cone->direction);
    float co_v = vec3_dot(co, cone->direction);

    float a = vec3_dot(r.direction, r.direction) - (1 + k2) * dv * dv;
    float b = 2 * (vec3_dot(r.direction, co) - (1 + k2) * dv * co_v);
    float c = vec3_dot(co, co) - (1 + k2) * co_v * co_v;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (0);

    float sqrt_disc = sqrt(discriminant);
    float t0 = (-b - sqrt_disc) / (2 * a);
    float t1 = (-b + sqrt_disc) / (2 * a);

    float t = t0;
    if (t < 0 || !is_valid_hit(cone, r, t))
    {
        t = t1;
        if (t < 0 || !is_valid_hit(cone, r, t))
            return (0);
    }

    rec->hit_point = ray_point_at(r, t);
    t_vec3 apex_to_hit = vec3_sub(rec->hit_point, apex);
    float projection = vec3_dot(apex_to_hit, cone->direction);
    rec->normal = vec3_normalize(vec3_sub(apex_to_hit,
                vec3_mult_float(cone->direction, projection * (1 + k2))));
    rec->t = t;
    return (1);
}
