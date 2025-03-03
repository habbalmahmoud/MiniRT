#include "../includes/miniRT.h"


int in_shadow(t_cor *scene, float hit_point[3], float normal[3])
{
    float epsilon = 0.001f;
    float shadow_orig[3];
    for (int i = 0; i < 3; i++)
        shadow_orig[i] = hit_point[i] + normal[i] * epsilon;

    float light_dir[3];
    subtract(scene->light.cor, shadow_orig, light_dir);
    float light_distance = sqrt(dot(light_dir, light_dir));
    normalize(light_dir, light_dir);

    t_ray shadow_ray;
    for (int i = 0; i < 3; i++)
    {
        shadow_ray.orig[i] = shadow_orig[i];
        shadow_ray.dir[i] = light_dir[i];
    }
    // Check intersection with spheres
    t_sp_list *cur_s = scene->spheres;
    while (cur_s)
    {
        float t = intersect_sphere(shadow_ray, &cur_s->sphere);
        if (t > 0.001f && t < light_distance)
            return 1;
        cur_s = cur_s->next;
    }
    // Check intersection with planes
    t_pl_list *cur_p = scene->planes;
    while (cur_p)
    {
        float t = intersect_plane(shadow_ray, &cur_p->plane);
        if (t > 0.001f && t < light_distance)
            return 1;
        cur_p = cur_p->next;
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
