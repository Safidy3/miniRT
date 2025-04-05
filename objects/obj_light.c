#include "../miniRT.h"

t_object	*create_pl(t_vec3 center, t_vec3 color, float brightness)
{
	t_object		*pl;
	t_proprieties	prts;

	pl = (t_object *)malloc(sizeof(t_object));
	pl->shape = POINT_LIGHT;
	pl->center = center;
	pl->radius = 0;
	pl->direction = create_nullvec();
	prts.color = vec3_mult_float(color, brightness);
	prts.material = 0;
	prts.parameter = brightness;
	prts.use_texture = 0;
	pl->proprieties = prts;
	return (pl);
}

t_object	*create_al(t_vec3 color, float brightness)
{
	t_object		*pl;
	t_proprieties	prts;

	pl = (t_object *)malloc(sizeof(t_object));
	pl->shape = AMBIENT_LIGHT;
	pl->center = create_nullvec();
	pl->radius = 0;
	pl->direction = create_nullvec();
	prts.color = vec3_mult_float(color, brightness);
	prts.material = 0;
	prts.parameter = brightness;
	prts.use_texture = 0;
	pl->proprieties = prts;
	return (pl);
}
