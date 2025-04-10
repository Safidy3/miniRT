/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:25:17 by safandri          #+#    #+#             */
/*   Updated: 2025/04/08 17:25:17 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_object	*create_al(t_vec3 color, float brightness)
{
	t_object		*pl;
	t_proprieties	prts;

	pl = (t_object *)malloc(sizeof(t_object));
	pl->shape = AMBIENT_LIGHT;
	pl->center = create_nullvec();
	pl->radius = 0;
	pl->direction = create_nullvec();
	pl->height = 0;
	prts.color = vec3_mult_float(color, brightness);
	prts.material = 0;
	prts.parameter = brightness;
	prts.use_texture = 0;
	pl->proprieties = prts;
	return (pl);
}
