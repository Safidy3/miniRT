/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:44:44 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/16 15:39:56 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len_s1;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len_s1 = ft_strlen(s1);
	while (len_s1 && ft_strchr(set, s1[len_s1]))
		len_s1--;
	return (ft_substr(s1, 0, len_s1 + 1));
}
