/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elt_value_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:26:42 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/02 00:38:36 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	is_char_type_id(char c)
{
	return (c == 'A' || c == 'C' || c == 'L');
}

int	is_str_type_id(char *str)
{
	if (str[2])
		return (0);
	return ((str[0] == 's' && str[1] == 'p') || (str[0] == 'c' && str[1] == 'y')
		|| (str[0] == 'p' && str[1] == 'l'));
}

int	is_in_range(float nbr, char c)
{
	if (c == 'c')
		return (nbr >= 0.0f && nbr <= 255.0f);
	else if (c == 'v') // this is for normal vector
		return (nbr >= -1.0f && nbr <= 1.0f);
	else if (c == 'f')
		return (nbr >= 0.0f && nbr <= 180.0f);
	else
		return (nbr >= 0.0f && nbr <= 1.0f);
}

int	get_3dcoord(t_3dcoord *coord, char **arr_coord, int is_normal_vect)
{
	if (!is_valid_float(arr_coord[0]) || !is_valid_float(arr_coord[1])
		|| !is_valid_float(arr_coord[2]))
	{
		printf("Error\n");
		printf("Invalid float format value. \n");
		free_2d_arr(arr_coord);
		return (0);
	}
	coord->x = ft_atof(arr_coord[0]);
	coord->y = ft_atof(arr_coord[1]);
	coord->z = ft_atof(arr_coord[2]);
	free_2d_arr(arr_coord);
	if (is_normal_vect && (!is_in_range(coord->x, 'v') || !is_in_range(coord->y,
				'v') || !is_in_range(coord->z, 'v')))
	{
		printf("Error\n");
		printf("Normal vector should be in range of [-1,1].\n");
		return (0);
	}
	return (1);
}

void	get_rgb_color(t_rgb *color, char **arr_coord, t_scene *scene)
{
	if (!is_valid_float(arr_coord[0]) || !is_valid_float(arr_coord[1])
		|| !is_valid_float(arr_coord[2]))
		free_pars_error(scene, arr_coord, "Element value format error \n");
	color->red = ft_atof(arr_coord[0]);
	color->green = ft_atof(arr_coord[1]);
	color->blue = ft_atof(arr_coord[2]);
	free_2d_arr(arr_coord);
	if (!is_in_range(color->red, 'c') || !is_in_range(color->green, 'c')
		|| !is_in_range(color->blue, 'c'))
		free_pars_error(scene, NULL, "RGB color should be in range of [0, 255]");
}

void	check_arg_nbr(char **splitted_elt, int arg_number, t_scene *scene)
{
	if ((splitted_elt[arg_number] && splitted_elt[arg_number][0] != '\n')
		|| !splitted_elt[arg_number - 1] || splitted_elt[arg_number
		- 1][0] == 10)
		free_pars_error(scene, splitted_elt, "Element value format error \n");
}

void	check_dup_capital(char **scene)
{
	int					i;
	static t_3dcoord	capitals;

	i = 0;
	while (scene[i] && scene)
	{
		if (scene[i][0] == 'A')
			capitals.x += 1.0f;
		if (scene[i][0] == 'C')
			capitals.y += 1.0f;
		if (scene[i][0] == 'L')
			capitals.z += 1.0f;
		if (capitals.x > 1 || capitals.y > 1 || capitals.z > 1)
		{
			printf("Error\n");
			printf("Element with capital letter id should be only declared once. \n");
			free_2d_arr(scene);
			exit(1);
		}
		i++;
	}
}
