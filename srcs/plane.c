/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:55:15 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 09:55:16 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float	intersect_plane(t_ray ray, t_pl *plane)
{
	float	denom;
	float	p0l[3];
	float	t;

	denom = dot(plane->vector, ray.dir);
	if (fabs(denom) < 1e-6)
		return (-1.0f);
	subtract(plane->cor, ray.orig, p0l);
	t = dot(p0l, plane->vector) / denom;
	if (t >= 0.001f)
		return (t);
	else
		return (-1.0f);
}

void	plane_normal(t_pl *plane, float normal[3])
{
	normal[0] = plane->vector[0];
	normal[1] = plane->vector[1];
	normal[2] = plane->vector[2];
	normalize(normal, normal);
}
