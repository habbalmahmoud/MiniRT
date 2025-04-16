/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:55:20 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 09:55:21 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	red_util1(t_cor *scene, t_render_utils *render_utils)
{
	render_utils->ray = generate_ray(render_utils->x,
			render_utils->y, &scene->cm);
	render_utils->color = 0x000000;
	render_utils->best_t = 1e30;
	render_utils->hit_type = 0;
	render_utils->hit_sphere = NULL;
	render_utils->hit_plane = NULL;
	render_utils->hit_cylinder = NULL;
	render_utils->cylinder_hit_part = -1;
	render_utils->cur_s = scene->spheres;
	while (render_utils->cur_s)
	{
		render_utils->t = intersect_sphere(render_utils->ray,
				&render_utils->cur_s->sphere);
		if (render_utils->t > 0 && render_utils->t < render_utils->best_t)
		{
			render_utils->best_t = render_utils->t;
			render_utils->hit_type = 1;
			render_utils->hit_sphere = &render_utils->cur_s->sphere;
		}
		render_utils->cur_s = render_utils->cur_s->next;
	}
}

void	rend_util2(t_cor *scene, t_render_utils *render_utils)
{
	render_utils->cur_p = scene->planes;
	while (render_utils->cur_p)
	{
		render_utils->t = intersect_plane(render_utils->ray,
				&render_utils->cur_p->plane);
		if (render_utils->t > 0 && render_utils->t < render_utils->best_t)
		{
			render_utils->best_t = render_utils->t;
			render_utils->hit_type = 2;
			render_utils->hit_plane = &render_utils->cur_p->plane;
		}
		render_utils->cur_p = render_utils->cur_p->next;
	}
}

void	rend_utils3(t_cor *scene, t_render_utils *render_utils)
{
	render_utils->cur_c = scene->cylinders;
	while (render_utils->cur_c)
	{
		render_utils->t = intersect_cylinder(render_utils->ray,
				&render_utils->cur_c->cyl, &render_utils->hit_part);
		if (render_utils->t > 0 && render_utils->t < render_utils->best_t)
		{
			render_utils->best_t = render_utils->t;
			render_utils->hit_type = 3;
			render_utils->hit_cylinder = &render_utils->cur_c->cyl;
			render_utils->cylinder_hit_part = render_utils->hit_part;
		}
		render_utils->cur_c = render_utils->cur_c->next;
	}
}

void	rend_utils4(t_render_utils *render_utils)
{
	if (render_utils->hit_type == 1)
	{
		sphere_normal(render_utils->hit_sphere,
			render_utils->hit_point, render_utils->normal);
		render_utils->obj_color[0] = (int)render_utils->hit_sphere->rgb[0];
		render_utils->obj_color[1] = (int)render_utils->hit_sphere->rgb[1];
		render_utils->obj_color[2] = (int)render_utils->hit_sphere->rgb[2];
	}
	else if (render_utils->hit_type == 2)
	{
		plane_normal(render_utils->hit_plane, render_utils->normal);
		render_utils->obj_color[0] = (int)render_utils->hit_plane->rgb[0];
		render_utils->obj_color[1] = (int)render_utils->hit_plane->rgb[1];
		render_utils->obj_color[2] = (int)render_utils->hit_plane->rgb[2];
	}
	else if (render_utils->hit_type == 3)
	{
		cylinder_normal(render_utils->hit_cylinder, render_utils->hit_point,
			render_utils->cylinder_hit_part, render_utils->normal);
		render_utils->obj_color[0] = (int)render_utils->hit_cylinder->rgb[0];
		render_utils->obj_color[1] = (int)render_utils->hit_cylinder->rgb[1];
		render_utils->obj_color[2] = (int)render_utils->hit_cylinder->rgb[2];
	}
}

void	rend_utils5(t_render_utils *render_utils, t_cor *scene)
{
	scale(render_utils->ray.dir, render_utils->best_t, render_utils->scaled);
	add(render_utils->ray.orig, render_utils->scaled, render_utils->hit_point);
	render_utils->obj_color[0] = 0;
	render_utils->obj_color[1] = 0;
	render_utils->obj_color[2] = 0;
	rend_utils4(render_utils);
	normalize(render_utils->normal, render_utils->normal);
	render_utils->intensity = compute_lighting(
			render_utils->hit_point, render_utils->normal, scene);
	render_utils->r = (int)(render_utils->obj_color[0]
			* render_utils->intensity / 255);
	render_utils->g = (int)(render_utils->obj_color[1]
			* render_utils->intensity / 255);
}
