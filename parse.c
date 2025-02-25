#include "./miniRT.h"

void parse_scene(const char *filename, t_scene *scene) {
    int fd = open(filename, O_RDONLY);
    char line[256];
    
    if (fd < 0) {
        printf("Error: Cannot open scene file\n");
        exit(1);
    }

    scene->num_spheres = 0;
    scene->spheres = malloc(sizeof(t_sphere) * 10); // Max 10 spheres

    while (read(fd, line, 255)) {
        if (line[0] == 's' && line[1] == 'p') {
            double x, y, z, d;
            int r, g, b;
            sscanf(line, "sp %lf,%lf,%lf %lf %d,%d,%d", &x, &y, &z, &d, &r, &g, &b);
            scene->spheres[scene->num_spheres++] = (t_sphere){
                .center = {x, y, z},
                .radius = d / 2,
                .color = create_trgb(0, r, g, b)
            };
        }
		else if (line[0] == 'A') {  // Ambient light
			sscanf(line, "A %lf", &scene->ambient_intensity);
		} 
		else if (line[0] == 'L') {  // Light source
			double x, y, z, intensity;
			sscanf(line, "L %lf,%lf,%lf %lf", &x, &y, &z, &intensity);
			scene->light = (t_light){{x, y, z}, intensity};
		}
    }
    close(fd);
}

