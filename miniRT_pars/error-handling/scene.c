/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:55:06 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 05:56:59 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	validate_scene_name(char *scene)
{
	int	scene_len;

	scene_len = ft_strlen(scene);
	return (scene[scene_len - 1] != 't' || scene[scene_len - 2] != 'r'
		|| scene[scene_len - 3] != '.');
}

int	is_valid_id(char **scene)
{
	while (scene)
	{
		if ((*scene)[1] == 32 && is_char_type_id((*scene)[0]))
		{
			scene++;
			continue ;
		}
		else if ((*scene)[2] == 32 && is_str_type_id(ft_substr(*scene, 0, 2)))
		{
			scene++;
			continue ;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}
