/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:30:49 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/16 14:53:11 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*s_sub;
	unsigned int		s_sub_counter;

	if (len == 0 || start > (unsigned int) ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start <= len)
		len = ft_strlen(s) - start;
	s_sub = (char *) malloc(sizeof(char) * (len + 1));
	if (s_sub == NULL)
		return (NULL);
	s_sub_counter = 0;
	while (s[start] != '\0' && len > 0)
	{
		s_sub[s_sub_counter] = s[start];
		s_sub_counter++;
		start++;
		len--;
	}
	s_sub[s_sub_counter] = '\0';
	return (s_sub);
}
