
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
	t_proprieties white_dielectric = create_proprieties(create_vec3(0, 0, 1), METAL, 0, 0);
	// t_proprieties Blue_metal = create_proprieties(create_vec3(0, 0, 1), METAL, 0, 0);
	t_proprieties purple = create_proprieties(create_vec3(0.490196078, 0, 1), METAL, 1, 0);

	t_object *shpere = create_sphere(create_vec3(1, 0, -1), 1.0);
	scene_add_obj(&data->world, shpere, white_dielectric);

	t_object *cylinder = create_cylinder(create_vec3(-0, 1, -1), create_vec3(0, 1, 0), 0.6, 1.5);
	scene_add_obj(&data->world, cylinder, purple);

	t_object *point_light = create_pl(create_vec3(-1, 0, -0.5), create_vec3(1, 1, 1), 1);
	scene_add_obj(&data->world, point_light, green_lamb);
	t_object *ambent_light = create_al(create_vec3(1, 1, 1), 0);
	scene_add_obj(&data->world, ambent_light, green_lamb);

	t_proprieties p_white_light = create_proprieties(create_vec3(1, 1, 1), LIGHT, 0, 0);
	t_object *shpere_light = create_sphere(create_vec3(-1, 0, -0.5), 1);
	scene_add_obj(&data->world, shpere_light, p_white_light);

	add_cornell_box(&data->world);

	create_camera(data, create_vec3(0, 0, 1), create_vec3(0, 0, -1), 90);
	compute_camera_rays(data);
}

void	bonus_sceen7(t_data *data)
{

	float	side = 5;
	float	ud = 4;
	float	height = 6;
	float	radius = 3;
	float	dept1 = -3.5;
	float	dept2 = -7;

	// t_proprieties purple = create_proprieties(create_vec3(0.490196078, 0, 1), LAMBERTIAN, 0, 0);
	t_proprieties green_lamb = create_proprieties(create_vec3(0, 1, 0), LAMBERTIAN, 0, 0);
	t_proprieties white_lamb = create_proprieties(create_vec3(0.329411765, 0.329411765, 0.329411765), LAMBERTIAN, 0, 0);
	t_proprieties white_metal = create_proprieties(create_vec3(1, 1, 1), METAL, 0.5, 0);
	t_proprieties Blue_lamb = create_proprieties(create_vec3(0, 0, 1), METAL, 0, 0);

	t_object *shpere = create_sphere(create_vec3(0, -2, -4), 2.0);
	scene_add_obj(&data->world, shpere, Blue_lamb);

	t_object *shpere1 = create_sphere(create_vec3(-side, ud, dept1), radius);
	scene_add_obj(&data->world, shpere1, white_metal);
	t_object *shpere2 = create_sphere(create_vec3(side, ud, dept1), radius);
	scene_add_obj(&data->world, shpere2, white_metal);
	t_object *shpere3 = create_sphere(create_vec3(-side, ud, dept2), radius);
	scene_add_obj(&data->world, shpere3, white_metal);
	t_object *shpere4 = create_sphere(create_vec3(side, ud, dept2), radius);
	scene_add_obj(&data->world, shpere4, white_metal);

	t_object *shpere5 = create_sphere(create_vec3(-side, -ud, dept1), radius);
	scene_add_obj(&data->world, shpere5, white_metal);
	t_object *shpere6 = create_sphere(create_vec3(side, -ud, dept1), radius);
	scene_add_obj(&data->world, shpere6, white_metal);
	t_object *shpere7 = create_sphere(create_vec3(-side, -ud, dept2), radius);
	scene_add_obj(&data->world, shpere7, white_metal);
	t_object *shpere8 = create_sphere(create_vec3(side, -ud, dept2), radius);
	scene_add_obj(&data->world, shpere8, white_metal);

	t_object *cylinder1 = create_cylinder(create_vec3(-side, 0, dept1), create_vec3(0, 1, 0), radius / 2, height);
	scene_add_obj(&data->world, cylinder1, white_metal);
	t_object *cylinder2 = create_cylinder(create_vec3(side, 0, dept1), create_vec3(0, 1, 0), radius / 2, height);
	scene_add_obj(&data->world, cylinder2, white_metal);
	t_object *cylinder3 = create_cylinder(create_vec3(-side, 0, dept2), create_vec3(0, 1, 0), radius / 2, height);
	scene_add_obj(&data->world, cylinder3, white_metal);
	t_object *cylinder4 = create_cylinder(create_vec3(side, 0, dept2), create_vec3(0, 1, 0), radius / 2, height);
	scene_add_obj(&data->world, cylinder4, white_metal);

	t_object *up = create_plane(create_vec3(0, 3.5, 0), create_vec3(0, -1, 0));
	t_object *down = create_plane(create_vec3(0, -3.5, 0), create_vec3(0, 1, 0));
	t_object *forward = create_plane(create_vec3(0, 0, -10), create_vec3(0, 0, -1));
	t_object *back = create_plane(create_vec3(0, 0, 5), create_vec3(0, 0, -1));
	scene_add_obj(&data->world, back, white_lamb);
	scene_add_obj(&data->world, forward, green_lamb);
	scene_add_obj(&data->world, up, white_lamb);
	scene_add_obj(&data->world, down, white_lamb);

	t_proprieties p_pint_light = create_proprieties(create_vec3(1, 0, 1), LIGHT, 0, 0);
	t_proprieties p_blue_light = create_proprieties(create_vec3(0, 0.784313725, 1), LIGHT, 0, 0);
	t_object *shpere_light = create_sphere(create_vec3(-side, 0, 3), 3);
	t_object *shpere_light2 = create_sphere(create_vec3(side, 0, 3), 3);
	scene_add_obj(&data->world, shpere_light, p_pint_light);
	scene_add_obj(&data->world, shpere_light2, p_blue_light);

	t_object *point_light = create_pl(create_vec3(0, 0, 0), create_vec3(1, 1, 1), 1);
	scene_add_obj(&data->world, point_light, white_lamb);
	t_object *ambent_light = create_al(create_vec3(1, 1, 1), 0.2);
	scene_add_obj(&data->world, ambent_light, white_lamb);

	create_camera(data, create_vec3(0, 0, 1), create_vec3(0, 0, -1), 90);
	compute_camera_rays(data);
}
