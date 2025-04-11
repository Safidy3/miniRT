/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elt_value_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:26:42 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/09 17:04:29 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_char_type_id(char c)
{
	return (c == 'A' || c == 'C' || c == 'L');
}

int	is_str_type_id(char *str)
{
	if (str[2])
		return (0);
	return ((str[0] == 's' && str[1] == 'p')
		|| (str[0] == 'c' && str[1] == 'y')
		|| (str[0] == 'p' && str[1] == 'l'));
}

int	is_in_range(float nbr, char c)
{
	if (c == 'c')
		return (nbr >= 0.0f && nbr <= 255.0f);
	else if (c == 'v')
		return (nbr >= -1.0f && nbr <= 1.0f);
	else if (c == 'f')
		return (nbr >= 0.0f && nbr <= 180.0f);
	else
		return (nbr >= 0.0f && nbr <= 1.0f);
}

void	check_arg_nbr(char **splitted_elt, int arg_number, t_scene *scene)
{
	if ((splitted_elt[arg_number] && splitted_elt[arg_number][0] != '\n')
		|| !splitted_elt[arg_number - 1]
		|| splitted_elt[arg_number - 1][0] == 10)
		free_pars_error(scene, splitted_elt, E_NUM_PARAM);
}

void	check_dup_capital(char **scene)
{
	int	i;
	int	c;
	int	a;
	int	l;

	i = 0;
	c = 0;
	a = 0;
	l = 0;
	while (scene[i] && scene)
	{
		if (scene[i][0] == 'A')
			a += 1;
		if (scene[i][0] == 'C')
			c += 1;
		if (scene[i][0] == 'L')
			l += 1;
		i++;
	}
	if (c != 1 || a != 1 || l == 0)
	{
		ft_putstr_err(E_OBJ_CAP);
		free_2d_arr(scene);
		exit(1);
	}
}
