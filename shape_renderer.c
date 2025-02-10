/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_renderer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:52:43 by safandri          #+#    #+#             */
/*   Updated: 2025/02/10 09:15:47 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_cube(t_data *img, t_mat4 view, t_mat4 projection)
{
    t_vec3 projected[8];
	t_vec3 cube_vertices[] = {
		{-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1},
		{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}
	};

	int cube_edges[12][2] = {
		{0,1}, {1,2}, {2,3}, {3,0},
		{4,5}, {5,6}, {6,7}, {7,4},
		{0,4}, {1,5}, {2,6}, {3,7}
	};

    // Project all vertices
    for (int i = 0; i < 8; i++)
	{
        t_vec3 v = cube_vertices[i];
        v = mat4_mult_vec3(view, v);
        v = mat4_mult_vec3(projection, v);

        // Convert to screen coordinates
        v.x = (v.x + 1.0) * 0.5 * WIDTH;
        v.y = (1.0 - v.y) * 0.5 * HEIGHT;
        projected[i] = v;

        // printf("Vertex %d: Screen Position: (%.2f, %.2f)\n", i, v.x, v.y);
    }

    // Draw edges
    for (int i = 0; i < 12; i++)
	{
        t_vec3 p0 = projected[cube_edges[i][0]];
        t_vec3 p1 = projected[cube_edges[i][1]];
        draw_line(img, p0, p1, 0x00FF0000);
    }
}

void	render_triangle(t_data *img, t_mat4 view, t_mat4 projection)
{
    t_vec3 projected[3];
	t_vec3 triangle_vertices[] = {
		{0, 1, 5},  // Top vertex
		{-1, -1, 5}, // Bottom-left vertex
		{1, -1, 5}   // Bottom-right vertex
	};

    for (int i = 0; i < 3; i++)
	{
        t_vec3 v = triangle_vertices[i];
        v = mat4_mult_vec3(view, v);       // Apply view transformation
        v = mat4_mult_vec3(projection, v); // Apply projection transformation

        // Convert to screen coordinates
        v.x = (v.x + 1.0) * 0.5 * WIDTH;
        v.y = (1.0 - v.y) * 0.5 * HEIGHT;
        projected[i] = v;
    }

    // Draw triangle edges : Green
    draw_line(img, projected[0], projected[1], 0x00FF00);
    draw_line(img, projected[1], projected[2], 0x00FF00); 
    draw_line(img, projected[2], projected[0], 0x00FF00);
}