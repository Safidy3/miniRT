
#include "miniRT.h"

void	print_obj(t_object *new_obj)
{
	if (new_obj->shape == SPHERE)
		printf("SPHERE\n");
	else if (new_obj->shape == PLANE)
		printf("PLANE\n");
	else if (new_obj->shape == CYLINDRE)
		printf("CYLINDRE\n");
	else if (new_obj->shape == POINT_LIGHT)
		printf("POINT_LIGHT\n");
	else if (new_obj->shape == AMBIENT_LIGHT)
		printf("AMBIENT_LIGHT\n");
	else if (new_obj->shape == CAMERA)
		printf("Object type: CAMERA\n");
	else
		printf("Unknown object type\n");
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
		int iter_val = 	(int)obj->shape;
		switch (iter_val)
		{
			case CAMERA:
				printf("CAMERA : %d\n", (int)obj->id);
				break;
			case SPHERE:
				printf("SPHERE : %d\n", (int)obj->id);
				break;
			case PLANE:
				printf("PLANE : %d\n", (int)obj->id);
				break;
			case CYLINDRE:
				printf("CYLINDRE : %d\n", (int)obj->id);
				break;
			case POINT_LIGHT:
				printf("POINT_LIGHT : %d\n", (int)obj->id);
				break;
			case AMBIENT_LIGHT:
				printf("AMBIENT_LIGHT : %d\n", (int)obj->id);
				break;
			default:
				break;
		}
		print_vec3(obj->center, "center");
		print_vec3(obj->direction, "direction");
		print_vec3(obj->proprieties.color, "color");
		printf("radius : %f\n", obj->radius);
		printf("height : %f\n\n", obj->height);
		// printf("id : %d\n", iter_val);
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