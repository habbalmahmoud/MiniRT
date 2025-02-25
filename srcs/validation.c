#include "../includes/miniRT.h"


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

#include <stdlib.h>
#include <stdio.h>

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
int check_sep(char s, char *c)
{
    int i;

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


/* Create a new sphere node */
t_sp_list *new_sphere(t_sp sphere)
{
    t_sp_list *node = malloc(sizeof(t_sp_list));
    if (!node)
    {
        perror("Failed to allocate sphere node");
        return (NULL);
    }
    node->sphere = sphere;
    node->next = NULL;
    return (node);
}

/* Append a sphere to the scene's sphere list */
void add_sphere(t_cor *cor, t_sp sphere)
{
    t_sp_list *node = new_sphere(sphere);
    t_sp_list *tmp;

    if (!node)
        return;
    if (cor->spheres == NULL)
    {
        cor->spheres = node;
        return;
    }
    tmp = cor->spheres;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

/* Create a new cylinder node */
t_cy_list *new_cylinder(t_cy cyl)
{
    t_cy_list *node = malloc(sizeof(t_cy_list));
    if (!node)
    {
        perror("Failed to allocate cylinder node");
        return (NULL);
    }
    node->cyl = cyl;
    node->next = NULL;
    return (node);
}

/* Append a cylinder to the scene's cylinder list */
void add_cylinder(t_cor *cor, t_cy cyl)
{
    t_cy_list *node = new_cylinder(cyl);
    t_cy_list *tmp;

    if (!node)
        return;
    if (cor->cylinders == NULL)
    {
        cor->cylinders = node;
        return;
    }
    tmp = cor->cylinders;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

/* Create a new plane node */
t_pl_list *new_plane(t_pl plane)
{
    t_pl_list *node = malloc(sizeof(t_pl_list));
    if (!node)
    {
        perror("Failed to allocate plane node");
        return (NULL);
    }
    node->plane = plane;
    node->next = NULL;
    return (node);
}

/* Append a plane to the scene's plane list */
void add_plane(t_cor *cor, t_pl plane)
{
    t_pl_list *node = new_plane(plane);
    t_pl_list *tmp;
    if (!node)
        return;
    if (cor->planes == NULL)
    {
        cor->planes = node;
        return;
    }
    tmp = cor->planes;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}


int check_dup(char **line, t_val *val)
{
    if ((!ft_strncmp(line[0], "A", ft_strlen(line[0])) || !ft_strncmp(line[0], "C", ft_strlen(line[0]))
        || !ft_strncmp(line[0], "L", ft_strlen(line[0])) || !ft_strncmp(line[0], "cy", ft_strlen(line[0]))
        || !ft_strncmp(line[0], "pl", ft_strlen(line[0])) || !ft_strncmp(line[0], "sp", ft_strlen(line[0]))
        || !ft_strncmp(line[0], "\0", ft_strlen(line[0])) || !ft_strncmp(line[0], "\n", ft_strlen(line[0]))))
    {
        if (line[0])
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
        }
    }
    else
        return (2);
    return (0);
}

float string_to_float(const char *str) {
    if (!str)
        return 0.0f;

    float result = 0.0f;
    float fraction = 0.0f;
    int sign = 1;
    int divisor = 1;
    int decimal_found = 0;

    while (ft_isspace(*str)) {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str) {
        if (ft_isdigit(*str)) {
            if (decimal_found) {
                fraction = fraction * 10 + (*str - '0');
                divisor *= 10;
            } else {
                result = result * 10 + (*str - '0');
            }
        } else if (*str == '.') {
            if (decimal_found) {
                break;
            }
            decimal_found = 1;
        } else {
            break;
        }
        str++;
    }

    result += fraction / divisor;
    return result * sign;
}

int is_all_digits(const char *str)
{
	int i;
    int f;

    f = 0;
	i = 0;
    if (!str || *str == '\0')
        return 0;

    while (*str)
	{
		if (*str == '.')
		{
			if (i > 0)
				return (3);
			i++;
		}
        else if (*str == '-')
		{
			if (f > 0)
				return (3);
			f++;
		}
        else if (!ft_isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

t_val *init_val(t_val *data)
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

int check_cor_a(char **line, t_cor *cor)
{
    char **rgb;

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

/* Camera parsing */
int check_cor_c(char **line, t_cor *cor)
{
    char **xyz;
    char **vector;

    if (twodsize(line) != 4)
    {
        printf("Error: Camera requires 3 arguments\n");
        return (1);
    }
    xyz = ft_split(line[1], ',');
    vector = ft_split(line[2], ',');
    if (twodsize(xyz) != 3 || twodsize(vector) != 3)
    {
        printf("Error: Camera coordinates and orientation must have 3 numbers each\n");
        freearray(xyz);
        freearray(vector);
        return (1);
    }
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

/* Light parsing */
int check_cor_l(char **line, t_cor *cor)
{
    char **xyz;

    if (twodsize(line) != 3)
    {
        printf("Error: Light requires 2 arguments\n");
        return (1);
    }
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
    freearray(xyz);
    return (0);
}

/* Sphere parsing: "sp <x,y,z> <diameter> <R,G,B>" */
int check_cor_sp(char **line, t_cor *cor)
{
    char **xyz;
    char **rgb;
    t_sp sphere;

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
    if (twodsize(rgb) != 3)
    {
        printf("Error: Sphere RGB must have 3 numbers\n");
        freearray(xyz);
        freearray(rgb);
        return (1);
    }
    sphere.cor[0] = string_to_float(xyz[0]);
    sphere.cor[1] = string_to_float(xyz[1]);
    sphere.cor[2] = string_to_float(xyz[2]);
    sphere.diameter = string_to_float(line[2]);
    sphere.rgb[0] = string_to_float(rgb[0]);
    sphere.rgb[1] = string_to_float(rgb[1]);
    sphere.rgb[2] = string_to_float(rgb[2]);
    freearray(xyz);
    freearray(rgb);
    add_sphere(cor, sphere);
    return (0);
}

/* Cylinder parsing: "cy <x,y,z> <x,y,z> <diameter> <height> <R,G,B>" */
int check_cor_cy(char **line, t_cor *cor)
{
    char **xyz;
    char **vector;
    char **rgb;
    t_cy cyl;

    if (twodsize(line) != 6)
    {
        printf("Error: Cylinder requires 5 arguments\n");
        return (1);
    }
    xyz = ft_split(line[1], ',');
    vector = ft_split(line[2], ',');
    rgb = ft_split(line[5], ',');
    if (twodsize(xyz) != 3 || twodsize(vector) != 3 || twodsize(rgb) != 3)
    {
        printf("Error: Cylinder: coordinates, axis, and RGB must have 3 numbers each\n");
        freearray(xyz);
        freearray(vector);
        freearray(rgb);
        return (1);
    }
    cyl.cor[0] = string_to_float(xyz[0]);
    cyl.cor[1] = string_to_float(xyz[1]);
    cyl.cor[2] = string_to_float(xyz[2]);
    cyl.vector[0] = string_to_float(vector[0]);
    cyl.vector[1] = string_to_float(vector[1]);
    cyl.vector[2] = string_to_float(vector[2]);
    cyl.cy_diameter = string_to_float(line[3]);
    cyl.cy_height = string_to_float(line[4]);
    cyl.rgb[0] = string_to_float(rgb[0]);
    cyl.rgb[1] = string_to_float(rgb[1]);
    cyl.rgb[2] = string_to_float(rgb[2]);
    freearray(xyz);
    freearray(vector);
    freearray(rgb);
    add_cylinder(cor, cyl);
    return (0);
}

/* Plane parsing: "pl <x,y,z> <x,y,z> <R,G,B>" */
int check_cor_pl(char **line, t_cor *cor)
{
    char **xyz;
    char **vector;
    char **rgb;
    t_pl plane;

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
    if (twodsize(xyz) != 3 || twodsize(vector) != 3 || twodsize(rgb) != 3)
    {
        printf("Error: Plane: point, normal, and RGB must have 3 values each\n");
        freearray(xyz);
        freearray(vector);
        freearray(rgb);
        return (1);
    }
    plane.cor[0] = string_to_float(xyz[0]);
    plane.cor[1] = string_to_float(xyz[1]);
    plane.cor[2] = string_to_float(xyz[2]);
    plane.vector[0] = string_to_float(vector[0]);
    plane.vector[1] = string_to_float(vector[1]);
    plane.vector[2] = string_to_float(vector[2]);
    /* Normalize the normal vector immediately */
    /*normalize(plane.vector);*/
    plane.rgb[0] = string_to_float(rgb[0]);
    plane.rgb[1] = string_to_float(rgb[1]);
    plane.rgb[2] = string_to_float(rgb[2]);
    freearray(xyz);
    freearray(vector);
    freearray(rgb);
    add_plane(cor, plane);
    return (0);
}


/*
** Unified check_cor() calls the proper parser based on the element identifier.
*/
int check_cor(char **line, t_cor *cor)
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
    else if (ft_strncmp(line[0], "sp", ft_strlen(line[0])) == 0)
    {   if (check_cor_sp(line, cor) == 1)
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

/*
** Unified validation function.
** First, it loops over all lines to check for duplicates in A, C, and L.
** Then it loops again to parse each line into the scene (t_cor).
*/
int validate(char **map, t_cor *cor)
{
    int i;
    char **line;
    t_val *val = malloc(sizeof(t_val));
    if (!val)
        return (1);
    init_val(val);
    i = 0;
    while (map[i])
    {
        line = ft_split(map[i], ' ');
        // if(twodsize(line) > 1)
        // {
        //     // i++;
        //     // continue;
        //     printf("%s\n", line[i]);
        // }
        // printf("%s\ndddd", line[0]);
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
        i++;
    }
    if (val->a == false || val->c == false || val->l == false)
    {
        printf("Error: Missing ambient, camera, or light element!\n");
        free(val);
        return (1);
    }
    free(val);
    
    
    i = 0;
    while (map[i])
    {
        line = ft_split(map[i], ' ');
        int j = 0;
        while (line[j])
        {
            int k = 0;
            while(line[j][k])
            {
                if ((line[j][k] >= 7 && line[j][k] <= 13) && line[j][k] != '\n')
                {
                    printf("Unknown element\n");
                    return(1);
                }
                k++;
            }
            j++;
        }
        if (check_cor(line, cor) == 1)
        {
            freearray(line);
            return (1);
        }
        freearray(line);
        i++;
    }
    return (0);
}
