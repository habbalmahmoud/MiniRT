/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:54:44 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 10:16:37 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	int_cyl(t_ray ray, t_cy *cylinder, t_cy_utils *cy_utils)
{
	normalize(cylinder->vector, cy_utils->v);
	cy_utils->r = cylinder->cy_diameter * 0.5f;
	cy_utils->h = cylinder->cy_height;
	cy_utils->half_h = cy_utils->h * 0.5f;
	subtract(ray.orig, cylinder->cor, cy_utils->delta);
	cy_utils->d_dot_v = dot(ray.dir, cy_utils->v);
	cy_utils->delta_dot_v = dot(cy_utils->delta, cy_utils->v);
	scale(cy_utils->v, cy_utils->d_dot_v, cy_utils->temp);
	subtract(ray.dir, cy_utils->temp, cy_utils->d_perp);
	scale(cy_utils->v, cy_utils->delta_dot_v, cy_utils->temp);
	subtract(cy_utils->delta, cy_utils->temp, cy_utils->delta_perp);
	cy_utils->a = dot(cy_utils->d_perp, cy_utils->d_perp);
	cy_utils->b = 2.0f * dot(cy_utils->d_perp, cy_utils->delta_perp);
	cy_utils->c_val = dot(cy_utils->delta_perp, cy_utils->delta_perp)
		- cy_utils->r * cy_utils->r;
}

void	int_cyl2(t_ray ray, t_cy *cylinder, t_cy_utils *cy_utils)
{
	cy_utils->t2 = (-cy_utils->b + cy_utils->sqrt_disc) / (2 * cy_utils->a);
	cy_utils->t_lateral = 1e30;
	if (cy_utils->t1 > 0.001f)
	{
		scale(ray.dir, cy_utils->t1, cy_utils->tempp);
		add(ray.orig, cy_utils->tempp, cy_utils->p);
		subtract(cy_utils->p, cylinder->cor, cy_utils->temp_vec);
		cy_utils->proj = dot(cy_utils->temp_vec, cy_utils->v);
		if (fabs(cy_utils->proj) <= cy_utils->half_h
			&& cy_utils->t1 < cy_utils->t_lateral)
			cy_utils->t_lateral = cy_utils->t1;
	}
	if (cy_utils->t2 > 0.001f)
	{
		scale(ray.dir, cy_utils->t2, cy_utils->tempp);
		add(ray.orig, cy_utils->tempp, cy_utils->p);
		subtract(cy_utils->p, cylinder->cor, cy_utils->temp_vec);
		cy_utils->proj = dot(cy_utils->temp_vec, cy_utils->v);
		if (fabs(cy_utils->proj) <= cy_utils->half_h
			&& cy_utils->t2 < cy_utils->t_lateral)
			cy_utils->t_lateral = cy_utils->t2;
	}
	if (cy_utils->t_lateral == 1e30)
		cy_utils->t_lateral = -1.0f;
}

void	int_cyl4(t_ray ray, t_cy_utils *cy_utils)
{
	if (cy_utils->t_top > 0.001f)
	{
		scale(ray.dir, cy_utils->t_top, cy_utils->temp);
		add(ray.orig, cy_utils->temp, cy_utils->p);
		subtract(cy_utils->p, cy_utils->top_center, cy_utils->diff);
		if (sqrt(dot(cy_utils->diff, cy_utils->diff)) > cy_utils->r)
			cy_utils->t_top = -1.0f;
	}
	else
		cy_utils->t_top = -1.0f;
	subtract(cy_utils->bottom_center, ray.orig, cy_utils->temp_vec);
	cy_utils->t_bottom = dot(cy_utils->temp_vec, cy_utils->v) / cy_utils->denom;
	if (cy_utils->t_bottom > 0.001f)
	{
		scale(ray.dir, cy_utils->t_bottom, cy_utils->temp);
		add(ray.orig, cy_utils->temp, cy_utils->p);
		subtract(cy_utils->p, cy_utils->bottom_center, cy_utils->diff);
		if (sqrt(dot(cy_utils->diff, cy_utils->diff)) > cy_utils->r)
			cy_utils->t_bottom = -1.0f;
	}
	else
		cy_utils->t_bottom = -1.0f;
}

void	int_cyl3(t_ray ray, t_cy *cylinder, t_cy_utils *cy_utils)
{
	scale(cy_utils->v, cy_utils->half_h, cy_utils->half_v);
	add(cylinder->cor, cy_utils->half_v, cy_utils->top_center);
	subtract(cylinder->cor, cy_utils->half_v, cy_utils->bottom_center);
	cy_utils->t_top = -1.0f;
	cy_utils->t_bottom = -1.0f;
	cy_utils->denom = dot(ray.dir, cy_utils->v);
	if (fabs(cy_utils->denom) > 1e-6)
	{
		subtract(cy_utils->top_center, ray.orig, cy_utils->temp_vec);
		cy_utils->t_top = dot(cy_utils->temp_vec, cy_utils->v)
			/ cy_utils->denom;
		int_cyl4(ray, cy_utils);
	}
}

int	int_cyl5(t_cy_utils *cy_utils, int *hit_part)
{
	cy_utils->t_final = 1e30;
	cy_utils->part = -1;
	if (cy_utils->t_lateral > 0 && cy_utils->t_lateral < cy_utils->t_final)
	{
		cy_utils->t_final = cy_utils->t_lateral;
		cy_utils->part = 0;
	}
	if (cy_utils->t_top > 0 && cy_utils->t_top < cy_utils->t_final)
	{
		cy_utils->t_final = cy_utils->t_top;
		cy_utils->part = 1;
	}
	if (cy_utils->t_bottom > 0 && cy_utils->t_bottom < cy_utils->t_final)
	{
		cy_utils->t_final = cy_utils->t_bottom;
		cy_utils->part = 2;
	}
	if (cy_utils->t_final == 1e30)
		return (1);
	*hit_part = cy_utils->part;
	return (0);
}
