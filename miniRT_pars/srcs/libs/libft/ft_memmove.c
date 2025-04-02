/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:21:18 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/19 13:52:09 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy(char *dest_prim, char *src_prim, size_t n)
{
	int	counter;

	counter = 0;
	while (n > 0)
	{
		dest_prim[counter] = src_prim[counter];
		counter++;
		n--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_prim;
	char	*src_prim;
	int		counter;

	if (dest == ((void *) 0) && src == ((void *) 0))
		return ((void *) 0);
	dest_prim = (char *) dest;
	src_prim = (char *) src;
	if (dest <= src)
		ft_copy(dest_prim, src_prim, n);
	else
	{
		counter = n - 1;
		while (n > 0)
		{
			dest_prim[counter] = src_prim[counter];
			counter--;
			n--;
		}
	}
	return (dest);
}
