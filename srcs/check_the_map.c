#include "../includes/miniRT.h"
#include <fcntl.h>

int fill_map(int fd, char **map)
{
    char *line;
    int i;

    i = 0;
    line = get_next_line(fd);
	while (line != NULL)
    {
        map[i] = line;
        i++;
        line = get_next_line(fd);
    }
    map[i] = NULL;
    if (map[0] == NULL)
    {
        free(map);
        printf("Error : Empty Map\n");
        return (1);
    }
    free(line);
    return (0);
}

int count_lines(int fd)
{
    char *line;
    int i;

    i = 0;
    line = get_next_line(fd);
    while (line != NULL)
    {
        i++;
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    return (i);
}

void change_new_line(char **map)
{
    int i = 0;
    while(map[i])
    {
        if (ft_strlen(map[i]) > 1 && map[i][ft_strlen(map[i]) - 1] == '\n')
            map[i][ft_strlen(map[i]) - 1] = '\0';
        i++;
    }
}

char **checking_the_map(char *str)
{
    int str_len;
    char *substr;
    int fd;
    int fd_cpy;
    char **map;

    str_len = ft_strlen(str);
    substr = ft_substr(str, str_len - 3, 3);
    if (ft_strncmp(substr, ".rt", 3) != 0)
    {
        free(substr);
        exit(printf("Error\nWrong Extension\n"));
    }
    free(substr);
    fd = open(str, O_RDONLY);
    fd_cpy = open(str, O_RDONLY);
    if (fd < 0 || fd_cpy < 0)
        exit(printf("Error reading the file!\n"));
    map = malloc((count_lines(fd_cpy) + 1) * sizeof(char *));
    if (!map)
        return (NULL);
    if (fill_map(fd, map) == 1)
        return (NULL);
    change_new_line(map);
    return (map);
}
