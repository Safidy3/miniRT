/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:02:28 by safandri          #+#    #+#             */
/*   Updated: 2024/02/28 14:51:52 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int num)
{
	if ((num >= 48 && num <= 57)
		|| (num >= 65 && num <= 90)
		|| (num >= 97 && num <= 122))
		return (8);
	return (0);
}

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}
