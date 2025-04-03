#include "../includes/miniRT.h"

int in_shadow(t_cor *scene, float hit_point[3], float normal[3])
{
	t_ish_utils shadow_utils;
	int i;

	i = -1;
    shadow_utils.epsilon = 0.001f;
	while (++i < 3)
		shadow_utils.shadow_orig[i] = hit_point[i] + normal[i] * shadow_utils.epsilon;
    subtract(scene->light.cor, shadow_utils.shadow_orig, shadow_utils.light_dir);
    shadow_utils.light_distance = sqrt(dot(shadow_utils.light_dir, shadow_utils.light_dir));
    normalize(shadow_utils.light_dir, shadow_utils.light_dir);
    for (int i = 0; i < 3; i++) {
        shadow_utils.shadow_ray.orig[i] = shadow_utils.shadow_orig[i];
        shadow_utils.shadow_ray.dir[i] = shadow_utils.light_dir[i];
    }
    // Check spheres
    shadow_utils.cur_s = scene->spheres;
    while (shadow_utils.cur_s) {
        shadow_utils.t = intersect_sphere(shadow_utils.shadow_ray, &shadow_utils.cur_s->sphere);
        if (shadow_utils.t > 0.001f && shadow_utils.t < shadow_utils.light_distance)
            return 1;
        shadow_utils.cur_s = shadow_utils.cur_s->next;
    }
    // Check planes
    shadow_utils.cur_p = scene->planes;
    while (shadow_utils.cur_p) {
        shadow_utils.t = intersect_plane(shadow_utils.shadow_ray, &shadow_utils.cur_p->plane);
        if (shadow_utils.t > 0.001f && shadow_utils.t < shadow_utils.light_distance)
            return 1;
        shadow_utils.cur_p = shadow_utils.cur_p->next;
    }
    // Check cylinders
    shadow_utils.cur_c = scene->cylinders;
    while (shadow_utils.cur_c) {
        shadow_utils.t = intersect_cylinder(shadow_utils.shadow_ray, &shadow_utils.cur_c->cyl, &shadow_utils.dummy);
        if (shadow_utils.t > 0.001f && shadow_utils.t < shadow_utils.light_distance)
            return 1;
        shadow_utils.cur_c = shadow_utils.cur_c->next;
    }
    return 0;
}


int compute_lighting(float hit_point[3], float normal[3], t_cor *scene)
{
    float intensity = scene->am.am; // Ambient always applied

    if (!in_shadow(scene, hit_point, normal))
    {
        float light_dir[3];
        subtract(scene->light.cor, hit_point, light_dir);
        normalize(light_dir, light_dir);
        float n_dot_l = dot(normal, light_dir);
        if (n_dot_l > 0)
            intensity += scene->light.brightness * n_dot_l;
    }
    if (intensity > 1.0f)
        intensity = 1.0f;
    return (int)(intensity * 255);
}

/* === Helper to pack color components into an integer === */

 int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}
