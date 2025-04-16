/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:06:44 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 15:19:42 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	check_c_util_2(char **xyz, char **vector)
{
	if (twodsize(xyz) != 3 || twodsize(vector) != 3)
	{
		printf("Error: Camera coordinates and orientation ");
		printf("must have 3 numbers each\n");
		freearray(xyz);
		freearray(vector);
		return (1);
	}
	return (0);
}

int	check_cor_c(char **line, t_cor *cor)
{
	char	**xyz;
	char	**vector;

	if (check_c_util(line) == 1)
		return (1);
	xyz = ft_split(line[1], ',');
	vector = ft_split(line[2], ',');
	if (check_c_util_2(xyz, vector) == 1)
		return (1);
	cor->cm.cor[0] = string_to_float(xyz[0]);
	cor->cm.cor[1] = string_to_float(xyz[1]);
	cor->cm.cor[2] = string_to_float(xyz[2]);
	cor->cm.vector[0] = string_to_float(vector[0]);
	cor->cm.vector[1] = string_to_float(vector[1]);
	cor->cm.vector[2] = string_to_float(vector[2]);
	cor->cm.fov = string_to_float(line[3]);
	freearray(xyz);
	freearray(vector);
	return (0);
}

int	check_l_util(char **line)
{
	if (twodsize(line) != 4)
	{
		printf("Error: Light requires 2 arguments\n");
		return (1);
	}
	return (0);
}

int	check_cor_l(char **line, t_cor *cor)
{
	char	**xyz;
	char	**rgb;

	if (check_l_util(line) == 1)
		return (1);
	xyz = ft_split(line[1], ',');
	if (twodsize(xyz) != 3)
	{
		printf("Error: Light coordinates must have 3 numbers\n");
		freearray(xyz);
		return (1);
	}
	cor->light.cor[0] = string_to_float(xyz[0]);
	cor->light.cor[1] = string_to_float(xyz[1]);
	cor->light.cor[2] = string_to_float(xyz[2]);
	cor->light.brightness = string_to_float(line[2]);
	rgb = ft_split(line[3], ',');
	cor->light.rgb[0] = string_to_float(rgb[0]);
	cor->light.rgb[1] = string_to_float(rgb[1]);
	cor->light.rgb[2] = string_to_float(rgb[2]);
	freearray(xyz);
	freearray(rgb);
	return (0);
}

int	check_sp_util(char **xyz, char **rgb, t_sp *sphere, t_cor *cor)
{
	if (twodsize(rgb) != 3)
	{
		printf("Error: Sphere RGB must have 3 numbers\n");
		freearray(xyz);
		freearray(rgb);
		return (1);
	}
	sphere->cor[0] = string_to_float(xyz[0]);
	sphere->cor[1] = string_to_float(xyz[1]);
	sphere->cor[2] = string_to_float(xyz[2]);
	sphere->rgb[0] = string_to_float(rgb[0]);
	sphere->rgb[1] = string_to_float(rgb[1]);
	sphere->rgb[2] = string_to_float(rgb[2]);
	freearray(xyz);
	freearray(rgb);
	add_sphere(cor, *sphere);
	return (0);
}
