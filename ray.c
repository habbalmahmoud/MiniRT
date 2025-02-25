#include "./miniRT.h"

int ray_sphere_intersect(t_ray ray, t_sphere sphere, double *t, t_vec3 *hit_point, t_vec3 *normal) {
    t_vec3 oc = vec_sub(ray.origin, sphere.center);
    double a = vec_dot(ray.direction, ray.direction);
    double b = 2.0 * vec_dot(oc, ray.direction);
    double c = vec_dot(oc, oc) - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c;

    printf("Checking Sphere at (%.2f, %.2f, %.2f), Radius: %.2f\n",
           sphere.center.x, sphere.center.y, sphere.center.z, sphere.radius);

    if (discriminant < 0) {
        printf("Ray missed sphere. Discriminant: %.2f\n", discriminant);
        return 0;
    }

    *t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (*t < 0) {
        printf("Ray hit behind camera. t = %.2f\n", *t);
        return 0;
    }

    *hit_point = vec_add(ray.origin, vec_mul(ray.direction, *t)); // Compute intersection point
    *normal = vec_normalize(vec_sub(*hit_point, sphere.center));  // Compute normal at hit point

    printf("Ray hit sphere at (%.2f, %.2f, %.2f) with normal (%.2f, %.2f, %.2f)\n",
           hit_point->x, hit_point->y, hit_point->z,
           normal->x, normal->y, normal->z);

    return 1;
}


/**/
/*int ray_sphere_intersect(t_ray ray, t_sphere sphere, double *t, t_vec3 *hit_point, t_vec3 *normal) {*/
/*    t_vec3 oc = vec_sub(ray.origin, sphere.center);*/
/*    double a = vec_dot(ray.direction, ray.direction);*/
/*    double b = 2.0 * vec_dot(oc, ray.direction);*/
/*    double c = vec_dot(oc, oc) - sphere.radius * sphere.radius;*/
/*    double discriminant = b * b - 4 * a * c;*/
/**/
/*    if (discriminant < 0)*/
/*        return 0;*/
/*    *t = (-b - sqrt(discriminant)) / (2.0 * a);*/
/*	if (*t < 0) return 0; // Hit is behind the camera*/
/**/
/*    *hit_point = vec_add(ray.origin, vec_mul(ray.direction, *t)); // Compute intersection point*/
/*    *normal = vec_normalize(vec_sub(*hit_point, sphere.center));  // Compute normal at hit point*/
/*    return 1;*/
/*}*/

