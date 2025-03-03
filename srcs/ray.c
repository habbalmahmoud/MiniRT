#include "../includes/miniRT.h"


 float intersect_sphere(t_ray ray, t_sp *sphere)
{
    float oc[3];
    subtract(ray.orig, sphere->cor, oc);
    float r = sphere->diameter * 0.5f;
    float a = dot(ray.dir, ray.dir); // should be 1 if ray.dir is normalized
    float b = 2.0f * dot(oc, ray.dir);
    float c = dot(oc, oc) - r * r;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return -1.0f;
    float sqrt_disc = sqrt(discriminant);
    float t1 = (-b - sqrt_disc) / (2.0f * a);
    float t2 = (-b + sqrt_disc) / (2.0f * a);
    if (t1 > 0.001f && t1 < t2)
        return t1;
    if (t2 > 0.001f)
        return t2;
    return -1.0f;
}

/*
 * sphere_normal:
 *   Computes the normal vector at the hit point on the sphere's surface.
 */
 void sphere_normal(t_sp *sphere, float hit_point[3], float normal[3])
{
    float r = sphere->diameter * 0.5f;
    normal[0] = (hit_point[0] - sphere->cor[0]) / r;
    normal[1] = (hit_point[1] - sphere->cor[1]) / r;
    normal[2] = (hit_point[2] - sphere->cor[2]) / r;
}

