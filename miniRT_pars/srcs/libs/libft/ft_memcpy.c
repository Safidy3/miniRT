/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:00:32 by jrakoton          #+#    #+#             */
/*   Updated: 2024/02/21 14:10:08 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_prim;
	const char	*src_prim;

	dest_prim = (char *) dest;
	src_prim = (const char *) src;
	if (dest == NULL && src == NULL)
		return (dest);
	while (n)
	{
		*(dest_prim++) = *(src_prim++);
		n--;
	}
	return (dest);
}
