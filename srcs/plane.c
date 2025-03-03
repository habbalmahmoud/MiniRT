#include "../includes/miniRT.h"



float intersect_plane(t_ray ray, t_pl *plane)
{
    float denom = dot(plane->vector, ray.dir);
    if (fabs(denom) < 1e-6)
        return -1.0f;  // Ray is parallel to the plane
    float p0l[3];
    subtract(plane->cor, ray.orig, p0l);
    float t = dot(p0l, plane->vector) / denom;
    return (t >= 0.001f) ? t : -1.0f;
}

/*
 * plane_normal:
 *   Returns the normalized normal vector of the plane.
 */
void plane_normal(t_pl *plane, float normal[3])
{
    normal[0] = plane->vector[0];
    normal[1] = plane->vector[1];
    normal[2] = plane->vector[2];
    normalize(normal, normal);
}
