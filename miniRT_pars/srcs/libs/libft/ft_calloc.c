/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:09:40 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/16 13:49:44 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (nmemb > 2147483647 || size > 2147483647)
		return (NULL);
	res = (void *) malloc(nmemb * size);
	if (res == NULL)
		return (NULL);
	else
	{
		ft_bzero(res, size * nmemb);
		return (res);
	}
}
