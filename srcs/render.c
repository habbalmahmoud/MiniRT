#include "../includes/miniRT.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	gen_ray(t_ray_utils *ray_utils, t_cm *cam)
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

t_ray	generate_ray(int x, int y, t_cm *cam)
{
	t_ray_utils	ray_utils;

	gen_ray(&ray_utils, cam);
	cross(ray_utils.forward, ray_utils.up, ray_utils.right);
	normalize(ray_utils.right, ray_utils.right);
	cross(ray_utils.right, ray_utils.forward, ray_utils.true_up);
	normalize(ray_utils.true_up, ray_utils.true_up);
	ray_utils.fov_rad = cam->fov * (M_PI / 180.0f);
	ray_utils.aspect_ratio = (float)WIDTH / (float)HEIGHT;
	ray_utils.px = (2 * ((x + 0.5f) / WIDTH) - 1)
		* tan(ray_utils.fov_rad / 2) * ray_utils.aspect_ratio;
	ray_utils.py = (1 - 2 * ((y + 0.5f) / HEIGHT)) * tan(ray_utils.fov_rad / 2);
	scale(ray_utils.right, ray_utils.px, ray_utils.tmp);
	add(ray_utils.forward, ray_utils.tmp, ray_utils.dir);
	scale(ray_utils.true_up, ray_utils.py, ray_utils.tmp);
	add(ray_utils.dir, ray_utils.tmp, ray_utils.dir);
	normalize(ray_utils.dir, ray_utils.ray.dir);
	return (ray_utils.ray);
}

void	render_scene(t_mlx *mlx, t_cor *scene)
{
	t_render_utils	render_utils;

	render_utils.y = -1;
	while (++render_utils.y < HEIGHT)
	{
		render_utils.x = -1;
		while (++render_utils.x < WIDTH)
		{
			red_util1(scene, &render_utils);
			rend_util2(scene, &render_utils);
			rend_utils3(scene, &render_utils);
			if (render_utils.hit_type)
			{
				rend_utils5(&render_utils, scene);
				render_utils.b = (int)(render_utils.obj_color[2]
						* render_utils.intensity / 255);
				render_utils.color = create_trgb(0, render_utils.r,
						render_utils.g, render_utils.b);
			}
			put_pixel(mlx, render_utils.x, render_utils.y, render_utils.color);
		}
	}
}
