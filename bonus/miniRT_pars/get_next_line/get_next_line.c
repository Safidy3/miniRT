/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:50:36 by jrakoton          #+#    #+#             */
/*   Updated: 2025/02/17 10:13:33 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_gnl(char *s)
{
	char	*res;
	int		counter;

	res = (char *)malloc(sizeof(char) * ft_strlen_gnl(s) + 1);
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

int	ft_check_ending(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	int			index_read;
	char		*str_buff;
	static char	*res = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str_buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str_buff)
		return (NULL);
	index_read = 1;
	while (!ft_check_ending(res) && index_read != 0)
	{
		index_read = read(fd, str_buff, BUFFER_SIZE);
		if (index_read < 0)
			return (free(str_buff), NULL);
		str_buff[index_read] = '\0';
		res = ft_strjoin_gnl(res, str_buff);
		if (res[0] == '\0')
			return (free(str_buff), free(res), res = NULL, NULL);
	}
	free(str_buff);
	str_buff = ft_get_first(res);
	res = ft_get_second(res);
	return (str_buff);
}
