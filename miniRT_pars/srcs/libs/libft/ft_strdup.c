/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:42:25 by jrakoton          #+#    #+#             */
/*   Updated: 2025/03/30 06:42:31 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	int		counter;

	res = (char *) malloc(sizeof(char) * ft_strlen(s) + 1);
	if (res == NULL)
		return (NULL);
	counter = 0;
	while (s[counter] != '\0')
	{
		res[counter] = s[counter];
		counter++;
	}
	res[counter] = '\0';
	return (res);
}
