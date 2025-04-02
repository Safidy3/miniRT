/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:38:33 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/16 16:07:14 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	counter;

	if (!(*s))
		return ;
	counter = 0;
	while (s[counter] != '\0')
	{
		(*f)(counter, &s[counter]);
		counter++;
	}
}
