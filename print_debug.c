
#include "miniRT.h"

void	printT(t_list *t)
{
	printf("size %d\n", ft_lstsize(t));
	while (t)
	{
		int iter_val = 	(int)((t_object *)(t->content))->shape;
		switch (iter_val)
		{
			case 0:
				printf("SPHERE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case 1:
				printf("RECTANGLE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case 2:
				printf("PLANE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case 3:
				printf("INF_CYLINDRE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case 4:
				printf("CYLINDRE : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case 5:
				printf("POINT_LIGHT : %d\n", (int)((t_object *)(t->content))->id);
				break;
			case 6:
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