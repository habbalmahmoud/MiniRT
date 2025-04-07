#include "../includes/miniRT.h"

void minirt(char **av)
{
    char **map;
    t_cor   *cor;

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
		init(cor);	
        
        free(cor);
    }
}
