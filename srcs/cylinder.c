#include "../includes/miniRT.h"

void	intersect_cylinder2()
{

}

float intersect_cylinder(t_ray ray, t_cy *cylinder, int *hit_part)
{
    float v[3];
    normalize(cylinder->vector, v);
    float r = cylinder->cy_diameter * 0.5f;
    float h = cylinder->cy_height;
    float half_h = h * 0.5f;
    float delta[3];
    subtract(ray.orig, cylinder->cor, delta);

    // Compute components perpendicular to the cylinder's axis.
    float D_dot_v = dot(ray.dir, v);
    float delta_dot_v = dot(delta, v);
    float D_perp[3], delta_perp[3], temp[3];
    scale(v, D_dot_v, temp);
    subtract(ray.dir, temp, D_perp);
    scale(v, delta_dot_v, temp);
    subtract(delta, temp, delta_perp);

    float A = dot(D_perp, D_perp);
    float B = 2.0f * dot(D_perp, delta_perp);
    float C_val = dot(delta_perp, delta_perp) - r*r;

    float t_lateral = -1.0f;
    if (fabs(A) > 1e-6) {
        float discriminant = B*B - 4*A*C_val;
        if (discriminant >= 0) {
            float sqrt_disc = sqrt(discriminant);
            float t1 = (-B - sqrt_disc) / (2*A);
            float t2 = (-B + sqrt_disc) / (2*A);
            t_lateral = 1e30;
            if (t1 > 0.001f) {
                float P[3], tempP[3];
                scale(ray.dir, t1, tempP);
                add(ray.orig, tempP, P);
                float temp_vec[3];
                subtract(P, cylinder->cor, temp_vec);
                float proj = dot(temp_vec, v);
                if (fabs(proj) <= half_h && t1 < t_lateral)
                    t_lateral = t1;
            }
            if (t2 > 0.001f) {
                float P[3], tempP[3];
                scale(ray.dir, t2, tempP);
                add(ray.orig, tempP, P);
                float temp_vec[3];
                subtract(P, cylinder->cor, temp_vec);
                float proj = dot(temp_vec, v);
                if (fabs(proj) <= half_h && t2 < t_lateral)
                    t_lateral = t2;
            }
            if (t_lateral == 1e30)
                t_lateral = -1.0f;
        }
    }

    // Compute cap intersections.
    float top_center[3], bottom_center[3];
    float half_v[3];
    scale(v, half_h, half_v);
    add(cylinder->cor, half_v, top_center);
    subtract(cylinder->cor, half_v, bottom_center);

    float t_top = -1.0f, t_bottom = -1.0f;
    float denom = dot(ray.dir, v);
    if (fabs(denom) > 1e-6) {
        // Top cap
        float temp_vec[3];
        subtract(top_center, ray.orig, temp_vec);
        t_top = dot(temp_vec, v) / denom;
        if (t_top > 0.001f) {
            float P[3], diff[3];
            scale(ray.dir, t_top, temp);
            add(ray.orig, temp, P);
            subtract(P, top_center, diff);
            if (sqrt(dot(diff, diff)) > r)
                t_top = -1.0f;
        } else {
            t_top = -1.0f;
        }
        // Bottom cap
        subtract(bottom_center, ray.orig, temp_vec);
        t_bottom = dot(temp_vec, v) / denom;
        if (t_bottom > 0.001f) {
            float P[3], diff[3];
            scale(ray.dir, t_bottom, temp);
            add(ray.orig, temp, P);
            subtract(P, bottom_center, diff);
            if (sqrt(dot(diff, diff)) > r)
                t_bottom = -1.0f;
        } else {
            t_bottom = -1.0f;
        }
    }

    // Choose the smallest positive t among lateral, top cap, and bottom cap.
    float t_final = 1e30;
    int part = -1;
    if (t_lateral > 0 && t_lateral < t_final) {
        t_final = t_lateral;
        part = 0; // lateral surface
    }
    if (t_top > 0 && t_top < t_final) {
        t_final = t_top;
        part = 1; // top cap
    }
    if (t_bottom > 0 && t_bottom < t_final) {
        t_final = t_bottom;
        part = 2; // bottom cap
    }
    if (t_final == 1e30)
        return -1.0f;
    *hit_part = part;
    return t_final;
}



void cylinder_normal(t_cy *cyl, float hit_point[3], int hit_part, float normal[3])
{
    float v[3];
	float temp[3]; 
	float proj_vec[3];
	float proj;
	float lateral[3];

	normalize(cyl->vector, v);
    if (hit_part == 0)
	{ 
        subtract(hit_point, cyl->cor, temp);
        proj = dot(temp, v);
        scale(v, proj, proj_vec);
        subtract(temp, proj_vec, lateral);
        normalize(lateral, normal);
    }
    else if (hit_part == 1)
	{ 
        normal[0] = v[0];
        normal[1] = v[1];
        normal[2] = v[2];
    }
    else if (hit_part == 2)
	{
        normal[0] = -v[0];
        normal[1] = -v[1];
        normal[2] = -v[2];
    }
}
