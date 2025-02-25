#ifndef MINIRT_H
#define MINIRT_H

#include "./mlx/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "X11/X.h"
#include "X11/keysym.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_vec3 {
    double x, y, z;
} t_vec3;

typedef struct s_ray {
    t_vec3 origin;
    t_vec3 direction;
} t_ray;

typedef struct s_sphere {
    t_vec3 center;
    double radius;
    int color;
} t_sphere;

typedef struct s_camera {
    t_vec3 pos;
    t_vec3 dir;
    double fov;
} t_camera;

typedef struct s_mlx {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_length;
    int endian;
} t_mlx;

typedef struct s_light {
    t_vec3 pos;
    double intensity;
} t_light;

typedef struct s_scene {
    t_camera camera;
    t_sphere *spheres;
    int num_spheres;
	t_light light;  // Add light source
    double ambient_intensity; // Ambient light level
    t_mlx mlx;
    int width, height;
} t_scene;

t_vec3 vec_sub(t_vec3 a, t_vec3 b);
t_vec3 vec_add(t_vec3 a, t_vec3 b);
t_vec3 vec_mul(t_vec3 a, double t);
double vec_dot(t_vec3 a, t_vec3 b);
t_vec3 vec_normalize(t_vec3 v);
int create_trgb(int t, int r, int g, int b);
int ray_sphere_intersect(t_ray ray, t_sphere sphere, double *t, t_vec3 *hit_point, t_vec3 *normal);
void render_scene(t_scene *scene);
void parse_scene(const char *filename, t_scene *scene);

#endif

