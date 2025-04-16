/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:08:51 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 15:19:50 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	check_cor_util(char **line, t_cor *cor)
{
	if (ft_strncmp(line[0], "A", ft_strlen(line[0])) == 0)
	{
		if (check_cor_a(line, cor) == 1)
			return (1);
	}
	else if (ft_strncmp(line[0], "C", ft_strlen(line[0])) == 0)
	{
		if (check_cor_c(line, cor) == 1)
			return (1);
	}
	else if (ft_strncmp(line[0], "L", ft_strlen(line[0])) == 0)
	{
		if (check_cor_l(line, cor) == 1)
			return (1);
	}
	return (0);
}

int	check_cor(char **line, t_cor *cor)
{
	if (check_cor_util(line, cor) == 1)
		return (1);
	else if (ft_strncmp(line[0], "sp", ft_strlen(line[0])) == 0)
	{
		if (check_cor_sp(line, cor) == 1)
			return (1);
	}
	else if (ft_strncmp(line[0], "cy", ft_strlen(line[0])) == 0)
	{
		if (check_cor_cy(line, cor) == 1)
			return (1);
	}
	else if (ft_strncmp(line[0], "pl", ft_strlen(line[0])) == 0)
	{
		if (check_cor_pl(line, cor) == 1)
			return (1);
	}
	return (0);
}

int	validate1(char **line, t_val *val)
{
	if (check_dup(line, val) == 1)
	{
		freearray(line);
		free(val);
		printf("Error: Duplicate A, C, or L element found!\n");
		return (1);
	}
	else if (check_dup(line, val) == 2)
	{
		printf("Error: Unknown element: %s\n", line[0]);
		freearray(line);
		free(val);
		return (1);
	}
	freearray(line);
	return (0);
}

int	validate2(char **line, t_cor *cor)
{
	int	j;
	int	k;

	j = -1;
	while (line[++j])
	{
		k = -1;
		while (line[j][++k])
		{
			if ((line[j][k] >= 7 && line[j][k] <= 13) && line[j][k] != '\n')
			{
				printf("Unknown element\n");
				return (1);
			}
		}
	}
	if (check_cor(line, cor) == 1)
	{
		freearray(line);
		return (1);
	}
	freearray(line);
	return (0);
}

int	validate3(t_val *val, char **line, char **map)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		line = ft_split(map[i], ' ');
		if (validate1(line, val) == 1)
			return (1);
	}
	if (val->a == false || val->c == false || val->l == false)
	{
		printf("Error: Missing ambient, camera, or light element!\n");
		free(val);
		return (1);
	}
	return (0);
}
