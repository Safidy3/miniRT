/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:14:18 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/03 06:39:28 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_pars(t_scene *scene, int argc, char **argv)
{
	if (argc < 2 || argc > 3)
	{
		ft_putstr_err("Error\nInvalid number of argument.");
		exit(EXIT_FAILURE);
	}
	if (validate_scene_name(argv[1]))
	{
		ft_putstr_err("Error\nInvalid filename \n");
		exit(EXIT_FAILURE);
	}
	p_scene(argv[1], scene);
}
