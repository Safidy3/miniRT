/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:28:10 by safandri          #+#    #+#             */
/*   Updated: 2025/04/08 17:28:10 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_proprieties	create_proprieties(t_vec3 color,
	int material, float parameter, int use_texture)
{
	t_proprieties	prts;

	prts.color = color;
	prts.parameter = parameter;
	prts.material = material;
	prts.use_texture = use_texture;
	return (prts);
}

t_vec3	texture_checker(const t_vec3 point, t_vec3 color1, t_vec3 color2)
{
	float	sines;
	int		checker_size;

	checker_size = 3;
	sines = sin(checker_size * point.x)
		* sin(checker_size * point.y)
		* sin(checker_size * point.z);
	if (sines < 0)
		return (color1);
	return (color2);
}

t_vec3	ray_reflected(const t_vec3 v, const t_vec3 n)
{
	t_vec3	dot;

	dot = vec3_mult_float(n, (vec3_dot(v, n) * 2));
	return (vec3_sub(v, dot));
}

int	refract(const t_vec3 v, const t_vec3 n, float ni_over_nt, t_vec3 *refracted)
{
	t_vec3	uv;
	float	dt;
	float	discriminant;

	uv = vec3_unit(v);
	dt = vec3_dot(uv, n);
	discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0)
	{
		*refracted = vec3_sub(
				vec3_mult_float(vec3_sub(uv, vec3_mult_float(n, dt)),
					ni_over_nt),
				vec3_mult_float(n, sqrt(discriminant)));
		return (1);
	}
	return (0);
}

float	schlick_approx(float cosine, float ref_idx)
{
	float	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cosine), 5));
}
