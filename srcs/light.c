#include "../includes/miniRT.h"

void in_shd(t_cor *scene, t_ish_utils *shadow_utils, float normal[3], float hit_point[3])
{
	int i;

	i = -1;
    shadow_utils->epsilon = 0.001f;
	while (++i < 3)
		shadow_utils->shadow_orig[i] = hit_point[i] + normal[i] * shadow_utils->epsilon;
    subtract(scene->light.cor, shadow_utils->shadow_orig, shadow_utils->light_dir);
    shadow_utils->light_distance = sqrt(dot(shadow_utils->light_dir, shadow_utils->light_dir));
    normalize(shadow_utils->light_dir, shadow_utils->light_dir);
	i = -1;
    while(++i < 3)
	{
        shadow_utils->shadow_ray.orig[i] = shadow_utils->shadow_orig[i];
        shadow_utils->shadow_ray.dir[i] = shadow_utils->light_dir[i];
    }
    shadow_utils->cur_s = scene->spheres;
}

int in_shd2(t_cor *scene, t_ish_utils *shadow_utils)
{
	while (shadow_utils->cur_s)
	{
        shadow_utils->t = intersect_sphere(shadow_utils->shadow_ray, &shadow_utils->cur_s->sphere);
        if (shadow_utils->t > 0.001f && shadow_utils->t < shadow_utils->light_distance)
            return 1;
        shadow_utils->cur_s = shadow_utils->cur_s->next;
    }
    shadow_utils->cur_p = scene->planes;
    while (shadow_utils->cur_p)
	{
        shadow_utils->t = intersect_plane(shadow_utils->shadow_ray, &shadow_utils->cur_p->plane);
        if (shadow_utils->t > 0.001f && shadow_utils->t < shadow_utils->light_distance)
            return 1;
        shadow_utils->cur_p = shadow_utils->cur_p->next;
    }
	return 0;
}

int in_shadow(t_cor *scene, float hit_point[3], float normal[3])
{
	t_ish_utils shadow_utils;
	
	in_shd(scene, &shadow_utils, normal, hit_point);
	if (in_shd2(scene, &shadow_utils) == 1)
		return 1;
    shadow_utils.cur_c = scene->cylinders;
    while (shadow_utils.cur_c)
	{
        shadow_utils.t = intersect_cylinder(shadow_utils.shadow_ray, &shadow_utils.cur_c->cyl, &shadow_utils.dummy);
        if (shadow_utils.t > 0.001f && shadow_utils.t < shadow_utils.light_distance)
            return 1;
        shadow_utils.cur_c = shadow_utils.cur_c->next;
    }
    return 0;
}

int compute_lighting(float hit_point[3], float normal[3], t_cor *scene)
{
    float intensity;
	float light_dir[3];
	float n_dot_l;

	intensity = scene->am.am;
    if (!in_shadow(scene, hit_point, normal))
    {
        subtract(scene->light.cor, hit_point, light_dir);
        normalize(light_dir, light_dir);
        n_dot_l = dot(normal, light_dir);
        if (n_dot_l > 0)
            intensity += scene->light.brightness * n_dot_l;
    }
    if (intensity > 1.0f)
        intensity = 1.0f;
    return (int)(intensity * 255);
}

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}
