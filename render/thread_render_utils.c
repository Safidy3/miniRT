#include "../miniRT.h"

void	intit_thread_data(t_data *data, t_data *og_data)
{
	int	i;

	data->aa_sample = og_data->aa_sample;
	data->cam = dup_camera(og_data->cam);
	data->world = deep_copy_world(og_data->world);
	data->seleced_object = og_data->seleced_object;
	i = -1;
	data->camera_rays = (t_ray **)malloc(sizeof(t_ray *) * WIDTH);
	while (++i < WIDTH)
		data->camera_rays[i] = (t_ray *)malloc(sizeof(t_ray) * HEIGHT);
	data->hit_objects = (t_object ***)malloc(sizeof(t_object **) * WIDTH);
	i = -1;
	while (++i < WIDTH)
		data->hit_objects[i] = (t_object **)malloc(sizeof(t_object *) * HEIGHT);
}

void	get_cpu_thread_num(t_threads *thread, char *thread_num)
{
	FILE	*p;

	p = popen("awk '/^processor/{n+=1}END{print n}' /proc/cpuinfo", "r");
	fgets(thread_num, 10, p);
	pclose(p);
	thread->thread_num = ft_atoi(thread_num);
	thread->pix_unit = WIDTH / thread->thread_num;
}

void	get_scattered_attenuation(t_vec3 *attenuation, t_ray *scattered,
		t_object *first_hit, t_ray r)
{
	t_proprieties	prts;

	prts = first_hit->proprieties;
	if (prts.material == METAL)
		metal_scatter_ray(r, attenuation, scattered, first_hit);
	else if (prts.material == LAMBERTIAN)
		lamberian_scatter_ray(r, attenuation, scattered, first_hit);
	else if (prts.material == DIELECTRIC)
		dielectric_scatter_ray(r, attenuation, scattered, first_hit);
}

t_ray	get_antialiased_ray(int x, int y, t_data *data)
{
	t_vec3	pix_pos;
	t_ray	r;
	float	i;
	float	j;

	i = (float)(x + drand48()) / (float)WIDTH;
	j = (float)(HEIGHT - y + drand48()) / (float)HEIGHT;
	pix_pos = vec3_add3(data->cam.lower_l,
			vec3_mult_float(data->cam.horizintal, i),
			vec3_mult_float(data->cam.vertical, j));
	r = create_ray(data->cam.origin, vec3_sub(pix_pos, data->cam.origin));
	return (r);
}

t_vec3	compute_path_traced_color(t_data *data, int x, int y)
{
	t_vec3	pix_col;
	int		s;
	t_ray	r;

	pix_col = create_vec3(0, 0, 0);
	s = -1;
	if (is_void(x, y, data))
		return (create_nullvec());
	while (++s < data->aa_sample)
	{
		r = get_antialiased_ray(x, y, data);
		pix_col = vec3_add(pix_col, path_traced_color(r, data->world, 0, NULL));
	}
	pix_col = vec3_div_float(pix_col, data->aa_sample);
	pix_col = create_vec3(sqrt(pix_col.x), sqrt(pix_col.y), sqrt(pix_col.z));
	return (pix_col);
}
