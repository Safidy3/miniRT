/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:20:21 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/01 01:41:57 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	print_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i][0] != '\n')
			printf("=%s \n", arr[i]);
		i++;
	}
}

void	print_sphere(t_sphere *sphere)
{
	printf("\n");
	printf("id	: %c \n", ((t_sphere *)(sphere))->id[0]);
	printf("id str	: %s \n", ((t_sphere *)(sphere))->id);
	printf("Center	: %f %f %f\n", ((t_sphere *)(sphere))->center_coord.x, ((t_sphere *)(sphere))->center_coord.y, ((t_sphere *)(sphere))->center_coord.z);
	printf("diameter: %f \n", ((t_sphere *)(sphere))->diameter);
	printf("Color	: %f %f %f\n", ((t_sphere *)(sphere))->color.red, ((t_sphere *)(sphere))->color.green, ((t_sphere *)(sphere))->color.blue);
	printf("\n");
}

void	print_cylinder(t_cylinder *cylinder)
{
	printf("\n");
	printf("id	: %c \n", ((t_cylinder *)(cylinder))->id[0]);
	printf("id str	: %s \n", ((t_cylinder *)(cylinder))->id);
	printf("Center	: %f %f %f\n", ((t_cylinder *)(cylinder))->center_coord.x, ((t_cylinder *)(cylinder))->center_coord.y, ((t_cylinder *)(cylinder))->center_coord.z);
	printf("Normal	: %f %f %f\n", ((t_cylinder *)(cylinder))->normal_vector.x, ((t_cylinder *)(cylinder))->normal_vector.y, ((t_cylinder *)(cylinder))->normal_vector.z);
	printf("height	: %f \n", ((t_cylinder *)(cylinder))->height);
	printf("diameter: %f \n", ((t_cylinder *)(cylinder))->diameter);
	printf("Color	: %f %f %f\n", ((t_cylinder *)(cylinder))->color.red, ((t_cylinder *)(cylinder))->color.green, ((t_cylinder *)(cylinder))->color.blue);
	printf("\n");
}

void	print_plane(t_plane *plane)
{
	printf("\n");
	printf("id	: %c \n", ((t_plane *)(plane))->id[0]);
	printf("id str	: %s \n", ((t_plane *)(plane))->id);
	printf("Center	: %f %f %f\n", ((t_plane *)(plane))->pt_coord.x, ((t_plane *)(plane))->pt_coord.y, ((t_plane *)(plane))->pt_coord.z);
	printf("Normal	: %f %f %f\n", ((t_plane *)(plane))->normal_vector.x, ((t_plane *)(plane))->normal_vector.y, ((t_plane *)(plane))->normal_vector.z);
	printf("Color 	: %f %f %f\n", ((t_plane *)(plane))->color.red, ((t_plane *)(plane))->color.green, ((t_plane *)(plane))->color.blue);
	printf("\n");
}
