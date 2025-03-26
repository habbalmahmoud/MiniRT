#include "../includes/miniRT.h"

float intersect_cylinder(t_ray ray, t_cy *cylinder, int *hit_part)
{
	t_cy_utils cy_utils;
    normalize(cylinder->vector, cy_utils.v);
    cy_utils.r = cylinder->cy_diameter * 0.5f;
    cy_utils.h = cylinder->cy_height;
    cy_utils.half_h = cy_utils.h * 0.5f;
    subtract(ray.orig, cylinder->cor, cy_utils.delta);

    // Compute components perpendicular to the cylinder's axis.
    cy_utils.D_dot_v = dot(ray.dir, cy_utils.v);
    cy_utils.delta_dot_v = dot(cy_utils.delta, cy_utils.v);
    scale(cy_utils.v, cy_utils.D_dot_v, cy_utils.temp);
    subtract(ray.dir, cy_utils.temp, cy_utils.D_perp);
    scale(cy_utils.v, cy_utils.delta_dot_v, cy_utils.temp);
    subtract(cy_utils.delta, cy_utils.temp, cy_utils.delta_perp);

    cy_utils.A = dot(cy_utils.D_perp, cy_utils.D_perp);
    cy_utils.B = 2.0f * dot(cy_utils.D_perp, cy_utils.delta_perp);
    cy_utils.C_val = dot(cy_utils.delta_perp, cy_utils.delta_perp) - cy_utils.r*cy_utils.r;

    cy_utils.t_lateral = -1.0f;
    if (fabs(cy_utils.A) > 1e-6) {
        cy_utils.discriminant = cy_utils.B*cy_utils.B - 4*cy_utils.A*cy_utils.C_val;
        if (cy_utils.discriminant >= 0) {
            cy_utils.sqrt_disc = sqrt(cy_utils.discriminant);
            cy_utils.t1 = (-cy_utils.B - cy_utils.sqrt_disc) / (2*cy_utils.A);
            cy_utils.t2 = (-cy_utils.B + cy_utils.sqrt_disc) / (2*cy_utils.A);
            cy_utils.t_lateral = 1e30;
            if (cy_utils.t1 > 0.001f) {
                scale(ray.dir, cy_utils.t1, cy_utils.tempP);
                add(ray.orig, cy_utils.tempP, cy_utils.P);
                subtract(cy_utils.P, cylinder->cor, cy_utils.temp_vec);
                cy_utils.proj = dot(cy_utils.temp_vec, cy_utils.v);
                if (fabs(cy_utils.proj) <= cy_utils.half_h && cy_utils.t1 < cy_utils.t_lateral)
                    cy_utils.t_lateral = cy_utils.t1;
            }
            if (cy_utils.t2 > 0.001f) {
                scale(ray.dir, cy_utils.t2, cy_utils.tempP);
                add(ray.orig, cy_utils.tempP, cy_utils.P);
                subtract(cy_utils.P, cylinder->cor, cy_utils.temp_vec);
                cy_utils.proj = dot(cy_utils.temp_vec, cy_utils.v);
                if (fabs(cy_utils.proj) <= cy_utils.half_h && cy_utils.t2 < cy_utils.t_lateral)
                    cy_utils.t_lateral = cy_utils.t2;
            }
            if (cy_utils.t_lateral == 1e30)
                cy_utils.t_lateral = -1.0f;
        }
    }

    // Compute cap intersections.
    scale(cy_utils.v, cy_utils.half_h, cy_utils.half_v);
    add(cylinder->cor, cy_utils.half_v, cy_utils.top_center);
    subtract(cylinder->cor, cy_utils.half_v, cy_utils.bottom_center);

    cy_utils.t_top = -1.0f, cy_utils.t_bottom = -1.0f;
    cy_utils.denom = dot(ray.dir, cy_utils.v);
    if (fabs(cy_utils.denom) > 1e-6) {
        // Top cap
        subtract(cy_utils.top_center, ray.orig, cy_utils.temp_vec);
        cy_utils.t_top = dot(cy_utils.temp_vec, cy_utils.v) / cy_utils.denom;
        if (cy_utils.t_top > 0.001f) {
            scale(ray.dir, cy_utils.t_top, cy_utils.temp);
            add(ray.orig, cy_utils.temp, cy_utils.P);
            subtract(cy_utils.P, cy_utils.top_center, cy_utils.diff);
            if (sqrt(dot(cy_utils.diff, cy_utils.diff)) > cy_utils.r)
                cy_utils.t_top = -1.0f;
        } else {
            cy_utils.t_top = -1.0f;
        }
        // Bottom cap
        subtract(cy_utils.bottom_center, ray.orig, cy_utils.temp_vec);
        cy_utils.t_bottom = dot(cy_utils.temp_vec, cy_utils.v) / cy_utils.denom;
        if (cy_utils.t_bottom > 0.001f) {
            scale(ray.dir, cy_utils.t_bottom, cy_utils.temp);
            add(ray.orig, cy_utils.temp, cy_utils.P);
            subtract(cy_utils.P, cy_utils.bottom_center, cy_utils.diff);
            if (sqrt(dot(cy_utils.diff, cy_utils.diff)) > cy_utils.r)
                cy_utils.t_bottom = -1.0f;
        } else {
            cy_utils.t_bottom = -1.0f;
        }
    }

    // Choose the smallest positive t among lateral, top cap, and bottom cap.
    cy_utils.t_final = 1e30;
    cy_utils.part = -1;
    if (cy_utils.t_lateral > 0 && cy_utils.t_lateral < cy_utils.t_final) {
        cy_utils.t_final = cy_utils.t_lateral;
        cy_utils.part = 0; // lateral surface
    }
    if (cy_utils.t_top > 0 && cy_utils.t_top < cy_utils.t_final) {
        cy_utils.t_final = cy_utils.t_top;
        cy_utils.part = 1; // top cap
    }
    if (cy_utils.t_bottom > 0 && cy_utils.t_bottom < cy_utils.t_final) {
        cy_utils.t_final = cy_utils.t_bottom;
        cy_utils.part = 2; // bottom cap
    }
    if (cy_utils.t_final == 1e30)
        return -1.0f;
    *hit_part = cy_utils.part;
    return cy_utils.t_final;
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
