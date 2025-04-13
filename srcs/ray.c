#include "../includes/miniRT.h"

float	intersect_sphere(t_ray ray, t_sp *sphere)
{
	t_sphere_utils	sphere_utils;

	subtract(ray.orig, sphere->cor, sphere_utils.oc);
	sphere_utils.r = sphere->diameter * 0.5f;
	sphere_utils.a = dot(ray.dir, ray.dir);
	sphere_utils.b = 2.0f * dot(sphere_utils.oc, ray.dir);
	sphere_utils.c = dot(sphere_utils.oc, sphere_utils.oc)
		- sphere_utils.r * sphere_utils.r;
	sphere_utils.discriminant = sphere_utils.b * sphere_utils.b
		- 4 * sphere_utils.a * sphere_utils.c;
	if (sphere_utils.discriminant < 0)
		return (-1.0f);
	sphere_utils.sqrt_disc = sqrt(sphere_utils.discriminant);
	sphere_utils.t1 = (-sphere_utils.b - sphere_utils.sqrt_disc)
		/ (2.0f * sphere_utils.a);
	sphere_utils.t2 = (-sphere_utils.b + sphere_utils.sqrt_disc)
		/ (2.0f * sphere_utils.a);
	if (sphere_utils.t1 > 0.001f && sphere_utils.t1 < sphere_utils.t2)
		return (sphere_utils.t1);
	if (sphere_utils.t2 > 0.001f)
		return (sphere_utils.t2);
	return (-1.0f);
}

void	sphere_normal(t_sp *sphere, float hit_point[3], float normal[3])
{
	float	r;

	r = sphere->diameter * 0.5f;
	normal[0] = (hit_point[0] - sphere->cor[0]) / r;
	normal[1] = (hit_point[1] - sphere->cor[1]) / r;
	normal[2] = (hit_point[2] - sphere->cor[2]) / r;
}
