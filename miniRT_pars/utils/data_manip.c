/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:23:25 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/09 16:54:35 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

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
		free_pars_error(scene, arr_obj, E_FLOAT);
	res_dec = 0.0f;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			free_pars_error(scene, arr_obj, E_PARAM);
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

t_vec3	make_coord(int index, char **splitted_obj,
		int is_normal_vect, t_scene *scene)
{
	t_vec3	coord;
	char	**arr_coord;

	arr_coord = ft_split(splitted_obj[index], ',');
	if (!arr_coord || ft_arr_len((void **)arr_coord) != 3
		|| !is_valid_float(arr_coord[0])
		|| !is_valid_float(arr_coord[1])
		|| !is_valid_float(arr_coord[2]))
		free_vec3_error(scene, arr_coord, splitted_obj, E_ARG);
	coord.x = ft_atof(arr_coord[0]);
	coord.y = ft_atof(arr_coord[1]);
	coord.z = ft_atof(arr_coord[2]);
	if (is_normal_vect 
			&& (!check_normilized(coord)
			|| !is_in_range(coord.x, 'v')
			|| !is_in_range(coord.y, 'v')
			|| !is_in_range(coord.z, 'v')))
		free_vec3_error(scene, arr_coord, splitted_obj, E_NORM);
	free_2d_arr(arr_coord);
	return (coord);
}

t_vec3	make_rgb(int index, char **splitted_obj, t_scene *scene)
{
	t_vec3	color;
	char	**arr_coord;
	char	*str_coord;

	str_coord = splitted_obj[index];
	arr_coord = ft_split(str_coord, ',');
	if (!arr_coord || ft_arr_len((void **)arr_coord) != 3
		|| !is_valid_float(arr_coord[0])
		|| !is_valid_float(arr_coord[1])
		|| !is_valid_float(arr_coord[2]))
		free_vec3_error(scene, arr_coord, splitted_obj, E_ARG);
	color.x = ft_atof(arr_coord[0]);
	color.y = ft_atof(arr_coord[1]);
	color.z = ft_atof(arr_coord[2]);
	if (!is_in_range(color.x, 'c') || !is_in_range(color.y, 'c')
		|| !is_in_range(color.z, 'c'))
		free_vec3_error(scene, arr_coord, splitted_obj, E_COL);
	free_2d_arr(arr_coord);
	return (make_color(color));
}
