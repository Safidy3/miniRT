#include "../miniRT.h"

void	object_translation(int keycode, t_data *data)
{
	if (keycode == 119)
		translate_object(data, create_vec3(0, 0, -0.1));
	else if (keycode == 115)
		translate_object(data, create_vec3(0, 0, 0.1));
	else if (keycode == 97)
		translate_object(data, create_vec3(-0.1, 0, 0));
	else if (keycode == 100)
		translate_object(data, create_vec3(0.1, 0, 0));
	else if (keycode == 101)
		translate_object(data, create_vec3(0, 0.1, 0));
	else if (keycode == 113)
		translate_object(data, create_vec3(0, -0.1, 0));
}

void	object_rotation(int keycode, t_data *data)
{
	if (keycode == 105)
		rotate_z(data, 0.1);
	else if (keycode == 112)
		rotate_z(data, -0.1);
	else if (keycode == 111)
		rotate_x(data, 0.1);
	else if (keycode == 108)
		rotate_x(data, -0.1);
	else if (keycode == 107)
		rotate_y(data, 0.1);
	else if (keycode == 59)
		rotate_y(data, -0.1);
}
