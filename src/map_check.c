/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:52:26 by msulc             #+#    #+#             */
/*   Updated: 2023/05/23 14:52:28 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	char_count_2(t_game *game, char *buf)
{
	int	i;

	game->c = 0;
	game->e = 0;
	game->p = 0;
	i = 0;
	while (buf[i])
	{
		if (buf[i] == 'C')
			game->c++;
		if (buf[i] == 'E')
			game->e++;
		if (buf[i] == 'P')
			game->p++;
		i++;
	}
	game->collectibles = game->c;
}

int	integrity_check(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '0' || buf[i] == 49 || buf[i] == 'E' || buf[i] == 'P'
			|| buf[i] == 'C' || buf[i] == '\n' || buf[i] == 'X')
			i++;
		else
			error_function(5);
	}
	return (0);
}

int	map_borders(t_map *map, char *buf)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (buf[i + k] != '\0' && j < map->hight)
	{
		i = 0;
		while (i < map->lenght)
		{
			if ((buf[i + k] != 49 && j == 0)
				|| (buf[i + k] != 49 && j == (map->hight - 1))
				|| buf[k] != 49 || buf[(map->lenght - 1) + k] != 49)
				error_function(4);
			i++;
		}
		j++;
		k += (map->lenght + 1);
	}
	return (0);
}

void	map_consistence(t_map *map, char *buf)
{
	map->hight = count_n(buf, 10);
	map->lenght = (map->total_char - map->hight) / map->hight;
	map->consistence = (map->total_char - \
	map->hight) % (map->lenght * map->hight);
	if (map->consistence != 0)
		error_function(4);
}

int	map_check(char *filename)
{
	int		fd;
	int		i;
	char	buf[2048 + 1];
	t_map	map;

	i = 0;
	while (i < 2049)
		buf[i++] = '\0';
	map_init(&map);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_function(2);
	map.total_char = read(fd, buf, 2048);
	buf[map.total_char] = '\0';
	close(fd);
	if (buf[0] == '\0')
		error_function(3);
	integrity_check(buf);
	map_consistence(&map, buf);
	map_borders(&map, buf);
	count_characters(buf);
	game_start(&map, buf);
	return (0);
}
