#include "../miniRT.h"

void	create_camera(t_data *data, t_vec3 origin, t_vec3 look_at, float fov)
{
	t_vec3	w;

	w = vec3_unit(vec3_sub(origin, look_at));
	update_camera(data, origin, look_at, fov);
	scene_add_obj(&data->world, create_obj_cam(origin, w, fov),
		create_proprieties(create_nullvec(), 0, 0, 0));
}

void	update_camera(t_data *data, t_vec3 origin, t_vec3 direction, float fov)
{
	float	theta;
	float	half_height;
	float	half_width;
	t_vec3	up;

	up = create_vec3(0, 1, 0);
	theta = fov * M_PI / 180.0;
	half_height = tan(theta / 2);
	half_width = ((float)WIDTH / (float)HEIGHT) * half_height;
	data->cam.fov = fov;
	data->cam.origin = origin;
	data->cam.direction = direction;
	data->cam.w = vec3_unit(vec3_inverse(data->cam.direction));
	data->cam.u = vec3_unit(vec3_cross(up, data->cam.w));
	data->cam.v = vec3_cross(data->cam.w, data->cam.u);
	data->cam.horizintal = vec3_mult_float(data->cam.u, 2 * half_width);
	data->cam.vertical = vec3_mult_float(data->cam.v, 2 * half_height);
	data->cam.lower_l = vec3_sub3(origin,
			vec3_div_float(data->cam.horizintal, 2),
			vec3_div_float(data->cam.vertical, 2));
	data->cam.lower_l = vec3_sub(data->cam.lower_l, data->cam.w);
	compute_camera_rays(data);
}

t_cam	dup_camera(t_cam cam)
{
	t_cam	new_cam;

	new_cam.w = cam.w;
	new_cam.u = cam.u;
	new_cam.v = cam.v;
	new_cam.horizintal = cam.horizintal;
	new_cam.lower_l = cam.lower_l;
	new_cam.origin = cam.origin;
	new_cam.vertical = cam.vertical;
	return (new_cam);
}

t_object	*create_obj_cam(t_vec3 origin, t_vec3 direction, float fov)
{
	t_object	*cam;

	cam = (t_object *)malloc(sizeof(t_object));
	cam->shape = CAMERA;
	cam->center = origin;
	cam->radius = fov;
	cam->direction = direction;
	cam->plane[0] = create_nullvec();
	cam->plane[1] = create_nullvec();
	cam->plane[2] = create_nullvec();
	cam->plane[3] = create_nullvec();
	cam->proprieties.color = create_nullvec();
	cam->proprieties.material = 0;
	cam->proprieties.parameter = 0;
	cam->proprieties.use_texture = 0;
	return (cam);
}
