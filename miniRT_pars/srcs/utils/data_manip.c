/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:23:25 by jrakoton          #+#    #+#             */
/*   Updated: 2025/03/30 08:09:26 by jrakoton         ###   ########.fr       */
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
	char *str_part;

	sign = 1.0f;
	res_dec = 0.0f;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
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
		free(str_part);
		return ((res_int + (res_dec / 100)) * sign);
	}
	else
		return (res_int * sign);
}
