/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:21:33 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 02:05:54 by safandri         ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			c;
	unsigned char	*s1_prim;
	unsigned char	*s2_prim;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	s1_prim = (unsigned char *) s1;
	s2_prim = (unsigned char *) s2;
	c = 0;
	while ((s1[c] || s2[c]))
	{
		if (s1[c] != s2[c])
			return (s1_prim[c] - s2_prim[c]);
		c++;
	}
	return (0);
}

int	ft_strcmp3(const char *s1, const char *s2, const char *s3)
{
	size_t			c;
	size_t			len1;
	size_t			len2;
	size_t			len3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	c = 0;
	if (len1 != len2
		|| len1 != len3
		|| len2 != len3)
		return (1);
	while ((s1[c] || s2[c] || s3[c]))
	{
		if (s1[c] != s2[c]
			|| s1[c] != s3[c]
			|| s2[c] != s3[c])
			return (1);
		c++;
	}
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}
