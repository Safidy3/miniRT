/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:21:33 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/19 11:30:53 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			c;
	unsigned char	*s1_prim;
	unsigned char	*s2_prim;

	s1_prim = (unsigned char *) s1;
	s2_prim = (unsigned char *) s2;
	c = 0;
	while ((s1[c] || s2[c]) && n > c)
	{
		if (s1[c] != s2[c])
			return (s1_prim[c] - s2_prim[c]);
		c++;
	}
	return (0);
}
