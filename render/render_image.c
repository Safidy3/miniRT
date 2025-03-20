/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:15:23 by safandri          #+#    #+#             */
/*   Updated: 2025/03/19 14:09:07 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	is_shadowed(t_data *data, t_vec3 hit_point, t_vec3 light_pos)
{
	float 		dist_first_sec;
	float 		dist_first_light;
	t_vec3		shadow_dir;
	t_ray		shadow_ray;
	t_object	*sec_hit_obj;
	
	shadow_dir = vec3_normalize(vec3_sub(light_pos, hit_point));
	shadow_ray = create_ray(hit_point, shadow_dir);
	sec_hit_obj = get_safe_hit_obj(shadow_ray, data->world);
	if (!sec_hit_obj) 
		return 0;
	dist_first_sec = vec3_len(vec3_sub(sec_hit_obj->hit_record.hit_point, hit_point));
	dist_first_light = vec3_len(vec3_sub(light_pos, hit_point));
	return (dist_first_sec < dist_first_light);
}

t_vec3 ray_casted_color(t_data *data, int x, int y)
{
	t_object	*first_hit_obj;
	t_object	*p_light;
	t_object	*a_light;
    t_vec3		result;
	float		n;
    
	first_hit_obj = get_safe_hit_obj(data->camera_rays[x][y], data->world);
    if (!first_hit_obj)
        return create_nullvec();
    p_light = get_light(data->world, POINT_LIGHT);
    a_light = get_light(data->world, AMBIENT_LIGHT);
    result = vec3_mult(first_hit_obj->proprieties.color, vec3_div_float(vec3_add(p_light->proprieties.color, a_light->proprieties.color), 2));
    if (is_shadowed(data, first_hit_obj->hit_record.hit_point, p_light->center))
        return vec3_mult_float(result, a_light->proprieties.material_parameter);
    n = fmax(a_light->proprieties.material_parameter, vec3_dot(first_hit_obj->hit_record.normal, vec3_normalize(vec3_sub(p_light->center, first_hit_obj->hit_record.hit_point))));
    return vec3_mult_float(result, n);
}

void	put_pixel_color(t_data *data)
{
	t_vec3	pix_col;
	int		x, y;

	compute_camera_rays(data);
	printf("rendering ...\n");
	for (x = 0; x < WIDTH; x++)
	{
		for (y = 0; y < HEIGHT; y++)
		{
			if (isVoid(x, y, data))
				continue;
			pix_col = ray_casted_color(data, x, y);
			my_mlx_pixel_put(data, x, y, pix_col);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	printf("Finished.\n");
}
