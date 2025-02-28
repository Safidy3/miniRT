#include "miniRT.h"

/*############################################### VECTORS ###############################################*/

t_vec3	create_vec3(float x,float y, float z)
{
	return (t_vec3){x, y, z};
}

t_vec3	create_nullvec()
{
	return (t_vec3){0, 0, 0};
}

void	print_vec3(t_vec3 v, char *name)
{
	if (name)
		printf("%s -> ", name);
	printf("x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3	vec3_add3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return (t_vec3){a.x + b.x + c.x, a.y + b.y + c.y, a.z + b.z + c.z};
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec3	vec3_sub3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return (t_vec3){a.x - b.x - c.x, a.y - b.y - c.y, a.z - b.z - c.z};
}

/*********************************/

t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

t_vec3	vec3_mult_float(t_vec3 a, float b)
{
	return (t_vec3){a.x * b, a.y * b, a.z * b};
}

t_vec3	vec3_safe_mult_float(t_vec3 a, float b)
{
	t_vec3 v = {a.x * b, a.y * b, a.z * b};
	if (v.x > 1)
		v.x = 1;
	if (v.y > 1)
		v.y = 1;
	if (v.z > 1)
		v.z = 1;
	return (v);
}

t_vec3	vec3_div(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x / b.x, a.y / b.y, a.z / b.z};
}

t_vec3	vec3_div_float(t_vec3 a, float b)
{
	return (t_vec3){a.x / b, a.y / b, a.z / b};
}

/*********************************/

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (t_vec3) {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

float	vec3_len(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

float	vec3_squared_len(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3	vec3_normalize(t_vec3 v)
{
	float	len;

	len = vec3_len(v);
	return (t_vec3){v.x / len, v.y / len, v.z / len};
}

t_vec3	vec3_unit(t_vec3 v)
{
	return (vec3_div_float(v, vec3_len(v)));
}

t_vec3	vec3_random_in_unit_object()
{
	t_vec3	p;
	t_vec3	tmp;

	do
	{
		tmp = vec3_mult_float(create_vec3(drand48(), drand48(), drand48()), 2.0) ;
		p = vec3_sub(tmp, create_vec3(1, 1, 1));
	}
	while (vec3_squared_len(p) >= 1.0);
	return (p);	
}

int		isNullVec3(t_vec3 v)
{
	if (v.x == 0 && v.x == 0 && v.z == 0)
		return (1);
	return (0);
}

/*############################################### RAYS ###############################################*/

t_ray	create_ray(t_vec3 origin, t_vec3 dir)
{
	t_ray	res;

	res.origin = origin;
	res.direction = dir;
	return (res);
}

t_vec3	ray_point_at(t_ray ray, float t)
{
	return (vec3_add(ray.origin, vec3_mult_float(ray.direction, t)));
}

/*############################################### TEXTURE ###############################################*/

t_vec3	texture_checker(const t_vec3 point, t_vec3 color1, t_vec3 color2)
{
	float	sines;
	int		checker_size = 3;

	sines = sin(checker_size * point.x) * sin(checker_size * point.y) * sin(checker_size * point.z);
	if (sines < 0)
		return (color1);
	return (color2);
}

/*############################################### MATERIAL ###############################################*/

t_vec3	ray_reflected(const t_vec3 v, const t_vec3 n)
{
	t_vec3	dot;

	dot = vec3_mult_float(n, (vec3_dot(v, n) * 2));
	return (vec3_sub(v, dot));
}

int refract(const t_vec3 v, const t_vec3 n, float ni_over_nt, t_vec3 *refracted)
{
	t_vec3 uv = vec3_unit(v);
	float dt = vec3_dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);

	if (discriminant > 0)
	{
		*refracted = vec3_sub(vec3_mult_float(vec3_sub(uv, vec3_mult_float(n, dt)), ni_over_nt), 
							  vec3_mult_float(n, sqrt(discriminant)));
		return (1);
	}
	return (0);
}

float schlick_approx(float cosine, float ref_idx)
{
	float	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

int dielectric_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_object obj)
{
	t_vec3	outward_normal;
	t_vec3	refracted;
	t_vec3	reflected;
	float	ni_over_nt;
	float	reflect_prob;
	float	cosine;

	*attenuation = create_vec3(1.0, 1.0, 1.0);  // Glass is transparent
	reflected = ray_reflected(r_in.direction, rec.normal);
	if (vec3_dot(r_in.direction, rec.normal) > 0) 
	{
		outward_normal = vec3_mult_float(rec.normal, -1);
		ni_over_nt = obj.material_parameter;
		// cosine = sqrt(1 - ni_over_nt * ni_over_nt * (1 - vec3_dot(r_in.direction, rec.normal) * vec3_dot(r_in.direction, rec.normal)));
		cosine = obj.material_parameter * vec3_dot(r_in.direction, rec.normal) / vec3_len(r_in.direction);
	}
	else
	{
		outward_normal = rec.normal;
		ni_over_nt = 1.0 / obj.material_parameter;
		// cosine = -vec3_dot(r_in.direction, rec.normal);
		cosine = -vec3_dot(r_in.direction, rec.normal) / vec3_len(r_in.direction);
	}

	if (refract(r_in.direction, outward_normal, ni_over_nt, &refracted))
		reflect_prob = schlick_approx(cosine, obj.material_parameter);
	else
	{
		*scattered = create_ray(rec.hit_point, reflected);
		reflect_prob = 1.0;
	}

	if (drand48() < reflect_prob)
		*scattered = create_ray(rec.hit_point, reflected);
	else
		*scattered = create_ray(rec.hit_point, refracted);

	return (1);
}

int	lamberian_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_object obj)
{
	t_vec3	target;
	(void)r_in;

	target = vec3_add3(rec.hit_point, rec.normal, vec3_random_in_unit_object());
	*scattered = create_ray(rec.hit_point, vec3_sub(target, rec.hit_point));
	if (obj.use_texture)
		*attenuation = texture_checker(rec.hit_point, obj.color, create_vec3(0.12, 0.12, 0.12));
	else
		*attenuation = obj.color;
	return (1);
}

int	metal_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_object obj)
{
	t_vec3	reflected;
	t_vec3	ray_dir;

	reflected = ray_reflected(vec3_unit(r_in.direction), rec.normal);
	ray_dir = vec3_add(reflected, vec3_mult_float(vec3_random_in_unit_object(), obj.material_parameter));
	*scattered = create_ray(rec.hit_point, ray_dir);
	if (obj.use_texture)
		*attenuation = texture_checker(rec.hit_point, obj.color, create_vec3(0.12, 0.12, 0.12));
	else
		*attenuation = obj.color;
	if (vec3_dot(scattered->direction, rec.normal) > 0)
		return (1);
	return (0);
}

int	light_scatter_ray(const t_ray r_in, const t_hit_record rec, t_vec3 *attenuation, t_ray *scattered, t_hit_object obj)
{
	t_vec3	target;
	(void)r_in;

	target = vec3_add3(rec.hit_point, rec.normal, vec3_random_in_unit_object());
	*scattered = create_ray(rec.hit_point, vec3_sub(target, rec.hit_point));
	*attenuation = obj.color;
	return (1);
}

/*############################################### CAMERA ###############################################*/

t_cam	create_camera(t_vec3 origin, t_vec3 look_at)
{
	t_cam	cam;
	t_vec3	u, v, w;
	float	theta;
	float	half_height;
	float	half_width;
	t_vec3	up;

	up = create_vec3(0, 1, 0);
	theta = FOV * M_PI / 180.0;
	half_height = tan(theta / 2);
	half_width = ((float)WIDTH / (float)HEIGHT) * half_height;

	w = vec3_unit(vec3_sub(origin, look_at));
	u = vec3_unit(vec3_cross(up, w));
	v = vec3_cross(w, u);

	cam.origin = origin;
	cam.horizintal = vec3_mult_float(u, 2 * half_width);
	cam.vertical = vec3_mult_float(v, 2 * half_height);

	cam.lower_L = vec3_sub3(origin, vec3_div_float(cam.horizintal, 2), vec3_div_float(cam.vertical, 2));
	cam.lower_L = vec3_sub(cam.lower_L, w);

	return (cam);
}

/*############################################### HITABLE ###############################################*/

/********************* sphere **********************/

t_hit_object	*create_sphere(t_vec3 center, float radius)
{
	t_hit_object	*shpere = (t_hit_object *)malloc(sizeof(t_hit_object));

	shpere->id = SPHERE;

	shpere->center = center;
	shpere->radius = radius;

	shpere->plane[0] = create_nullvec();
	shpere->plane[1] = create_nullvec();
	shpere->plane[2] = create_nullvec();
	shpere->plane[3] = create_nullvec();
	return (shpere);
}

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

/********************* Plane **********************/

t_hit_object	*create_rectangle(t_vec3 x0, t_vec3 x1, t_vec3 y0, t_vec3 y1)
{
	t_hit_object	*res = (t_hit_object *)malloc(sizeof(t_hit_object));

	res->id = RECTANGLE;

	res->center = create_nullvec();
	res->radius = 0;

	res->plane[0] = x0;
	res->plane[1] = x1;
	res->plane[2] = y0;
	res->plane[3] = y1;
	return (res);
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
    hit_rec->normal = normal;
    return (1);
}



// int hit_rectangle(t_hit_object *obj, const t_ray r, t_hit_record *hit_rec)
// {
// 	t_vec3 normal = vec3_unit(vec3_cross(vec3_sub(obj->plane[1], obj->plane[0]), vec3_sub(obj->plane[3], obj->plane[0])));
// 	float denom = vec3_dot(normal, r.direction);
// 	float t;

// 	if (fabs(denom) < 1e-6)
// 		return (0);  // Ray is parallel to the plane

// 	t = vec3_dot(vec3_sub(obj->plane[0], r.origin), normal) / denom;
// 	if (t < MIN_T || t > MAX_T)
// 		return (0);  // Intersection is out of range

// 	// Compute intersection point
// 	t_vec3 hit_point = ray_point_at(r, t);
	
// 	// Define a local coordinate system for the rectangle
// 	t_vec3 u = vec3_unit(vec3_sub(obj->plane[1], obj->plane[0])); // X-axis
// 	t_vec3 v = vec3_unit(vec3_sub(obj->plane[3], obj->plane[0])); // Y-axis
	
// 	// Project hit point onto the rectangle's coordinate system
// 	t_vec3 local_hit = vec3_sub(hit_point, obj->plane[0]);
// 	float x_proj = vec3_dot(local_hit, u);
// 	float y_proj = vec3_dot(local_hit, v);
	
// 	// Compute rectangle width and height
// 	float width = vec3_len(vec3_sub(obj->plane[1], obj->plane[0]));
// 	float height = vec3_len(vec3_sub(obj->plane[3], obj->plane[0]));

// 	// Check if hit point is inside the rectangle bounds
// 	if (x_proj < 0 || x_proj > width || y_proj < 0 || y_proj > height)
// 		return (0);  // Outside the rectangle

// 	// Store hit information
// 	hit_rec->t = t;
// 	hit_rec->hit_point = hit_point;
// 	hit_rec->normal = normal;

// 	return (1);
// }



/********************* obj **********************/

void	scene_add_obj(t_list **world, t_hit_object *obj, t_vec3 color, int use_texture, float material_parameter, int material)
{
    if (!obj)
        return;

    obj->color = vec3_safe_mult_float(color, 1);
    obj->use_texture = use_texture;
    obj->material = material;
    obj->material_parameter = (material == METAL) ? fmin(material_parameter, 1.0) : material_parameter;

    obj->hit_record.t = -1;
    obj->hit_record.hit_point = create_vec3(0, 0, 0);
    obj->hit_record.normal = create_vec3(0, 0, 0);
    obj->hit_record.color = color;

    t_list *new_obj = ft_lstnew((void *)obj);
    if (!new_obj)
    {
        free(obj);
        return;
    }
    ft_lstadd_back(world, new_obj);
}

int	hit_obj(t_hit_object *obj, const t_ray r, t_hit_record *hit_rec)
{
	if (obj->id == SPHERE)
		return (hit_sphere(obj, r, hit_rec));
	else if (obj->id == RECTANGLE)
		return (hit_plane(obj, r, hit_rec));
	return (0);
}

void	delete_obj(void *obj)
{
	free(obj);
}

void	clear_sceen(t_list **world)
{
	if (world && *world)
	{
		ft_lstclear(world, &delete_obj);
		*world = NULL;
	}
}

t_hit_object	*make_obj(t_list *obj)
{
	if (obj)
		return ((t_hit_object *)obj->content);
	else
		return (NULL);
}















/****************************************************************************/








t_mat4	mat4_look_at(t_vec3 pos, t_vec3 target, t_vec3 up)
{
	t_mat4	mat;
	t_vec3	forward = vec3_normalize(vec3_sub(target, pos));
	t_vec3	right = vec3_normalize(vec3_cross(forward, up));
	t_vec3	new_up = vec3_cross(right, forward);

	mat.m[0][0] = right.x;    mat.m[0][1] = new_up.x;    mat.m[0][2] = -forward.x; mat.m[0][3] = 0;
	mat.m[1][0] = right.y;    mat.m[1][1] = new_up.y;    mat.m[1][2] = -forward.y; mat.m[1][3] = 0;
	mat.m[2][0] = right.z;    mat.m[2][1] = new_up.z;    mat.m[2][2] = -forward.z; mat.m[2][3] = 0;
	mat.m[3][0] = -vec3_dot(right, pos);
	mat.m[3][1] = -vec3_dot(new_up, pos);
	mat.m[3][2] = vec3_dot(forward, pos);  mat.m[3][3] = 1;
	return	(mat);
}

t_vec3	mat4_mult_vec3(t_mat4 mat, t_vec3 v)
{
	t_vec3 result;
	result.x = mat.m[0][0] * v.x + mat.m[1][0] * v.y + mat.m[2][0] * v.z + mat.m[3][0];
	result.y = mat.m[0][1] * v.x + mat.m[1][1] * v.y + mat.m[2][1] * v.z + mat.m[3][1];
	result.z = mat.m[0][2] * v.x + mat.m[1][2] * v.y + mat.m[2][2] * v.z + mat.m[3][2];
	float w = mat.m[0][3] * v.x + mat.m[1][3] * v.y + mat.m[2][3] * v.z + mat.m[3][3];
	
	if (w != 0.0)
	{
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}
	return	(result);
}

t_mat4	mat4_perspective(float fov, float aspect, float near, float far)
{
	t_mat4	mat;
	float	tan_half = tanf(fov * 0.5 * M_PI / 180.0);

	mat.m[0][0] = 1.0 / (aspect * tan_half);
	mat.m[1][1] = 1.0 / tan_half;
	mat.m[2][2] = -(far + near) / (far - near);
	mat.m[2][3] = -1.0;
	mat.m[3][2] = -(2.0 * far * near) / (far - near);
	mat.m[3][3] = 0.0;
	return	(mat);
}
