#include "miniRT.h"
int create_trgb(int t, int r, int g, int b) {
    return (t << 24 | r << 16 | g << 8 | b);
}


void render_scene(t_scene *scene) {
    int i, j;
    t_ray ray;
    double t;
    t_sphere *sphere;
    t_vec3 hit_point, normal;

    printf("Rendering scene...\n");

    for (j = 0; j < scene->height; j++) {
        for (i = 0; i < scene->width; i++) {
            // Compute ray direction
            double u = (2.0 * i / (scene->width - 1)) - 1.0;
            double v = 1.0 - (2.0 * j / (scene->height - 1)); 
            ray.origin = scene->camera.pos;
            
		
			ray.direction = vec_normalize((t_vec3){u, v * (scene->height / scene->width), 1.0});



            // Print ray for center pixel
            if (i == scene->width / 2 && j == scene->height / 2) {
                printf("Ray from (%.2f, %.2f, %.2f) -> Dir (%.2f, %.2f, %.2f)\n",
                       ray.origin.x, ray.origin.y, ray.origin.z,
                       ray.direction.x, ray.direction.y, ray.direction.z);
            }

            // Check for the closest sphere hit
            double closest_t = INFINITY;
            t_sphere *closest_sphere = NULL;
            for (int k = 0; k < scene->num_spheres; k++) {
                sphere = &scene->spheres[k];
                if (ray_sphere_intersect(ray, *sphere, &t, &hit_point, &normal) && t < closest_t) {
                    closest_t = t;
                    closest_sphere = sphere;
                }
            }

            // Debug intersection
            if (closest_sphere) {
                printf("Hit sphere at (%.2f, %.2f, %.2f), Radius: %.2f\n",
                       closest_sphere->center.x, closest_sphere->center.y, closest_sphere->center.z,
                       closest_sphere->radius);
            }

            if (closest_sphere) {  
                // Compute lighting at the hit point
                double light_intensity = scene->ambient_intensity;

                // Check if the point is in shadow
                t_ray shadow_ray;
                shadow_ray.origin = vec_add(hit_point, vec_mul(normal, 0.001)); // Offset to avoid self-shadowing
                shadow_ray.direction = vec_normalize(vec_sub(scene->light.pos, hit_point));

                int in_shadow = 0;
                for (int k = 0; k < scene->num_spheres; k++) {
                    if (ray_sphere_intersect(shadow_ray, scene->spheres[k], &t, &hit_point, &normal)) {
                        in_shadow = 1;
                        break;
                    }
                }

                if (in_shadow) {
                    printf("Point at (%.2f, %.2f, %.2f) is in shadow\n",
                           hit_point.x, hit_point.y, hit_point.z);
                }

                if (!in_shadow) {
                    // Diffuse lighting (Lambertian reflection)
                    t_vec3 light_dir = vec_normalize(vec_sub(scene->light.pos, hit_point));
                    double diffuse = vec_dot(normal, light_dir);
                    if (diffuse > 0) {
                        light_intensity += scene->light.intensity * diffuse;
                    }
                }

                // Apply final color with lighting
                int r = (closest_sphere->color >> 16 & 0xFF) * light_intensity;
                int g = (closest_sphere->color >> 8 & 0xFF) * light_intensity;
                int b = (closest_sphere->color & 0xFF) * light_intensity;
                int final_color = (255 << 24) | (r << 16) | (g << 8) | b;

                // Debug final color
                printf("Final color (R: %d, G: %d, B: %d) at pixel (%d, %d)\n", r, g, b, i, j);

                mlx_pixel_put(scene->mlx.mlx, scene->mlx.win, i, j, final_color);
            }
        }
    }
}


/*void render_scene(t_scene *scene) {*/
/*    int i, j;*/
/*    t_ray ray;*/
/*    double t;*/
/*    t_sphere *sphere;*/
/*    t_vec3 hit_point, normal;*/
/**/
/*    for (j = 0; j < scene->height; j++) {*/
/*        for (i = 0; i < scene->width; i++) {*/
/*            // Compute ray direction*/
/*            double u = (2.0 * i / (scene->width - 1)) - 1.0;*/
/*            double v = 1.0 - (2.0 * j / (scene->height - 1)); */
/*            ray.origin = scene->camera.pos;*/
/*            ray.direction = vec_normalize((t_vec3){u, v, 1.0});*/
/**/
/*            // Check for the closest sphere hit*/
/*            double closest_t = INFINITY;*/
/*            t_sphere *closest_sphere = NULL;*/
/*            for (int k = 0; k < scene->num_spheres; k++) {*/
/*                sphere = &scene->spheres[k];*/
/*                if (ray_sphere_intersect(ray, *sphere, &t, &hit_point, &normal) && t < closest_t) {*/
/*                    closest_t = t;*/
/*                    closest_sphere = sphere;*/
/*                }*/
/*            }*/
/**/
/*            if (closest_sphere) {  */
/*                // Compute lighting at the hit point*/
/*                double light_intensity = scene->ambient_intensity;*/
/**/
/*                // Check if the point is in shadow*/
/*                t_ray shadow_ray;*/
/*                shadow_ray.origin = vec_add(hit_point, vec_mul(normal, 0.001)); // Offset to avoid self-shadowing*/
/*                shadow_ray.direction = vec_normalize(vec_sub(scene->light.pos, hit_point));*/
/**/
/*                int in_shadow = 0;*/
/*                for (int k = 0; k < scene->num_spheres; k++) {*/
/*                    if (ray_sphere_intersect(shadow_ray, scene->spheres[k], &t, &hit_point, &normal)) {*/
/*                        in_shadow = 1;*/
/*                        break;*/
/*                    }*/
/*                }*/
/**/
/*                if (!in_shadow) {*/
/*                    // Diffuse lighting (Lambertian reflection)*/
/*                    t_vec3 light_dir = vec_normalize(vec_sub(scene->light.pos, hit_point));*/
/*                    double diffuse = vec_dot(normal, light_dir);*/
/*                    if (diffuse > 0) {*/
/*                        light_intensity += scene->light.intensity * diffuse;*/
/*                    }*/
/*                }*/
/**/
/*                // Apply final color with lighting*/
/*                int r = (closest_sphere->color >> 16 & 0xFF) * light_intensity;*/
/*                int g = (closest_sphere->color >> 8 & 0xFF) * light_intensity;*/
/*                int b = (closest_sphere->color & 0xFF) * light_intensity;*/
/*                int final_color = (255 << 24) | (r << 16) | (g << 8) | b;*/
/**/
/*                mlx_pixel_put(scene->mlx.mlx, scene->mlx.win, i, j, final_color);*/
/*            }*/
/*        }*/
/*    }*/
/*}*/

