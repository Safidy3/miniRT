/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:33:41 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/17 12:00:44 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	counter;

	if (!(*s))
		return (ft_strdup(""));
	counter = 0;
	res = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (res == NULL)
		return (NULL);
	while (counter < (unsigned int) ft_strlen(s))
	{
		res[counter] = (*f)(counter, s[counter]);
		counter++;
	}
	res[counter] = '\0';
	return (res);
}
