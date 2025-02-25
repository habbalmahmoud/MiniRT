#include "../includes/miniRT.h"

void minirt(char **av)
{
    char **map;
    t_cor   *cor;
    /*t_mlx   mlx;*/
    cor = malloc(sizeof(t_cor));
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
		printf("a : %f r:%f g:%f b:%f \n", cor->am.am, cor->am.rgb[0], cor->am.rgb[1], cor->am.rgb[2]);
        
        free(cor);
    }
}
