/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:34:41 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/22 10:50:03 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbr_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		if (n != -2147483648)
		{
			n *= -1;
			ft_nbr_len(n);
		}
		else
			return (12);
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	ft_fill_char(char *res, int n, int *counter)
{
	if (n > 9)
	{
		ft_fill_char(res, (n / 10), counter);
		ft_fill_char(res, (n % 10), counter);
	}
	else
	{
		res[*counter] = n + '0';
		(*counter)++;
	}
	res[*counter] = '\0';
}

static char	*ft_alloc_res(char *res, int *counter, int n)
{
	int	n_prim;

	n_prim = n;
	if (n == -214748364)
		res = (char *) malloc(sizeof(char) * 12);
	else if (n <= 0 && n != -214748364)
		res = (char *) malloc(sizeof(char) * (ft_nbr_len(n_prim) + 2));
	else
		res = (char *) malloc(sizeof(char) * ft_nbr_len(n_prim) + 1);
	if (res == NULL)
		return (NULL);
	else
	{
		if (n < 0)
		{
			res[0] = '-';
			n_prim *= -1;
			ft_fill_char(res, n_prim, counter);
		}
		else
			ft_fill_char(res, n_prim, counter);
		return (res);
	}
}

static char	*ft_display_neg(char *res, int n, int *counter)
{
	if (n == -2147483648)
	{
		res = ft_alloc_res(res, counter, -214748364);
		if (res == NULL)
			return (NULL);
		res[10] = '8';
		res[11] = '\0';
	}
	else
		res = ft_alloc_res(res, counter, n);
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		*counter;
	int		counter_value;

	res = NULL;
	if (n < 0)
	{
		counter_value = 1;
		counter = &counter_value;
		res = ft_display_neg(res, n, counter);
	}
	else
	{
		counter_value = 0;
		counter = &counter_value;
		res = ft_alloc_res(res, counter, n);
	}
	return (res);
}
