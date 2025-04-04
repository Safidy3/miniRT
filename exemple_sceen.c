
#include "miniRT.h"

void	add_cornell_box(t_list **world)
{
	t_proprieties white_lamb = create_proprieties(create_vec3(1, 1, 1), LAMBERTIAN, 0, 0);
	t_proprieties red_lamb = create_proprieties(create_vec3(1, 0, 0), LAMBERTIAN, 0, 0);
	t_proprieties green_lamb = create_proprieties(create_vec3(0, 1, 0), LAMBERTIAN, 0, 0);

	t_object *up = create_plane(
		create_vec3(0, 2, 0),
		create_vec3(0, -1, 0)
	);
	scene_add_obj(world, up, white_lamb);

	t_object *down = create_plane(
		create_vec3(0, -2, 0),
		create_vec3(0, 1, 0)
	);
	scene_add_obj(world, down, white_lamb);

	t_object *fw = create_plane(
		create_vec3(0, 0, -2),
		create_vec3(0, 0, 1)
	);
	scene_add_obj(world, fw, white_lamb);

	t_object *left = create_plane(
		create_vec3(-2, 0, 0),
		create_vec3(1, 0, 0)
	);
	scene_add_obj(world, left, red_lamb);

	t_object *right = create_plane(
		create_vec3(2, 0, 0),
		create_vec3(-1, 0, 0)
	);
	scene_add_obj(world, right, green_lamb);

	t_object *back = create_plane(
		create_vec3(0, 0, 2),
		create_vec3(0, 0, -1)
	);
	scene_add_obj(world, back, white_lamb);
}

void	add_sceen(t_data *data)
{
	t_proprieties green_lamb = create_proprieties(create_vec3(0, 1, 0), LAMBERTIAN, 0, 0);
	t_proprieties white_dielectric = create_proprieties(create_vec3(1, 1, 1), LAMBERTIAN, 0, 0);
	// t_proprieties Blue_metal = create_proprieties(create_vec3(0, 0, 1), METAL, 0, 0);
	t_proprieties purple = create_proprieties(create_vec3(0.490196078, 0, 1), LAMBERTIAN, 0, 0);

	t_object *shpere = create_sphere(create_vec3(1, 0, -1), 1.0);
	scene_add_obj(&data->world, shpere, white_dielectric);

	t_object *cylinder = create_cylinder(create_vec3(-0, 1, -1), create_vec3(0, 1, 0), 0.6, 1.5);
	scene_add_obj(&data->world, cylinder, purple);

	t_object *point_light = create_pl(create_vec3(-1, 0, -0.5), create_vec3(1, 1, 1), 1);
	scene_add_obj(&data->world, point_light, green_lamb);
	t_object *ambent_light = create_al(create_vec3(1, 1, 1), 0.2);
	scene_add_obj(&data->world, ambent_light, green_lamb);

	// t_proprieties p_white_light = create_proprieties(create_vec3(1, 1, 1), LIGHT, 0, 0);
	// t_object *shpere_light = create_sphere(create_vec3(-1, 0, -0.5), 1);
	// scene_add_obj(&data->world, shpere_light, p_white_light);

	add_cornell_box(&data->world);

	create_camera(data, create_vec3(0, 0, 1), create_vec3(0, 0, -1), 90);
	compute_camera_rays(data);
}

void	sceen1(t_data *data)
{
	t_proprieties green_lamb = create_proprieties(create_vec3(0, 1, 0), LAMBERTIAN, 0, 0);
	t_proprieties white_lamb = create_proprieties(create_vec3(1, 1, 1), LAMBERTIAN, 0, 0);

	t_object *point_light = create_pl(create_vec3(-1, 0, -0.5), create_vec3(1, 1, 1), 1);
	t_object *ambent_light = create_al(create_vec3(1, 1, 1), 0.2);
	t_object *plan = create_plane(create_vec3(0, 0, -2), create_vec3(0, 0, 1));

	scene_add_obj(&data->world, point_light, white_lamb);
	scene_add_obj(&data->world, ambent_light, green_lamb);
	scene_add_obj(&data->world, plan, white_lamb);

	create_camera(data, create_vec3(0, 0, 1), create_vec3(0, 0, -1), 90);
	compute_camera_rays(data);
}
