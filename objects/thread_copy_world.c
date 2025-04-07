#include "../miniRT.h"

t_object	*copy_obj(t_object *obj)
{
	t_object	*new_obj;

	new_obj = NULL;
	if (obj->shape == SPHERE)
		new_obj = create_sphere(obj->center, obj->radius * 2);
	else if (obj->shape == PLANE)
		new_obj = create_plane(obj->center, obj->direction);
	else if (obj->shape == CYLINDRE)
		new_obj = create_cylinder(obj->center,
				obj->direction, obj->radius * 2, obj->height);
	else if (obj->shape == AMBIENT_LIGHT)
		new_obj = create_al(obj->proprieties.color, obj->proprieties.parameter);
	else if (obj->shape == CAMERA)
		new_obj = create_obj_cam(obj->center, obj->direction, obj->radius);
	return (new_obj);
}

void	copy_hit_rec(t_object *new_obj, t_object *obj)
{
	new_obj->hit_record.t = -1;
	new_obj->hit_record.hit_point = create_vec3(0, 0, 0);
	new_obj->hit_record.normal = create_vec3(0, 0, 0);
	new_obj->hit_record.color = obj->proprieties.color;
	if (new_obj->shape != POINT_LIGHT && new_obj->shape != AMBIENT_LIGHT)
	{
		new_obj->proprieties.color = vec3_safe_mult_float(
				obj->proprieties.color, 1);
		new_obj->proprieties.use_texture = obj->proprieties.use_texture;
		new_obj->proprieties.material = obj->proprieties.material;
		if (obj->proprieties.material == METAL)
			new_obj->proprieties.parameter = fmin(
					obj->proprieties.parameter, 1.0);
		else
			new_obj->proprieties.parameter = obj->proprieties.parameter;
	}
}

t_list	*deep_copy_world(t_list *world)
{
	t_list		*new_world;
	t_object	*obj;
	t_object	*new_obj;

	new_world = NULL;
	while (world)
	{
		obj = make_obj(world);
		new_obj = copy_obj(obj);
		copy_hit_rec(new_obj, obj);
		new_obj->id = ft_lstsize(world);
		ft_lstadd_back(&new_world, ft_lstnew((void *)new_obj));
		world = world->next;
	}
	return (new_world);
}
