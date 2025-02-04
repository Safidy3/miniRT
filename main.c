/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:42:07 by safandri          #+#    #+#             */
/*   Updated: 2025/01/28 15:58:50 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "stdio.h"
#include "unistd.h"
#include <stdlib.h>
#include <math.h>

#define WIDTH 960
#define HEIGHT 720
#define FOV 60
#define NEAR 0.1
#define FAR 100.0
#define M_PI 3.14159265358979323846

typedef struct s_vec3 {
	float x;
	float y;
	float z;
} t_vec3;

typedef struct s_mat4 {
	float m[4][4];
} t_mat4;

typedef struct s_camera {
	t_vec3 pos;
	t_vec3 target;
	t_vec3 up;
} t_camera;

typedef struct s_data {
	void    *mlx;               // Pointer to the MLX instance
	void    *win;               // Pointer to the window instance
	void    *img;               // Pointer to the image
	char    *addr;              // Address of the image data
	int     bits_per_pixel;     // Bits per pixel (color depth)
	int     line_length;        // Length of a line in bytes
	int     endian;             // Endianess of the pixel data
} t_data;


// Vector operations
t_vec3 vec3_sub(t_vec3 a, t_vec3 b) {
	return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

float vec3_dot(t_vec3 a, t_vec3 b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b) {
	return (t_vec3){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

t_vec3 vec3_normalize(t_vec3 v) {
	float len = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
	return (t_vec3){v.x/len, v.y/len, v.z/len};
}

// Matrix operations
t_mat4 mat4_look_at(t_vec3 pos, t_vec3 target, t_vec3 up) {
	t_mat4 mat;
	t_vec3 forward = vec3_normalize(vec3_sub(target, pos));
	t_vec3 right = vec3_normalize(vec3_cross(forward, up));
	t_vec3 new_up = vec3_cross(right, forward);

	mat.m[0][0] = right.x;    mat.m[0][1] = new_up.x;    mat.m[0][2] = -forward.x; mat.m[0][3] = 0;
	mat.m[1][0] = right.y;    mat.m[1][1] = new_up.y;    mat.m[1][2] = -forward.y; mat.m[1][3] = 0;
	mat.m[2][0] = right.z;    mat.m[2][1] = new_up.z;    mat.m[2][2] = -forward.z; mat.m[2][3] = 0;
	mat.m[3][0] = -vec3_dot(right, pos);
	mat.m[3][1] = -vec3_dot(new_up, pos);
	mat.m[3][2] = vec3_dot(forward, pos);  mat.m[3][3] = 1;
	return mat;
}

t_mat4 mat4_perspective(float fov, float aspect, float near, float far) {
	t_mat4 mat;
	float tan_half = tanf(fov * 0.5 * M_PI / 180.0);

	mat.m[0][0] = 1.0 / (aspect * tan_half);
	mat.m[1][1] = 1.0 / tan_half;
	mat.m[2][2] = -(far + near) / (far - near);
	mat.m[2][3] = -1.0;
	mat.m[3][2] = -(2.0 * far * near) / (far - near);
	mat.m[3][3] = 0.0;
	return mat;
}

t_vec3 mat4_mult_vec3(t_mat4 mat, t_vec3 v) {
	t_vec3 result;
	result.x = mat.m[0][0] * v.x + mat.m[1][0] * v.y + mat.m[2][0] * v.z + mat.m[3][0];
	result.y = mat.m[0][1] * v.x + mat.m[1][1] * v.y + mat.m[2][1] * v.z + mat.m[3][1];
	result.z = mat.m[0][2] * v.x + mat.m[1][2] * v.y + mat.m[2][2] * v.z + mat.m[3][2];
	float w = mat.m[0][3] * v.x + mat.m[1][3] * v.y + mat.m[2][3] * v.z + mat.m[3][3];
	
	if (w != 0.0) {
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}
	return result;
}

// Cube definition
t_vec3 cube_vertices[] = {
	{-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1},
	{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}
};

int cube_edges[12][2] = {
	{0,1}, {1,2}, {2,3}, {3,0},
	{4,5}, {5,6}, {6,7}, {7,4},
	{0,4}, {1,5}, {2,6}, {3,7}
};

void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
		char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void draw_line(t_data *img, t_vec3 p0, t_vec3 p1, int color) {
	int dx = abs((int)p1.x - (int)p0.x);
	int dy = abs((int)p1.y - (int)p0.y);
	int sx = p0.x < p1.x ? 1 : -1;
	int sy = p0.y < p1.y ? 1 : -1;
	int err = dx - dy;

	while (1) {
		my_mlx_pixel_put(img, (int)p0.x, (int)p0.y, color);
		if ((int)p0.x == (int)p1.x && (int)p0.y == (int)p1.y) break;
		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; p0.x += sx; }
		if (e2 < dx) { err += dx; p0.y += sy; }
	}
}

void render_cube(t_data *img, t_mat4 view, t_mat4 projection) {
    t_vec3 projected[8];

    // Project all vertices
    for (int i = 0; i < 8; i++) {
        t_vec3 v = cube_vertices[i];
        v = mat4_mult_vec3(view, v);
        v = mat4_mult_vec3(projection, v);

        // Convert to screen coordinates
        v.x = (v.x + 1.0) * 0.5 * WIDTH;
        v.y = (1.0 - v.y) * 0.5 * HEIGHT;
        projected[i] = v;

        // Debugging
        printf("Vertex %d: Screen Position: (%.2f, %.2f)\n", i, v.x, v.y);
    }

    // Draw edges
    for (int i = 0; i < 12; i++) {
        t_vec3 p0 = projected[cube_edges[i][0]];
        t_vec3 p1 = projected[cube_edges[i][1]];
        draw_line(img, p0, p1, 0x00FF0000);
    }
}

// triangle definition
t_vec3 triangle_vertices[] = {
    {0, 1, 5},  // Top vertex
    {-1, -1, 5}, // Bottom-left vertex
    {1, -1, 5}   // Bottom-right vertex
};

void render_triangle(t_data *img, t_mat4 view, t_mat4 projection) {
    t_vec3 projected[3];

    for (int i = 0; i < 3; i++) {
        t_vec3 v = triangle_vertices[i];
        v = mat4_mult_vec3(view, v);       // Apply view transformation
        v = mat4_mult_vec3(projection, v); // Apply projection transformation

        // Convert to screen coordinates
        v.x = (v.x + 1.0) * 0.5 * WIDTH;
        v.y = (1.0 - v.y) * 0.5 * HEIGHT;
        projected[i] = v;
    }

    // Draw triangle edges
    draw_line(img, projected[0], projected[1], 0x00FF00); // Green
    draw_line(img, projected[1], projected[2], 0x00FF00); 
    draw_line(img, projected[2], projected[0], 0x00FF00);
}


// int frame_loop(void *param) {
//     static float angle = 0;
//     t_data *img = (t_data *)param;

//     // Clear window instead of destroying the image
//     mlx_clear_window(img->mlx, img->win);

//     // Camera setup
//     t_camera cam = {
//         .pos = {0, 0, -5},
//         .target = {0, 0, 0},
//         .up = {0, 1, 0}
//     };

//     // Create matrices
//     t_mat4 view = mat4_look_at(cam.pos, cam.target, cam.up);
//     t_mat4 proj = mat4_perspective(FOV, (float)WIDTH/HEIGHT, NEAR, FAR);

//     // Copy vertices to avoid modifying the original ones
//     t_vec3 transformed_vertices[8];
//     for (int i = 0; i < 8; i++) {
//         float x = cube_vertices[i].x;
//         float z = cube_vertices[i].z;
//         transformed_vertices[i].x = x * cos(angle) - z * sin(angle);
//         transformed_vertices[i].z = x * sin(angle) + z * cos(angle);
//         transformed_vertices[i].y = cube_vertices[i].y;
//     }

//     angle += 0.02; // Increment rotation angle

//     // Render the cube
//     render_cube(img, view, proj);

//     // **Important: Draw image to window**
//     mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);

//     return 0;
// }

int frame_loop(void *param) {
    t_data *img = (t_data *)param;

    mlx_clear_window(img->mlx, img->win);

    // Camera setup
    t_camera cam = {
        .pos = {0, 0, -5}, 
        .target = {0, 0, 0}, 
        .up = {0, 1, 0}
    };

    t_mat4 view = mat4_look_at(cam.pos, cam.target, cam.up);
    t_mat4 proj = mat4_perspective(FOV, (float)WIDTH / HEIGHT, NEAR, FAR);

    // Render the triangle
    render_triangle(img, view, proj);

    mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);

    return 0;
}




int main(void) {
	void    *mlx;
	void    *win;
	t_data  img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "3D Cube");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
							   &img.line_length, &img.endian);

	img.mlx = mlx; // Store mlx instance in img
	img.win = win; // Store window instance in img

	mlx_loop_hook(mlx, frame_loop, &img);
	mlx_loop(mlx);
	return 0;
}
