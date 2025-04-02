/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:17:34 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/20 11:48:11 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ncmp(const char *s1, const char *s2, size_t n)
{
	size_t			c;
	unsigned char	*s1_prim;
	unsigned char	*s2_prim;

	s1_prim = (unsigned char *) s1;
	s2_prim = (unsigned char *) s2;
	c = 0;
	while (n > c)
	{
		if (s1[c] != s2[c])
			return (s1_prim[c] - s2_prim[c]);
		c++;
	}
	return (0);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*s1_prim;
	char	*s2_prim;

	s1_prim = (char *) s1;
	s2_prim = (char *) s2;
	return (ft_ncmp(s1_prim, s2_prim, n));
}
