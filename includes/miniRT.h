#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include <math.h>
#include "../Libft/libft.h"
#include "../GNL/get_next_line.h"
#include "../mlx/mlx.h"
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

/* Window and rendering */
void        minirt(char **av);
void        create_window(t_mlx *mlx, t_cor *cor);
void        render_scene(t_mlx *mlx, t_cor *cor);
void        put_pixel(t_mlx *mlx, int x, int y, int color);

/* Raytracing helpers */
float       dot_product(float v1[3], float v2[3]);
void        normalize(float v[3]);
int         ray_intersects_sphere(float origin[3], float dir[3], t_sp sphere, float *t);
int is_in_shadow(float hit_point[3], t_cor *scene, float light_pos[3]);

#endif
