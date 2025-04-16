/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:02:46 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 15:19:20 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	assign_bbig(char *sub_big, size_t *i, size_t *j, char const *s)
{
	size_t	m;

	m = 0;
	while (*i < *j)
	{
		sub_big[m] = s[*i];
		m++;
		*i = *i + 1;
	}
	sub_big[m] = '\0';
}

int	check_sep(char s, char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (s == c[i])
			return (1);
		i++;
	}
	return (0);
}

void	fill_bbig(char **big, char const *s, char *c)
{
	size_t	i;
	size_t	j;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (check_sep(s[i], c))
			i++;
		if (s[i] == '\0')
			return ;
		j = i;
		while (!check_sep(s[i], c))
		{
			if (s[j] == '\0')
				break ;
			j++;
		}
		big[counter] = (char *)malloc(((j - i) + 1));
		assign_bbig(big[counter], &i, &j, s);
		counter++;
	}
}

size_t	ccount_words(char const *s, char *c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (check_sep(s[i], c) == 1)
			i++;
		if (s[i] == '\0')
			break ;
		while (!check_sep(s[i], c))
		{
			if (s[i] == '\0')
				break ;
			i++;
		}
		words++;
	}
	return (words);
}

char	**ftt_split(char const *s, char *c)
{
	size_t	biglen;
	char	**big;

	biglen = ccount_words(s, c);
	big = (char **)malloc((biglen + 1) * sizeof(char *));
	if (big == NULL)
		return (NULL);
	fill_bbig(big, s, c);
	big[biglen] = NULL;
	return (big);
}
