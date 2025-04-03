/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:57:21 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 04:13:17 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	counter;

	counter = 0;
	if (str)
	{
		while (str[counter] != '\0')
			counter++;
	}
	return (counter);
}

char	*ft_strjoin_gnl(char *str1, char *str2)
{
	char	*res;
	int		counter;

	if (!str1)
		return (ft_strdup_gnl(str2));
	res = (char *)malloc(sizeof(char) * (ft_strlen_gnl(str1)
				+ ft_strlen_gnl(str2) + 1));
	if (!res)
		return (NULL);
	counter = 0;
	while (str1[counter] != '\0')
	{
		res[counter] = str1[counter];
		counter++;
	}
	while (*str2)
	{
		res[counter] = *str2;
		counter++;
		str2++;
	}
	res[counter] = '\0';
	free(str1);
	return (res);
}

int	ft_get_index(char *str)
{
	int	ending_index;

	ending_index = 0;
	if (str)
	{
		while (str[ending_index] != '\n' && str[ending_index] != '\0')
			ending_index++;
		if (str[ending_index] == '\n')
			ending_index++;
	}
	return (ending_index);
}

char	*ft_get_first(char *str)
{
	char	*res;
	int		counter;

	counter = ft_get_index(str);
	res = (char *)malloc(sizeof(char) * (counter + 1));
	counter = 0;
	while (str[counter] != '\n' && str[counter] != '\0')
	{
		res[counter] = str[counter];
		counter++;
	}
	if (str[counter] == '\n')
	{
		res[counter] = '\n';
		res[counter + 1] = '\0';
	}
	else
		res[counter] = '\0';
	return (res);
}

char	*ft_get_second(char *str)
{
	int		counter;
	int		index;
	char	*res;

	if (!str)
		return (NULL);
	counter = ft_strlen_gnl(str) - ft_get_index(str) + 2;
	res = (char *)malloc(sizeof(char) * counter);
	if (!res)
		return (NULL);
	index = 0;
	counter = ft_get_index(str);
	while (str[counter])
	{
		res[index] = str[counter];
		index++;
		counter++;
	}
	res[index] = '\0';
	free(str);
	return (res);
}
