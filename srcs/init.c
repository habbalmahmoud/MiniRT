#include "../includes/miniRT.h"

int	close_window(int keycode)
{
	if (keycode == 65307)
	{
		exit(0);
		/*return(0);*/
	}
	return (0);
}

int init(t_cor *scenee)
{
	(void)scenee;
	t_mlx mlx;
    t_cor scene;
    t_sp_list *sphere_node;
    t_pl_list *plane_node, *plane_node2;
	t_cy_list *cylinder_node;

    /* Initialize miniLibX */
    mlx.ptr = mlx_init();
    if (!mlx.ptr)
        return (1);
    mlx.win_ptr = mlx_new_window(mlx.ptr, WIDTH, HEIGHT, "miniRT");
    mlx.img = mlx_new_image(mlx.ptr, WIDTH, HEIGHT);
    mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel,
                                  &mlx.line_length, &mlx.endian);

    /* --- Setup Scene --- */
    /* Ambient lighting (ratio only; color used optionally for tint) */
    scene.am.am = 0.2f;
    scene.am.rgb[0] = 255;
    scene.am.rgb[1] = 255;
    scene.am.rgb[2] = 255;

    /* Camera: position, orientation and FOV */
    scene.cm.cor[0] = 0;
    scene.cm.cor[1] = 2;
    scene.cm.cor[2] = -5;
    scene.cm.vector[0] = 0;
    scene.cm.vector[1] = 0;
    scene.cm.vector[2] = 1;
    scene.cm.fov = 70;

    /* Light: position and brightness */
    scene.light.cor[0] = 6;
    scene.light.cor[1] = 7;
    scene.light.cor[2] = 5;
    scene.light.brightness = 0.9f;

    /* Sphere: create a single sphere and add it to the scene */
    sphere_node = malloc(sizeof(t_sp_list));
    if (!sphere_node)
        return (1);
    sphere_node->sphere.cor[0] = 0;
    sphere_node->sphere.cor[1] = 0;
    sphere_node->sphere.cor[2] = 10;
    sphere_node->sphere.diameter = 4;
    sphere_node->sphere.rgb[0] = 255;
    sphere_node->sphere.rgb[1] = 0;
    sphere_node->sphere.rgb[2] = 0;
    sphere_node->next = NULL;
    scene.spheres = sphere_node;

    /* Plane: create a plane and add it to the scene.
       For example, a plane that acts as a floor:
         - A point on the plane at (0, -2, 0)
         - A normal pointing upward (0, 1, 0)
         - A blue color {0, 0, 225} */
    plane_node = malloc(sizeof(t_pl_list));
    if (!plane_node)
        return (1);
    plane_node->plane.cor[0] = 0;
    plane_node->plane.cor[1] = -2;
    plane_node->plane.cor[2] = 0;
    plane_node->plane.vector[0] = 0;
    plane_node->plane.vector[1] = 1;
    plane_node->plane.vector[2] = 0;
    plane_node->plane.rgb[0] = 0;
    plane_node->plane.rgb[1] = 0;
    plane_node->plane.rgb[2] = 225;
    plane_node->next = NULL;

	plane_node2 = malloc(sizeof(t_pl_list));
    if (!plane_node2)
        return (1);
    plane_node2->plane.cor[0] = -3;
    plane_node2->plane.cor[1] = 0;
    plane_node2->plane.cor[2] = 0;
    /* This plane's normal points along +x, so it will form a vertical wall */
    plane_node2->plane.vector[0] = 1;
    plane_node2->plane.vector[1] = 0;
    plane_node2->plane.vector[2] = 0;
    plane_node2->plane.rgb[0] = 0;
    plane_node2->plane.rgb[1] = 225;
    plane_node2->plane.rgb[2] = 0;
    plane_node2->next = NULL;

	plane_node->next = plane_node2;
    scene.planes = plane_node;


cylinder_node = malloc(sizeof(t_cy_list));
    if (!cylinder_node)
        return (1);
    cylinder_node->cyl.cor[0] = 3;
    cylinder_node->cyl.cor[1] = 0;
    cylinder_node->cyl.cor[2] = 8;
    cylinder_node->cyl.vector[0] = 0;
    cylinder_node->cyl.vector[1] = 1;
    cylinder_node->cyl.vector[2] = 0;
    cylinder_node->cyl.cy_diameter = 2;
    cylinder_node->cyl.cy_height = 4;
    cylinder_node->cyl.rgb[0] = 150;
    cylinder_node->cyl.rgb[1] = 0;
    cylinder_node->cyl.rgb[2] = 150;
    cylinder_node->next = NULL;
    scene.cylinders = cylinder_node;


    /* Render the scene */
    render_scene(&mlx, &scene);

    /* Display the image */
    mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.img, 0, 0);

    /* Wait for key press (e.g., ESC) to exit cleanly */
    mlx_key_hook(mlx.win_ptr, close_window, 0);
    mlx_loop(mlx.ptr);

    return (0);


}
