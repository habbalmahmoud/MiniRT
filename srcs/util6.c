/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:07:21 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 15:19:44 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	check_cor_sp(char **line, t_cor *cor)
{
	char	**xyz;
	char	**rgb;
	t_sp	sphere;

	if (twodsize(line) != 4)
	{
		printf("Error: Sphere requires 3 arguments\n");
		return (1);
	}
	xyz = ft_split(line[1], ',');
	if (twodsize(xyz) != 3)
	{
		printf("Error: Sphere center must have 3 numbers\n");
		freearray(xyz);
		return (1);
	}
	rgb = ft_split(line[3], ',');
	sphere.diameter = string_to_float(line[2]);
	if (check_sp_util(xyz, rgb, &sphere, cor) == 1)
		return (1);
	return (0);
}

int	check_cy_util(char **xyz, char **vector, char **rgb, t_cy *cyl)
{
	if (twodsize(xyz) != 3 || twodsize(vector) != 3 || twodsize(rgb) != 3)
	{
		printf("Error: Cylinder: coordinates, axis, ");
		printf("and RGB must have 3 numbers each\n");
		freearray(xyz);
		freearray(vector);
		freearray(rgb);
		return (1);
	}
	cyl->cor[0] = string_to_float(xyz[0]);
	cyl->cor[1] = string_to_float(xyz[1]);
	cyl->cor[2] = string_to_float(xyz[2]);
	cyl->vector[0] = string_to_float(vector[0]);
	cyl->vector[1] = string_to_float(vector[1]);
	cyl->vector[2] = string_to_float(vector[2]);
	cyl->rgb[0] = string_to_float(rgb[0]);
	cyl->rgb[1] = string_to_float(rgb[1]);
	cyl->rgb[2] = string_to_float(rgb[2]);
	return (0);
}

int	check_cor_cy(char **line, t_cor *cor)
{
	char	**xyz;
	char	**vector;
	char	**rgb;
	t_cy	cyl;

	if (twodsize(line) != 6)
	{
		printf("Error: Cylinder requires 5 arguments\n");
		return (1);
	}
	xyz = ft_split(line[1], ',');
	vector = ft_split(line[2], ',');
	rgb = ft_split(line[5], ',');
	if (check_cy_util(xyz, vector, rgb, &cyl) == 1)
		return (1);
	cyl.cy_diameter = string_to_float(line[3]);
	cyl.cy_height = string_to_float(line[4]);
	freearray(xyz);
	freearray(vector);
	freearray(rgb);
	add_cylinder(cor, cyl);
	return (0);
}

int	check_pl_util(char **xyz, char **vector, char **rgb, t_pl *plane)
{
	if (twodsize(xyz) != 3 || twodsize(vector) != 3 || twodsize(rgb) != 3)
	{
		printf("Error: Plane: point, normal, and RGB must have 3 values each\n");
		freearray(xyz);
		freearray(vector);
		freearray(rgb);
		return (1);
	}
	plane->cor[0] = string_to_float(xyz[0]);
	plane->cor[1] = string_to_float(xyz[1]);
	plane->cor[2] = string_to_float(xyz[2]);
	plane->vector[0] = string_to_float(vector[0]);
	plane->vector[1] = string_to_float(vector[1]);
	plane->vector[2] = string_to_float(vector[2]);
	plane->rgb[0] = string_to_float(rgb[0]);
	plane->rgb[1] = string_to_float(rgb[1]);
	plane->rgb[2] = string_to_float(rgb[2]);
	freearray(xyz);
	freearray(vector);
	freearray(rgb);
	return (0);
}

int	check_cor_pl(char **line, t_cor *cor)
{
	char	**xyz;
	char	**vector;
	char	**rgb;
	t_pl	plane;

	if (ft_strlen(line[0]) == 0 || ft_strncmp(line[0], "pl", 2) != 0)
	{
		printf("Error: Not a plane line.\n");
		return (1);
	}
	if (twodsize(line) != 4)
	{
		printf("Error: Plane requires 3 arguments: point, normal, and RGB\n");
		return (1);
	}
	xyz = ft_split(line[1], ',');
	vector = ft_split(line[2], ',');
	rgb = ft_split(line[3], ',');
	if (check_pl_util(xyz, vector, rgb, &plane))
		return (1);
	add_plane(cor, plane);
	return (0);
}
