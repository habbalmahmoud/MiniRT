#include "../includes/miniRT.h"

int main(int ac, char **av)
{
	if (ac != 2)
		printf("Error\nOnly 2 Arguments Required !\n");
	else
		minirt(av);
	return (0);
}