/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:55:13 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 09:55:13 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	minirt(char **av)
{
	char	**map;
	t_cor	*cor;

	cor = malloc(sizeof(t_cor));
	map = checking_the_map(av[1]);
	if (map == NULL)
	{
		free(cor);
	}
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
