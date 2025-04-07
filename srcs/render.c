#include "../includes/miniRT.h"

void put_pixel(t_mlx *mlx, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void gen_ray(t_ray_utils *ray_utils, t_cm *cam)
{
	ray_utils->up[0] = 0;
	ray_utils->up[1] = 1;
	ray_utils->up[2] = 0;
    ray_utils->ray.orig[0] = cam->cor[0];
    ray_utils->ray.orig[1] = cam->cor[1];
    ray_utils->ray.orig[2] = cam->cor[2];
    ray_utils->forward[0] = cam->vector[0];
    ray_utils->forward[1] = cam->vector[1];
    ray_utils->forward[2] = cam->vector[2];
    normalize(ray_utils->forward, ray_utils->forward);
    if (fabs(dot(ray_utils->forward, ray_utils->up)) > 0.999f)
    {
        ray_utils->up[0] = 1;
        ray_utils->up[1] = 0;
        ray_utils->up[2] = 0;
    }
}

t_ray generate_ray(int x, int y, t_cm *cam)
{
	t_ray_utils ray_utils;

	gen_ray(&ray_utils, cam);
    cross(ray_utils.forward, ray_utils.up, ray_utils.right);
    normalize(ray_utils.right, ray_utils.right);
    cross(ray_utils.right, ray_utils.forward, ray_utils.true_up);
    normalize(ray_utils.true_up, ray_utils.true_up);
    ray_utils.fov_rad = cam->fov * (M_PI / 180.0f);
    ray_utils.aspect_ratio = (float)WIDTH / (float)HEIGHT;
    ray_utils.px = (2 * ((x + 0.5f) / WIDTH) - 1) * tan(ray_utils.fov_rad / 2) * ray_utils.aspect_ratio;
    ray_utils.py = (1 - 2 * ((y + 0.5f) / HEIGHT)) * tan(ray_utils.fov_rad / 2);
    scale(ray_utils.right, ray_utils.px, ray_utils.tmp);
    add(ray_utils.forward, ray_utils.tmp, ray_utils.dir);
    scale(ray_utils.true_up, ray_utils.py, ray_utils.tmp);
    add(ray_utils.dir, ray_utils.tmp, ray_utils.dir);
    normalize(ray_utils.dir, ray_utils.ray.dir);
    return ray_utils.ray;
}

void render_scene(t_mlx *mlx, t_cor *scene)
{
    int x, y;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            t_ray ray = generate_ray(x, y, &scene->cm);
            int color = 0x000000; // Background color (black)
            float best_t = 1e30;
            int hit_type = 0; // 0: none, 1: sphere, 2: plane, 3: cylinder
            t_sp *hit_sphere = NULL;
            t_pl *hit_plane = NULL;
            t_cy *hit_cylinder = NULL;
            int cylinder_hit_part = -1;

            // Test sphere intersections
            t_sp_list *cur_s = scene->spheres;
            while (cur_s) {
                float t = intersect_sphere(ray, &cur_s->sphere);
                if (t > 0 && t < best_t) {
                    best_t = t;
                    hit_type = 1;
                    hit_sphere = &cur_s->sphere;
                }
                cur_s = cur_s->next;
            }

            // Test plane intersections
            t_pl_list *cur_p = scene->planes;
            while (cur_p) {
                float t = intersect_plane(ray, &cur_p->plane);
                if (t > 0 && t < best_t) {
                    best_t = t;
                    hit_type = 2;
                    hit_plane = &cur_p->plane;
                }
                cur_p = cur_p->next;
            }

            // Test cylinder intersections
            t_cy_list *cur_c = scene->cylinders;
            while (cur_c) {
                int hit_part;
                float t = intersect_cylinder(ray, &cur_c->cyl, &hit_part);
                if (t > 0 && t < best_t) {
                    best_t = t;
                    hit_type = 3;
                    hit_cylinder = &cur_c->cyl;
                    cylinder_hit_part = hit_part;
                }
                cur_c = cur_c->next;
            }

            if (hit_type) {
                float hit_point[3], scaled[3];
                scale(ray.dir, best_t, scaled);
                add(ray.orig, scaled, hit_point);

                float normal[3];
                int obj_color[3] = {0, 0, 0};
                if (hit_type == 1) {
                    sphere_normal(hit_sphere, hit_point, normal);
                    obj_color[0] = (int)hit_sphere->rgb[0];
                    obj_color[1] = (int)hit_sphere->rgb[1];
                    obj_color[2] = (int)hit_sphere->rgb[2];
                }
                else if (hit_type == 2) {
                    plane_normal(hit_plane, normal);
                    obj_color[0] = (int)hit_plane->rgb[0];
                    obj_color[1] = (int)hit_plane->rgb[1];
                    obj_color[2] = (int)hit_plane->rgb[2];
                }
                else if (hit_type == 3) {
                    cylinder_normal(hit_cylinder, hit_point, cylinder_hit_part, normal);
                    obj_color[0] = (int)hit_cylinder->rgb[0];
                    obj_color[1] = (int)hit_cylinder->rgb[1];
                    obj_color[2] = (int)hit_cylinder->rgb[2];
                }
                normalize(normal, normal);
                int intensity = compute_lighting(hit_point, normal, scene);
                int r = (int)(obj_color[0] * intensity / 255);
                int g = (int)(obj_color[1] * intensity / 255);
                int b = (int)(obj_color[2] * intensity / 255);
                color = create_trgb(0, r, g, b);
            }
            put_pixel(mlx, x, y, color);
        }
    }
}





