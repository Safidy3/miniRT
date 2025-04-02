/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:37:27 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/15 16:27:16 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_counter;
	size_t	dst_len;
	size_t	src_counter;

	if (!(dst || src))
		return (0);
	dst_counter = 0;
	while (dst_counter < size && dst[dst_counter])
	{
		dst_counter++;
	}
	dst_len = ft_strlen(dst);
	src_counter = 0;
	while (src[src_counter] && (src_counter + dst_counter + 1) < size)
	{
		dst[dst_len + src_counter] = src[src_counter];
		src_counter++;
	}
	if (dst_counter != size)
		dst[dst_len + src_counter] = '\0';
	return (dst_counter + ft_strlen(src));
}
