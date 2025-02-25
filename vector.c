#include "miniRT.h"

t_vec3 vec_sub(t_vec3 a, t_vec3 b) {
    return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec3 vec_add(t_vec3 a, t_vec3 b) {
    return (t_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3 vec_mul(t_vec3 a, double t) {
    return (t_vec3){a.x * t, a.y * t, a.z * t};
}

double vec_dot(t_vec3 a, t_vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3 vec_normalize(t_vec3 v) {
    double len = sqrt(vec_dot(v, v));
    return (t_vec3){v.x / len, v.y / len, v.z / len};
}

