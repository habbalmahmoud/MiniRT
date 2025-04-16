/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:55:57 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 10:12:59 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include "../Libft/libft.h"
# include "../GNL/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include "X11/X.h"
# include "X11/keysym.h"
# include <stdlib.h>
# include <stdbool.h>
# include <float.h>
# include <unistd.h>

# define HEIGHT 700
# define WIDTH 1000

typedef struct s_mlx
{
	void	*ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_mlx;

typedef struct s_light
{
	float	cor[3];
	float	brightness;
	float	rgb[3];
}		t_light;

typedef struct s_am
{
	float	am;
	float	rgb[3];
}		t_am;

typedef struct s_cm
{
	float	cor[3];
	float	vector[3];
	float	fov;
}		t_cm;

typedef struct s_sp
{
	float	cor[3];
	float	rgb[3];
	float	diameter;
}		t_sp;

typedef struct s_cy
{
	float		cor[3];
	float		vector[3];
	float		rgb[3];
	float		cy_diameter;
	float		cy_height;
}		t_cy;

typedef struct s_pl
{
	float	cor[3];
	float	vector[3];
	float	rgb[3];
}		t_pl;

typedef struct s_sp_list {
	t_sp				sphere;
	struct s_sp_list	*next;
}		t_sp_list;

typedef struct s_cy_list
{
	t_cy				cyl;
	struct s_cy_list	*next;
}		t_cy_list;

typedef struct s_pl_list
{
	t_pl				plane;
	struct s_pl_list	*next;
}		t_pl_list;

typedef struct s_cor
{
	t_am		am;
	t_cm		cm;
	t_light		light;
	t_sp_list	*spheres;
	t_cy_list	*cylinders;
	t_pl_list	*planes;
}		t_cor;

typedef struct s_val
{
	bool	a;
	bool	c;
	bool	l;
	bool	sp;
	bool	cy;
	bool	pl;
}		t_val;

typedef struct s_ray
{
	float	orig[3];
	float	dir[3];
}		t_ray;

typedef struct s_cy_utils
{
	float	v[3];
	float	r;
	float	h;
	float	half_h;
	float	delta[3];
	float	d_dot_v;
	float	d_perp[3];
	float	delta_dot_v;
	float	delta_perp[3];
	float	temp[3];
	float	a;
	float	b;
	float	c_val;
	float	t_lateral;
	float	discriminant;
	float	sqrt_disc;
	float	t1;
	float	t2;
	float	p[3];
	float	tempp[3];
	float	temp_vec[3];
	float	proj;
	float	top_center[3];
	float	bottom_center[3];
	float	half_v[3];
	float	t_top;
	float	t_bottom;
	float	denom;
	float	diff[3];
	float	t_final;
	int		part;
}		t_cy_utils;

typedef struct s_cyl_norm
{
	float	v[3];
	float	temp[3];
	float	proj_vec[3];
	float	proj;
	float	lateral[3];
}		t_cyl_norm;

typedef struct s_ish_utils
{
	float		epsilon;
	float		shadow_orig[3];
	float		light_dir[3];
	float		light_distance;
	t_ray		shadow_ray;
	t_sp_list	*cur_s;
	float		t;
	t_pl_list	*cur_p;
	t_cy_list	*cur_c;
	int			dummy;
}		t_ish_utils;

typedef struct s_sphere_utils
{
	float	oc[3];
	float	r;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_disc;
	float	t1;
	float	t2;
}		t_sphere_utils;

typedef struct s_ray_utils
{
	t_ray	ray;
	float	forward[3];
	float	right[3];
	float	true_up[3];
	float	up[3];
	float	fov_rad;
	float	aspect_ratio;
	float	px;
	float	py;
	float	dir[3];
	float	tmp[3];
}		t_ray_utils;

typedef struct s_render_utils
{
	int			x;
	int			y;
	t_ray		ray;
	int			color;
	float		best_t;
	int			hit_type;
	t_sp		*hit_sphere;
	t_pl		*hit_plane;
	t_cy		*hit_cylinder;
	int			cylinder_hit_part;
	t_sp_list	*cur_s;
	float		t;
	t_pl_list	*cur_p;
	t_cy_list	*cur_c;
	int			hit_part;
	float		hit_point[3];
	float		scaled[3];
	float		normal[3];
	int			obj_color[3];
	int			intensity;
	int			r;
	int			g;
	int			b;
}		t_render_utils;

t_sp_list	*new_sphere(t_sp sphere);
void		add_sphere(t_cor *cor, t_sp sphere);
t_cy_list	*new_cylinder(t_cy cyl);
void		add_cylinder(t_cor *cor, t_cy cyl);
t_pl_list	*new_plane(t_pl plane);
void		add_plane(t_cor *cor, t_pl plane);
char		**checking_the_map(char *str);
int			validate(char **map, t_cor *cor);
void		minirt(char **av);
float		dot(float a[3], float b[3]);
void		subtract(float a[3], float b[3], float out[3]);
void		add(float a[3], float b[3], float out[3]);
void		scale(float v[3], float s, float out[3]);
void		cross(float a[3], float b[3], float out[3]);
void		normalize(float in[3], float out[3]);
float		intersect_sphere(t_ray ray, t_sp *sphere);
void		sphere_normal(t_sp *sphere, float hit_point[3], float normal[3]);
int			compute_lighting(float hit_point[3], float normal[3], t_cor *scene);
int			create_trgb(int t, int r, int g, int b);
void		put_pixel(t_mlx *mlx, int x, int y, int color);
t_ray		generate_ray(int x, int y, t_cm *cam);
void		render_scene(t_mlx *mlx, t_cor *scene);
int			init(t_cor *scene);
float		intersect_plane(t_ray ray, t_pl *plane);
void		plane_normal(t_pl *plane, float normal[3]);
int			in_shadow(t_cor *scene, float hit_point[3], float normal[3]);
void		cylinder_normal(t_cy *cyl, float hit_point[3],
				int hit_part, float normal[3]);
float		intersect_cylinder(t_ray ray, t_cy *cylinder, int *hit_part);
void		int_cyl(t_ray ray, t_cy *cylinder, t_cy_utils *cy_utils);
void		int_cyl2(t_ray ray, t_cy *cylinder, t_cy_utils *cy_utils);
void		int_cyl4(t_ray ray, t_cy_utils *cy_utils);
void		int_cyl3(t_ray ray, t_cy *cylinder, t_cy_utils *cy_utils);
int			int_cyl5(t_cy_utils *cy_utils, int *hit_part);
void		red_util1(t_cor *scene, t_render_utils *render_utils);
void		rend_util2(t_cor *scene, t_render_utils *render_utils);
void		rend_utils3(t_cor *scene, t_render_utils *render_utils);
void		rend_utils4(t_render_utils *render_utils);
void		rend_utils5(t_render_utils *render_utils, t_cor *scene);

#endif
