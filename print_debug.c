
#include "miniRT.h"
# include <stdio.h>

void	print_obj(t_object *new_obj)
{
	if (new_obj->shape == SPHERE)
		ft_putstr("SPHERE\n");
	else if (new_obj->shape == PLANE)
		ft_putstr("PLANE\n");
	else if (new_obj->shape == CYLINDRE)
		ft_putstr("CYLINDRE\n");
	else if (new_obj->shape == POINT_LIGHT)
		ft_putstr("POINT_LIGHT\n");
	else if (new_obj->shape == AMBIENT_LIGHT)
		ft_putstr("AMBIENT_LIGHT\n");
	else if (new_obj->shape == CAMERA)
		ft_putstr("CAMERA\n");
	else
		ft_putstr("Unknown object type\n");
	print_vec3(new_obj->center, "center   ");
	print_vec3(new_obj->direction, "direction");
	print_vec3(new_obj->proprieties.color, "color    ");
	printf("brightness: %f\n", new_obj->proprieties.parameter);
	printf("radius    : %f\n", new_obj->radius);
	printf("height    : %f\n\n", new_obj->height);
}

void	printT(t_list *t)
{
	t_object	*obj;
	printf("size %d\n", ft_lstsize(t));
	while (t)
	{
		obj = (t_object *)(t->content);
		print_obj(obj);
		t = t->next;
	}
	printf("\n");
}

void	print_vec3(t_vec3 v, char *name)
{
	if (name)
		printf("%s : ", name);
	printf("%f, %f, %f\n", v.x, v.y, v.z);
}
