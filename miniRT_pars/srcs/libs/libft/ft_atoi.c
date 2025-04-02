/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:29:26 by jrakoton          #+#    #+#             */
/*   Updated: 2025/03/27 21:11:43 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	counter;
	int	sign;
	int	res;

	counter = 0;
	sign = 1;
	res = 0;
	while (nptr[counter] == 32 || (nptr[counter] >= 9 && nptr[counter] <= 13))
		counter++;
	if (nptr[counter] == 43 || nptr[counter] == 45)
	{
		if (nptr[counter] == 45)
		{
			sign *= -1;
		}
		counter++;
	}
	while (nptr[counter] >= '0' && nptr[counter] <= '9')
	{
		res = (res * 10) + ((nptr[counter] - 48));
		counter++;
	}
	return (sign * res);
}
