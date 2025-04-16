/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:40:21 by mhabbal           #+#    #+#             */
/*   Updated: 2024/06/13 11:39:52 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <stdlib.h>
#include <stdio.h>

int	validate(char **map, t_cor *cor)
{
	int		i;
	char	**line;
	t_val	*val;

	val = malloc(sizeof(t_val));
	if (!val)
		return (1);
	init_val(val);
	line = 0;
	if (validate3(val, line, map) == 1)
		return (1);
	free(val);
	i = -1;
	while (map[++i])
	{
		line = ft_split(map[i], ' ');
		if (validate2(line, cor) == 1)
			return (1);
	}
	return (0);
}

void	cross( float a[3], float b[3], float out[3])
{
	out[0] = a[1] * b[2] - a[2] * b[1];
	out[1] = a[2] * b[0] - a[0] * b[2];
	out[2] = a[0] * b[1] - a[1] * b[0];
}
