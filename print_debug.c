
#include "miniRT.h"

void	printT(t_list *t)
{
	printf("size %d\n", ft_lstsize(t));
	while (t)
	{
		int iter_val = 	(int)((t_object *)(t->content))->shape;
		switch (iter_val)
		{
			case SPHERE:
				printf("SPHERE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case RECTANGLE:
				printf("RECTANGLE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case PLANE:
				printf("PLANE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case CYLINDRE:
				printf("CYLINDRE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case POINT_LIGHT:
				printf("POINT_LIGHT : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case AMBIENT_LIGHT:
				printf("AMBIENT_LIGHT : %d\n", (int)((t_object *)(t->content))->id);
				break;
			default:
				break;
		}
		// printf("id : %d\n", iter_val);
		t = t->next;
	}
	printf("\n");
}

void	print_vec3(t_vec3 v, char *name)
{
	if (name)
		printf("%s -> ", name);
	printf("x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}