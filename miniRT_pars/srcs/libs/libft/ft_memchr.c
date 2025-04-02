/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:06:53 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/20 11:45:46 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*s_prim;
	size_t	counter;

	s_prim = (char *) s;
	counter = 0;
	while (counter < n)
	{
		if ((unsigned char)s_prim[counter] == (unsigned char)c)
			return ((void *)(&s_prim[counter]));
		counter++;
	}
	return (NULL);
}
