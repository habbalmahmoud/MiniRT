#include "./miniRT.h"

int main(int argc, char **argv) {
    t_scene scene;

    if (argc != 2) {
        printf("Usage: ./miniRT <scene.rt>\n");
        return 1;
    }

    parse_scene(argv[1], &scene);

    scene.width = 800;
    scene.height = 600;
    scene.camera = (t_camera){{0, 0, -50}, {0, 0, 1}, 70};

    scene.mlx.mlx = mlx_init();
    scene.mlx.win = mlx_new_window(scene.mlx.mlx, scene.width, scene.height, "miniRT - Spheres");

    render_scene(&scene);

    mlx_loop(scene.mlx.mlx);
    return 0;
}

