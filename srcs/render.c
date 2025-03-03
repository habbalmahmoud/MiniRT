#include "../includes/miniRT.h"



 void put_pixel(t_mlx *mlx, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

/* === Ray Generation from Camera === */

/*
 * generate_ray:
 *   Given a pixel (x, y) and camera parameters, computes the ray that passes
 *   from the camera origin through the pixel.
 */
 t_ray generate_ray(int x, int y, t_cm *cam)
{
    t_ray ray;
    float forward[3], right[3], true_up[3];
    float up[3] = {0, 1, 0};

    /* Camera origin */
    ray.orig[0] = cam->cor[0];
    ray.orig[1] = cam->cor[1];
    ray.orig[2] = cam->cor[2];

    /* Forward vector (camera direction) */
    forward[0] = cam->vector[0];
    forward[1] = cam->vector[1];
    forward[2] = cam->vector[2];
    normalize(forward, forward);

    /* Compute right vector (cross of forward and up) */
    if (fabs(dot(forward, up)) > 0.999f)
    {
        up[0] = 1;
        up[1] = 0;
        up[2] = 0;
    }
    cross(forward, up, right);
    normalize(right, right);

    /* Recompute true up vector */
    cross(right, forward, true_up);
    normalize(true_up, true_up);

    /* Convert FOV (horizontal) to radians */
    float fov_rad = cam->fov * (M_PI / 180.0f);
    float aspect_ratio = (float)WIDTH / (float)HEIGHT;
    /* Screen space coordinates (normalized to [-1, 1]) */
    float px = (2 * ((x + 0.5f) / WIDTH) - 1) * tan(fov_rad / 2) * aspect_ratio;
    float py = (1 - 2 * ((y + 0.5f) / HEIGHT)) * tan(fov_rad / 2);

    /* Compute ray direction: forward + (px * right) + (py * true_up) */
    float dir[3], tmp[3];
    scale(right, px, tmp);
    add(forward, tmp, dir);
    scale(true_up, py, tmp);
    add(dir, tmp, dir);
    normalize(dir, ray.dir);

    return ray;
}

/* === Scene Rendering === */

/*
 * render_scene:
 *   Iterates over every pixel, generates a ray, checks for intersections with the sphere(s),
 *   computes lighting, and writes the final color to the image.
 */
void render_scene(t_mlx *mlx, t_cor *scene)
{
    int x, y;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            t_ray ray = generate_ray(x, y, &scene->cm);
            int color = 0x000000; /* Background color: black */
            float best_t = 1e30;
            int hit_type = 0; /* 0: none, 1: sphere, 2: plane */
            t_sp *hit_sphere = NULL;
            t_pl *hit_plane = NULL;

            /* Check sphere intersections */
            t_sp_list *cur_s = scene->spheres;
            while (cur_s)
            {
                float t = intersect_sphere(ray, &cur_s->sphere);
                if (t > 0 && t < best_t)
                {
                    best_t = t;
                    hit_type = 1;
                    hit_sphere = &cur_s->sphere;
                }
                cur_s = cur_s->next;
            }

            /* Check plane intersections */
            t_pl_list *cur_p = scene->planes;
            while (cur_p)
            {
                float t = intersect_plane(ray, &cur_p->plane);
                if (t > 0 && t < best_t)
                {
                    best_t = t;
                    hit_type = 2;
                    hit_plane = &cur_p->plane;
                }
                cur_p = cur_p->next;
            }

            if (hit_type)
            {
                /* Compute hit point: ray.origin + best_t * ray.dir */
                float hit_point[3], scaled[3];
                scale(ray.dir, best_t, scaled);
                add(ray.orig, scaled, hit_point);

                /* Compute normal and get object color */
                float normal[3];
                int obj_color[3] = {0, 0, 0};
                if (hit_type == 1)
                {
                    sphere_normal(hit_sphere, hit_point, normal);
                    obj_color[0] = (int)hit_sphere->rgb[0];
                    obj_color[1] = (int)hit_sphere->rgb[1];
                    obj_color[2] = (int)hit_sphere->rgb[2];
                }
                else if (hit_type == 2)
                {
                    plane_normal(hit_plane, normal);
                    obj_color[0] = (int)hit_plane->rgb[0];
                    obj_color[1] = (int)hit_plane->rgb[1];
                    obj_color[2] = (int)hit_plane->rgb[2];
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
