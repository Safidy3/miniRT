/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:23:11 by safandri          #+#    #+#             */
/*   Updated: 2025/03/29 09:45:02 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	scene_add_obj(t_list **world, t_object *obj, t_proprieties prts)
{
	t_list	*new_obj;

	if (!obj)
		return ;
	new_obj = ft_lstnew((void *)obj);
	obj->id = ft_lstsize(*world);
	obj->hit_record.t = -1;
	obj->hit_record.hit_point = create_vec3(0, 0, 0);
	obj->hit_record.normal = create_vec3(0, 0, 0);
	obj->hit_record.color = prts.color;
	if (obj->shape != POINT_LIGHT && obj->shape != AMBIENT_LIGHT
		&& obj->shape != CAMERA)
	{
		obj->proprieties.color = vec3_safe_mult_float(prts.color, 1);
		obj->proprieties.use_texture = prts.use_texture;
		obj->proprieties.material = prts.material;
		if (prts.material == METAL)
			obj->proprieties.parameter = fmin(prts.parameter, 1.0);
		else
			obj->proprieties.parameter = prts.parameter;
	}
	ft_lstadd_back(world, new_obj);
}

int	hit_obj(t_object *obj, const t_ray r, t_hit_record *hit_rec)
{
	if (obj->shape == SPHERE)
		return (hit_sphere(obj, r, hit_rec));
	else if (obj->shape == PLANE)
		return (hit_plane(obj, r, hit_rec));
	else if (obj->shape == CYLINDRE)
		return (hit_cylinder(obj, r, hit_rec));
	return (0);
}
