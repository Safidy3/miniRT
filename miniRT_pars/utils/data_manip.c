/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:23:25 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 09:41:32 by safandri         ###   ########.fr       */
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

int	ft_atoint(int index, char **arr_obj, int data_type, t_scene *scene)
{
	float	res_int;

	res_int = ft_atoi(arr_obj[index]);
	if (data_type == METAL)
		if (res_int < 0 || res_int > 1)
			free_pars_error(scene, arr_obj, E_METAL);
	return (res_int);
}
