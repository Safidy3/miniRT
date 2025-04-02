/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:21:41 by jrakoton          #+#    #+#             */
/*   Updated: 2025/02/18 10:47:55 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H

# include "../libs/libft/libft.h"
# include "global.h"

int	validate_scene_name(char *scene);
int	is_valid_id(char **scene);

#endif