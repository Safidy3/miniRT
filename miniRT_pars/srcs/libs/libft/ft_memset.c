/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:19:24 by jrakoton          #+#    #+#             */
/*   Updated: 2024/02/20 15:49:24 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	counter;
	char	*s_prim;

	s_prim = (char *) s;
	counter = 0;
	while (counter < n)
	{
		s_prim[counter] = c;
		counter++;
	}
	return (s);
}
