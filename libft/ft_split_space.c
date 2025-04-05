/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 04:13:32 by safandri          #+#    #+#             */
/*   Updated: 2025/04/03 04:13:33 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arr_len(void **a)
{
	int	i;

	i = 0;
	while (a && a[i])
		i++;
	return (i);
}

int	get_word_count(const char *input)
{
	int			word_count;
	int			in_word;
	const char	*p;

	word_count = 0;
	in_word = 0;
	p = input;
	while (*p != '\0')
	{
		if (ft_isspace(*p))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			word_count++;
		}
		p++;
	}
	return (word_count);
}

void	copy_world(int length, const char *start,
			char **result, int *word_index)
{
	result[*word_index] = malloc(length + 1);
	strncpy(result[*word_index], start, length);
	result[*word_index][length] = '\0';
	*word_index = *word_index + 1;
}

void	create_array(char **result,
		const char *start, const char *p)
{
	int			word_index;
	int			in_word;

	word_index = 0;
	in_word = 0;
	while (*p != '\0')
	{
		if (ft_isspace(*p))
		{
			if (in_word)
			{
				copy_world(p - start, start, result, &word_index);
				in_word = 0;
			}
		}
		else if (!in_word)
		{
			start = p;
			in_word = 1;
		}
		p++;
	}
}

char	**ft_split_space(const char	*input)
{
	int			word_count;
	char		**result;
	const char	*start;
	const char	*p;

	word_count = 0;
	start = input;
	p = input;
	if (input == NULL)
		return (NULL);
	word_count = get_word_count(input);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[word_count] = NULL;
	create_array(result, start, p);
	return (result);
}
