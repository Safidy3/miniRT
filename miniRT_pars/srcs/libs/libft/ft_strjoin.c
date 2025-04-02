/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:18:12 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/20 12:09:52 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(char const *s1, char const *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (-1);
	else if (s1 != NULL && s2 != NULL)
	{
		if (ft_strlen(s1) == 0 && ft_strlen(s2) == 0)
			return (1);
		else
			return (ft_strlen(s1) + ft_strlen(s2));
	}
	else if (s1 == NULL && s2 != NULL)
		return (ft_strlen(s2));
	else
		return (ft_strlen(s1));
}

static char	*ft_copy_str_tilln(char *dest, char const *src, unsigned int *start)
{
	unsigned int	counter;

	counter = 0;
	while (src[counter] != '\0')
	{
		dest[*start] = src[counter];
		(*start)++;
		counter++;
	}
	return (dest);
}

static char	*ft_alloc_res(int size)
{
	char	*res;

	if (size == 1)
		res = (char *) malloc(sizeof(char) * size);
	else
		res = (char *) malloc(sizeof(char) * (size + 1));
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*s1_s2_comb;
	unsigned int	counter;
	int				size;

	size = ft_get_size(s1, s2);
	if (size == -1)
		return (NULL);
	else
	{
		s1_s2_comb = ft_alloc_res(size);
		if (s1_s2_comb == NULL)
			return (NULL);
		else
		{
			counter = 0;
			if (s1 != NULL)
				ft_copy_str_tilln(s1_s2_comb, s1, &counter);
			if (s2 != NULL)
				ft_copy_str_tilln(s1_s2_comb, s2, &counter);
			s1_s2_comb[counter] = '\0';
			return (s1_s2_comb);
		}
	}
}
