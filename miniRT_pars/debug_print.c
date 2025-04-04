/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:20:21 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 09:42:37 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s \n", arr[i]);
		i++;
	}
}

void	print_obj_list(t_scene *scene)
{
	t_list	*tmp;

	tmp = scene->obj_lst;
	while (tmp)
	{
		print_cylinder((tmp->content));
		tmp = tmp->next;
	}
}

void	print_cylinder(t_obj *cylinder)
{
	printf("\n");
	if (cylinder->shape == SPHERE)
		printf("Sphere	: SPHERE\n");
	else if (cylinder->shape == PLANE)
		printf("Plane	: PLANE\n");
	else if (cylinder->shape == CYLINDRE)
		printf("Cylinder: CYLINDRE\n");
	else if (cylinder->shape == POINT_LIGHT)
		printf("Light	: POINT_LIGHT\n");
	else if (cylinder->shape == AMBIENT_LIGHT)
		printf("Ambient : AMBIENT_LIGHT\n");
	else if (cylinder->shape == CAMERA)
		printf("Camera	: CAMERA\n");
	printf("Center	: %f %f %f\n", cylinder->center.x,
		cylinder->center.y,
		cylinder->center.z);
	printf("Normal	: %f %f %f\n", cylinder->normal_vector.x,
		cylinder->normal_vector.y,
		cylinder->normal_vector.z);
	printf("height	: %f \n", cylinder->height);
	printf("diameter: %f \n", cylinder->diameter);
	printf("Color	: %f %f %f\n", cylinder->color.x,
		cylinder->color.y,
		cylinder->color.z);
	printf("\n");
}
