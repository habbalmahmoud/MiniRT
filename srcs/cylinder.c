/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:54:59 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 10:14:58 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float	intersect_cylinder(t_ray ray, t_cy *cylinder, int *hit_part)
{
	t_cy_utils	cy_utils;

	int_cyl(ray, cylinder, &cy_utils);
	cy_utils.t_lateral = -1.0f;
	if (fabs(cy_utils.a) > 1e-6)
	{
		cy_utils.discriminant = cy_utils.b * cy_utils.b - 4
			* cy_utils.a * cy_utils.c_val;
		if (cy_utils.discriminant >= 0)
		{
			cy_utils.sqrt_disc = sqrt(cy_utils.discriminant);
			cy_utils.t1 = (-cy_utils.b - cy_utils.sqrt_disc) / (2 * cy_utils.a);
			int_cyl2(ray, cylinder, &cy_utils);
		}
	}
	int_cyl3(ray, cylinder, &cy_utils);
	if (int_cyl5(&cy_utils, hit_part) == 1)
		return (-1.0f);
	return (cy_utils.t_final);
}

void	cylinder_normal(t_cy *cyl, float hit_point[3], int hit_part,
						float normal[3])
{
	t_cyl_norm	norm;

	normalize(cyl->vector, norm.v);
	if (hit_part == 0)
	{
		subtract(hit_point, cyl->cor, norm.temp);
		norm.proj = dot(norm.temp, norm.v);
		scale(norm.v, norm.proj, norm.proj_vec);
		subtract(norm.temp, norm.proj_vec, norm.lateral);
		normalize(norm.lateral, normal);
	}
	else if (hit_part == 1)
	{
		normal[0] = norm.v[0];
		normal[1] = norm.v[1];
		normal[2] = norm.v[2];
	}
	else if (hit_part == 2)
	{
		normal[0] = -norm.v[0];
		normal[1] = -norm.v[1];
		normal[2] = -norm.v[2];
	}
}
