/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:03:22 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 15:19:27 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_sp_list	*new_sphere(t_sp sphere)
{
	t_sp_list	*node;

	node = malloc(sizeof(t_sp_list));
	if (!node)
	{
		perror("Failed to allocate sphere node");
		return (NULL);
	}
	node->sphere = sphere;
	node->next = NULL;
	return (node);
}

void	add_sphere(t_cor *cor, t_sp sphere)
{
	t_sp_list	*node;
	t_sp_list	*tmp;

	node = new_sphere(sphere);
	if (!node)
		return ;
	if (cor->spheres == NULL)
	{
		cor->spheres = node;
		return ;
	}
	tmp = cor->spheres;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_cy_list	*new_cylinder(t_cy cyl)
{
	t_cy_list	*node;

	node = malloc(sizeof(t_cy_list));
	if (!node)
	{
		perror("Failed to allocate cylinder node");
		return (NULL);
	}
	node->cyl = cyl;
	node->next = NULL;
	return (node);
}

void	add_cylinder(t_cor *cor, t_cy cyl)
{
	t_cy_list	*node;
	t_cy_list	*tmp;

	node = new_cylinder(cyl);
	if (!node)
		return ;
	if (cor->cylinders == NULL)
	{
		cor->cylinders = node;
		return ;
	}
	tmp = cor->cylinders;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_pl_list	*new_plane(t_pl plane)
{
	t_pl_list	*node;

	node = malloc(sizeof(t_pl_list));
	if (!node)
	{
		perror("Failed to allocate plane node");
		return (NULL);
	}
	node->plane = plane;
	node->next = NULL;
	return (node);
}
