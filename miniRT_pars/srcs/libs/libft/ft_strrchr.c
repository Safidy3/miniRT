/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:05:28 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/20 11:51:40 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			s_len;
	unsigned char	*res;

	s_len = ft_strlen(s);
	res = (unsigned char *) s;
	while (s_len + 1 > 0)
	{
		if (res[s_len] == (unsigned char)c)
			return ((char *)&res[s_len]);
		s_len--;
	}
	return (NULL);
}
