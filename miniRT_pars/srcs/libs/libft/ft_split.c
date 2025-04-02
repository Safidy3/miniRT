/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:08:13 by jrakoton          #+#    #+#             */
/*   Updated: 2024/03/22 12:06:52 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_counter(char const *s, char c)
{
	int		word_nbr;
	char	*s_prim;

	s_prim = (char *) s;
	word_nbr = 0;
	while (*s_prim)
	{
		if (*s_prim != c)
		{
			word_nbr++;
			while (*s_prim && *s_prim != c)
				s_prim++;
		}
		else
			s_prim++;
	}
	return (word_nbr);
}

static int	ft_char_counter(char const *s, char c)
{
	int	char_ptr;

	char_ptr = 0;
	while (*s != '\0' && *s != c)
	{
		s++;
		char_ptr++;
	}
	return (char_ptr);
}

static int	ft_free_memalloc_char(char **res, int	*res_counter)
{
	if (res[*res_counter] == NULL)
	{
		while (*res_counter > 1 && res[*res_counter - 1])
			free(res[--(*res_counter)]);
		free(res);
		return (1);
	}
	else
		return (0);
}

static void	ft_alloc_char(char **res, char const *s, char c, int *s_counter)
{
	int	res_char_c;
	int	res_counter;
	int	char_size;

	res_counter = 0;
	while (s[*s_counter] != '\0')
	{
		if (s[*s_counter] == c)
			(*s_counter)++;
		else
		{
			res_char_c = 0;
			char_size = (ft_char_counter((s + *s_counter), c));
			res[res_counter] = (char *) malloc(sizeof(char) * (char_size + 1));
			if (ft_free_memalloc_char(res, &res_counter) == 1)
				return ;
			while (res_char_c < char_size)
				res[res_counter][res_char_c++] = s[(*s_counter)++];
			res[res_counter][res_char_c] = '\0';
			res_counter++;
		}
	}
	res[res_counter] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		s_counter;

	res = (char **) malloc(sizeof(char *) * (ft_word_counter(s, c) + 1));
	if (res == NULL)
		return (NULL);
	s_counter = 0;
	ft_alloc_char(res, s, c, &s_counter);
	return (res);
}
