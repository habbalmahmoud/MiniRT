#include "../includes/miniRT.h"


void init_cor(t_cor *cor)
{
	cor->light.cor[0] = 0;
	cor->light.cor[1] = 0;
	cor->light.cor[2] = 0;
	cor->light.rgb[0] = 0;
	cor->light.rgb[1] = 0;
	cor->light.rgb[2] = 0;
	cor->light.brightness = 0;
	cor->planes = malloc(sizeof(t_pl_list));
	cor->planes->plane.cor[0] = 0;
	cor->planes->plane.cor[1] = 0;
	cor->planes->plane.cor[2] = 0;
	cor->planes->plane.rgb[0] = 0;
	cor->planes->plane.rgb[1] = 0;
	cor->planes->plane.rgb[2] = 0;
	cor->planes->plane.vector[0] = 0;
	cor->planes->plane.vector[1] = 0;
	cor->planes->plane.vector[2] = 0;
	cor->planes->next = NULL;
	cor->am.am = 0;
	cor->am.rgb[0] = 0;
	cor->am.rgb[1] = 0;
	cor->am.rgb[2] = 0;
	cor->cm.cor[0] = 0;
	cor->cm.cor[1] = 0;
	cor->cm.cor[2] = 0;
	cor->cm.fov = 0;
	cor->cm.vector[0] = 0;
	cor->cm.vector[1] = 0;
	cor->cm.vector[2] = 0;
	cor->cylinders = malloc(sizeof(t_cy_list));
	cor->cylinders->cyl.cor[0] = 0;
	cor->cylinders->cyl.cor[1] = 0;
	cor->cylinders->cyl.cor[2] = 0;
	cor->cylinders->cyl.vector[0] = 0;
	cor->cylinders->cyl.vector[1] = 0;
	cor->cylinders->cyl.vector[2] = 0;
	cor->cylinders->cyl.rgb[0] = 0;
	cor->cylinders->cyl.rgb[1] = 0;
	cor->cylinders->cyl.rgb[2] = 0;
	cor->cylinders->cyl.cy_diameter = 0;
	cor->cylinders->cyl.cy_height = 0;
	cor->cylinders->next = NULL;
	cor->spheres = malloc(sizeof(t_sp_list));
	cor->spheres->sphere.cor[0] = 0;
	cor->spheres->sphere.cor[1] = 0;
	cor->spheres->sphere.cor[2] = 0;
	cor->spheres->sphere.rgb[0] = 0;
	cor->spheres->sphere.rgb[1] = 0;
	cor->spheres->sphere.rgb[2] = 0;
	cor->spheres->sphere.diameter = 0;
	cor->spheres->next = NULL;
}



void minirt(char **av)
{
    char **map;
    t_cor   *cor;
    /*t_mlx   mlx;*/
    cor = malloc(sizeof(t_cor));
	init_cor(cor);
    if ((map = checking_the_map(av[1])) == NULL)
        free(cor);
    else if (validate(map, cor) == 1)
    {
        freearray(map);
        free(cor);
    }
    else
    {
        freearray(map);
		init(cor);	
        
        free(cor);
    }
}
