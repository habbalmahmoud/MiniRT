/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:06:03 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 15:19:38 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	digits_utils(const char *str, int *i, int *f)
{
	if (*str == '.')
	{
		if (*i > 0)
			return (3);
		*i = *i + 1;
	}
	else if (*str == '-')
	{
		if (*f > 0)
			return (3);
		*f = *f + 1;
	}
	return (0);
}

int	is_all_digits(const char *str)
{
	int	i;
	int	f;

	f = 0;
	i = 0;
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (digits_utils(str, &i, &f) == 3)
			return (3);
		else if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

t_val	*init_val(t_val *data)
{
	if (!data)
		return (NULL);
	data->a = false;
	data->c = false;
	data->l = false;
	data->sp = false;
	data->cy = false;
	data->pl = false;
	return (data);
}

int	check_cor_a(char **line, t_cor *cor)
{
	char	**rgb;

	if (twodsize(line) != 3)
	{
		printf("Error: Ambient Light requires 2 arguments\n");
		return (1);
	}
	rgb = ft_split(line[2], ',');
	if (twodsize(rgb) != 3)
	{
		printf("Error: Ambient Light RGB must have 3 numbers\n");
		freearray(rgb);
		return (1);
	}
	cor->am.am = string_to_float(line[1]);
	cor->am.rgb[0] = string_to_float(rgb[0]);
	cor->am.rgb[1] = string_to_float(rgb[1]);
	cor->am.rgb[2] = string_to_float(rgb[2]);
	freearray(rgb);
	return (0);
}

int	check_c_util(char **line)
{
	if (twodsize(line) != 4)
	{
		printf("Error: Camera requires 3 arguments\n");
		return (1);
	}
	return (0);
}
