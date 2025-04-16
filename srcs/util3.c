/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:03:44 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 15:19:32 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	add_plane(t_cor *cor, t_pl plane)
{
	t_pl_list	*node;
	t_pl_list	*tmp;

	node = new_plane(plane);
	if (!node)
		return ;
	if (cor->planes == NULL)
	{
		cor->planes = node;
		return ;
	}
	tmp = cor->planes;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int	check_dup_util(char **line, t_val *val)
{
	if (!ft_strncmp(line[0], "A", ft_strlen(line[0])) && val->a == true)
		return (1);
	else if (!ft_strncmp(line[0], "A", ft_strlen(line[0])) && val->a == false)
		val->a = true;
	else if (!ft_strncmp(line[0], "C", ft_strlen(line[0])) && val->c == true)
		return (1);
	else if (!ft_strncmp(line[0], "C", ft_strlen(line[0])) && val->c == false)
		val->c = true;
	else if (!ft_strncmp(line[0], "L", ft_strlen(line[0])) && val->l == true)
		return (1);
	else if (!ft_strncmp(line[0], "L", ft_strlen(line[0])) && val->l == false)
		val->l = true;
	else if (!ft_strncmp(line[0], "cy", ft_strlen(line[0])) && val->cy == false)
		val->cy = true;
	else if (!ft_strncmp(line[0], "sp", ft_strlen(line[0])) && val->sp == false)
		val->sp = true;
	else if (!ft_strncmp(line[0], "pl", ft_strlen(line[0])) && val->pl == false)
		val->pl = true;
	return (0);
}

int	check_dup(char **line, t_val *val)
{
	if ((!ft_strncmp(line[0], "A", ft_strlen(line[0]))
			|| !ft_strncmp(line[0], "C", ft_strlen(line[0]))
			|| !ft_strncmp(line[0], "L", ft_strlen(line[0]))
			|| !ft_strncmp(line[0], "cy", ft_strlen(line[0]))
			|| !ft_strncmp(line[0], "pl", ft_strlen(line[0]))
			|| !ft_strncmp(line[0], "sp", ft_strlen(line[0]))
			|| !ft_strncmp(line[0], "\0", ft_strlen(line[0]))
			|| !ft_strncmp(line[0], "\n", ft_strlen(line[0]))))
	{
		if (line[0])
			if (check_dup_util(line, val) == 1)
				return (1);
	}
	else
		return (2);
	return (0);
}

void	stf_util(const char *str, t_stf_utils *stf_utils)
{
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			if (stf_utils->decimal_found)
			{
				stf_utils->fraction = stf_utils->fraction * 10 + (*str - '0');
				stf_utils->divisor *= 10;
			}
			else
				stf_utils->result = stf_utils->result * 10 + (*str - '0');
		}
		else if (*str == '.')
		{
			if (stf_utils->decimal_found)
				break ;
			stf_utils->decimal_found = 1;
		}
		else
			break ;
		str++;
	}
}

float	string_to_float(const char *str)
{
	t_stf_utils	stf_utils;	

	if (!str)
		return (0.0f);
	stf_utils.result = 0.0f;
	stf_utils.fraction = 0.0f;
	stf_utils.sign = 1;
	stf_utils.divisor = 1;
	stf_utils.decimal_found = 0;
	while (ft_isspace(*str))
	{
		str++;
	}
	if (*str == '-')
	{
		stf_utils.sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	stf_util(str, &stf_utils);
	stf_utils.result += stf_utils.fraction / stf_utils.divisor;
	return (stf_utils.result * stf_utils.sign);
}
