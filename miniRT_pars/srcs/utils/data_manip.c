/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:23:25 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 01:21:25 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	is_valid_float(char *str)
{
	if (*str && (*str == '+' || *str == '-'))
		str++;
	if (!str || !(*str) || !ft_isdigit(*str))
		return (0);
	while (*str && ft_isdigit(*str))
		str++;
	if (!(*str) || *str == '\n')
		return (1);
	if (*str && *str != '.')
		return (0);
	str++;
	if (!(*str))
		return (0);
	while (*str && ft_isdigit(*str))
	{
		str++;
	}
	if (!(*str))
		return (1);
	return (0);
}

// Array to float
float	ft_atof(char *str)
{
	float	res_int;
	float	res_dec;
	float	sign;
	char	*str_part;

	sign = 1.0f;
	res_dec = 0.0f;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	res_int = (float)ft_atoi(str);
	while (*str && ft_isdigit(*str))
		str++;
	if (*str == '.')
	{
		str++;
		str_part = ft_substr(str, 0, 2);
		res_dec = (float)ft_atoi(str_part);
		if (ft_strlen(str_part) < 2)
			res_dec *= 10;
		return (free(str_part), (res_int + (res_dec / 100)) * sign);
	}
	return (res_int * sign);
}

float	ft_atofl(int index, char **arr_obj, t_scene *scene)
{
	float	res_int;
	float	res_dec;
	char	*str_part;
	char	*str;

	str = arr_obj[index];
	if (!is_valid_float(str))
		free_pars_error(scene, arr_obj, "Element value format error \n");
	res_dec = 0.0f;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			free_pars_error(scene, arr_obj, "Diameter/radius/brightness can not be negative\n");
	res_int = (float)ft_atoi(str);
	while (*str && ft_isdigit(*str))
		str++;
	if (*str == '.')
	{
		str++;
		str_part = ft_substr(str, 0, 2);
		res_dec = (float)ft_atoi(str_part);
		if (ft_strlen(str_part) < 2)
			res_dec *= 10;
		return (free(str_part), (res_int + (res_dec / 100)));
	}
	return (res_int);
}

t_3dcoord	make_coord(int index, char **splitted_obj, int is_normal_vect, t_scene *scene)
{
	t_3dcoord	coord;
	char		**arr_coord;

	arr_coord = ft_split(splitted_obj[index], ',');
	if (!is_valid_float(arr_coord[0]) || !is_valid_float(arr_coord[1])
		|| !is_valid_float(arr_coord[2]))
		free_vec3_error(scene, arr_coord, splitted_obj, "Element value format error \n");
	coord.x = ft_atof(arr_coord[0]);
	coord.y = ft_atof(arr_coord[1]);
	coord.z = ft_atof(arr_coord[2]);
	free_2d_arr(arr_coord);
	if (is_normal_vect && (!is_in_range(coord.x, 'v') || !is_in_range(coord.y, 'v')
		|| !is_in_range(coord.z, 'v')))
		free_vec3_error(scene, arr_coord, splitted_obj, "Element value format error \n");
	return (coord);
}

t_rgb	make_rgb(int index, char **splitted_obj, t_scene *scene)
{
	t_rgb	color;
	char	**arr_coord;
	char	*str_coord;

	str_coord = splitted_obj[index];
	arr_coord = ft_split(str_coord, ',');
	if (!is_valid_float(arr_coord[0]) || !is_valid_float(arr_coord[1])
		|| !is_valid_float(arr_coord[2]))
		free_vec3_error(scene, arr_coord, splitted_obj, "Element value format error \n");
	color.red = ft_atof(arr_coord[0]);
	color.green = ft_atof(arr_coord[1]);
	color.blue = ft_atof(arr_coord[2]);
	free_2d_arr(arr_coord);
	if (!is_in_range(color.red, 'c') || !is_in_range(color.green, 'c')
		|| !is_in_range(color.blue, 'c'))
		free_vec3_error(scene, arr_coord, splitted_obj, "Element value format error \n");
	return (color);
}
