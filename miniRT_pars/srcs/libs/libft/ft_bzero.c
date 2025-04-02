/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:20:55 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/13 10:31:52 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_smemset(void *s, int c, size_t n)
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

void	ft_bzero(void *s, size_t n)
{
	ft_smemset(s, '\0', n);
}
