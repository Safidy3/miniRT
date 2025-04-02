/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:09:47 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/20 11:56:44 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b_counter;
	size_t	l_counter;

	if (!(*little))
		return ((char *) big);
	if (!(*big))
		return (NULL);
	b_counter = 0;
	while (b_counter < len && big[b_counter])
	{
		l_counter = 0;
		while (little[l_counter] && b_counter + l_counter < len
			&& big[b_counter + l_counter] == little[l_counter])
			l_counter++;
		if (little[l_counter] == '\0')
			return ((char *)(big + b_counter));
		b_counter++;
	}
	return (NULL);
}
