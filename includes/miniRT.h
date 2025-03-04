#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include <math.h>
#include "../Libft/libft.h"
#include "../GNL/get_next_line.h"
#include "../minilibx-linux/mlx.h"
#include "X11/X.h"
#include "X11/keysym.h"
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <unistd.h>

# define HEIGHT 700
# define WIDTH 1000

typedef struct s_mlx
{
    void        *ptr;
    void        *win_ptr;
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_mlx;

typedef struct s_light
{
    float       cor[3];
    float       brightness;
	float		rgb[3];
}               t_light;

typedef struct s_am
{
    float       am;
    float       rgb[3];
}               t_am;

typedef struct s_cm
{
    float       cor[3];
    float       vector[3];
    float       fov;
}               t_cm;

typedef struct s_sp
{
    float       cor[3];
    float       rgb[3];
    float       diameter;
}               t_sp;

typedef struct s_cy
{
    float       cor[3];
    float       vector[3];
    float       rgb[3];
    float       cy_diameter;
    float       cy_height;
}               t_cy;

typedef struct s_pl
{
    float       cor[3];
    float       vector[3];
    float       rgb[3];
}               t_pl;

/* Linked-list node definitions for each object type */
typedef struct s_sp_list {
    t_sp                sphere;
    struct s_sp_list    *next;
} t_sp_list;

typedef struct s_cy_list {
    t_cy                cyl;
    struct s_cy_list    *next;
} t_cy_list;

typedef struct s_pl_list {
    t_pl                plane;
    struct s_pl_list    *next;
} t_pl_list;

/* Unified scene structure.
   We use t_cor as our scene type. */
typedef struct s_cor
{
    t_am        am;
    t_cm        cm;
    t_light     light;
    t_sp_list   *spheres;
    t_cy_list   *cylinders;
    t_pl_list   *planes;
} t_cor;

/* Structure for duplicate checking for A, C, L */
typedef struct s_val
{
    bool    a;
    bool    c;
    bool    l;
    bool    sp;
    bool    cy;
    bool    pl;
} t_val;

typedef struct s_ray {
    float orig[3];   // Ray origin
    float dir[3];    // Ray direction (should be normalized)
} t_ray;


/* Function prototypes */

/* Object list management */
t_sp_list   *new_sphere(t_sp sphere);
void         add_sphere(t_cor *cor, t_sp sphere);
t_cy_list   *new_cylinder(t_cy cyl);
void         add_cylinder(t_cor *cor, t_cy cyl);
t_pl_list   *new_plane(t_pl plane);
void         add_plane(t_cor *cor, t_pl plane);

/* Validation / Parsing functions */
char       **checking_the_map(char *str);
int         validate(char **map, t_cor *cor);


void        minirt(char **av);
 float dot(float a[3], float b[3]);
 void subtract(float a[3],float b[3], float out[3]);
 void add(float a[3],float b[3], float out[3]);
 void scale(float v[3], float s, float out[3]);
 void cross(float a[3],float b[3], float out[3]);
 void normalize(float in[3], float out[3]);
 float intersect_sphere(t_ray ray, t_sp *sphere);
 void sphere_normal(t_sp *sphere, float hit_point[3], float normal[3]);
 int compute_lighting(float hit_point[3], float normal[3], t_cor *scene);
 int create_trgb(int t, int r, int g, int b);
 void put_pixel(t_mlx *mlx, int x, int y, int color);
 t_ray generate_ray(int x, int y, t_cm *cam);
 void render_scene(t_mlx *mlx, t_cor *scene);
int init(t_cor *scene);
float intersect_plane(t_ray ray, t_pl *plane);
void plane_normal(t_pl *plane, float normal[3]);
int in_shadow(t_cor *scene, float hit_point[3], float normal[3]);
void cylinder_normal(t_cy *cyl, float hit_point[3], int hit_part, float normal[3]);
float intersect_cylinder(t_ray ray, t_cy *cylinder, int *hit_part);

#endif
