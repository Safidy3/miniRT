/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:20:21 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 04:21:13 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

void	print_cylinder(t_obj *cylinder)
{
	printf("\n");
	printf("shape	: %i \n", ((t_obj *)(cylinder))->shape);
	printf("Center	: %f %f %f\n", ((t_obj *)(cylinder))->center_coord.x,
		((t_obj *)(cylinder))->center_coord.y,
		((t_obj *)(cylinder))->center_coord.z);
	printf("Normal	: %f %f %f\n", ((t_obj *)(cylinder))->normal_vector.x,
		((t_obj *)(cylinder))->normal_vector.y,
		((t_obj *)(cylinder))->normal_vector.z);
	printf("height	: %f \n", ((t_obj *)(cylinder))->height);
	printf("diameter: %f \n", ((t_obj *)(cylinder))->diameter);
	printf("Color	: %f %f %f\n", ((t_obj *)(cylinder))->color.red,
		((t_obj *)(cylinder))->color.green,
		((t_obj *)(cylinder))->color.blue);
	printf("\n");
}
