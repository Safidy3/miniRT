/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:41:41 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/16 15:24:02 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*res;

	res = (char *) s;
	while (*res)
	{
		if (*res == (char) c)
			return (res);
		res++;
	}
	if (*res == (char) c)
		return (res);
	return (NULL);
}
