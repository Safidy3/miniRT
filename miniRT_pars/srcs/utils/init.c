/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:55:02 by jrakoton          #+#    #+#             */
/*   Updated: 2025/04/02 20:27:54 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	init_ambient(t_ambient *ambient)
{
	ambient->id = '\0';
	ambient->brightness = 0.0f;
	ambient->color.red = 0.0f;
	ambient->color.green = 0.0f;
	ambient->color.blue = 0.0f;
}

void	init_camera(t_camera *camera)
{
	camera->id = '\0';
	camera->center_coord.x = 0.0f;
	camera->center_coord.y = 0.0f;
	camera->center_coord.z = 0.0f;
	camera->vector_dir.x = 0.0f;
	camera->vector_dir.y = 0.0f;
	camera->vector_dir.z = 0.0f;
	camera->fov = 0.0f;
}

void	init_plane(t_plane *plane)
{
	plane->id[0] = 'p';
	plane->id[1] = 'l';
	plane->id[2] = '\0';
	plane->center_coord.x = 0.0f;
	plane->center_coord.y = 0.0f;
	plane->center_coord.z = 0.0f;
	plane->normal_vector.x = 0.0f;
	plane->normal_vector.y = 0.0f;
	plane->normal_vector.z = 0.0f;
	plane->color.red = 0.0f;
	plane->color.green = 0.0f;
	plane->color.blue = 0.0f;
}

void	init_sphere(t_sphere *sphere)
{
	sphere->id[0] = 's';
	sphere->id[1] = 'p';
	sphere->id[2] = '\0';
	sphere->center_coord.x = 0.0f;
	sphere->center_coord.y = 0.0f;
	sphere->center_coord.z = 0.0f;
	sphere->diameter = 0.0f;
	sphere->color.red = 0.0f;
	sphere->color.green = 0.0f;
	sphere->color.blue = 0.0f;
}

void	init_light(t_light *light)
{
	light->id = '\0';
	light->center_coord.x = 0.0f;
	light->center_coord.y = 0.0f;
	light->center_coord.z = 0.0f;
	light->brightness = 0.0f;
	light->color.red = 0.0f;
	light->color.green = 0.0f;
	light->color.blue = 0.0f;
}

void	init_cylinder(t_cylinder *cylinder)
{
	cylinder->id[0] = 'c';
	cylinder->id[1] = 'y';
	cylinder->id[2] = '\0';
	cylinder->center_coord.x = 0.0f;
	cylinder->center_coord.y = 0.0f;
	cylinder->center_coord.z = 0.0f;
	cylinder->normal_vector.x = 0.0f;
	cylinder->normal_vector.y = 0.0f;
	cylinder->normal_vector.z = 0.0f;
	cylinder->diameter = 0.0f;
	cylinder->height = 0.0f;
	cylinder->color.red = 0.0f;
	cylinder->color.green = 0.0f;
	cylinder->color.blue = 0.0f;
}

void	init_scene_elt(t_scene *scene)
{
	init_ambient(&scene->ambient);
	init_camera(&scene->camera);
	init_plane(&scene->plane);
	init_light(&scene->light);
	scene->plane_lst = NULL;
	scene->sphere_lst = NULL;
	scene->cylinder_lst = NULL;
}

void	p_scene(char *filename, t_scene *scene)
{
	int	fd;

	get_fd(filename, &fd, 1, scene);
	scene->scene_len = get_scene_len(fd);
	scene->scene_arr = (char **)malloc(sizeof(char *) * (scene->scene_len + 1));
	if (!(scene->scene_arr))
	{
		printf("Error\n");
		printf("Malloc error\n");
		exit(1);
	}
	get_fd(filename, &fd, 2, scene);
	get_scene(fd, scene);
	validate_scene(scene);
	init_scene_elt(scene);
	parse(scene);
}
