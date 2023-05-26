/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:48:10 by msulc             #+#    #+#             */
/*   Updated: 2023/05/23 14:48:41 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/so_long.h"

void	map_init(t_map *map)
{
	map->total_char = 0;
	map->lenght = 0;
	map->hight = 0;
	map->consistence = 0;
}

void	game_init(t_game *game)
{
	game->coll = (t_coll *)malloc(sizeof(t_coll));
	if (!game->coll)
		exit(1);
	game->coll->pos_x = 0;
	game->coll->pos_y = 0;
	game->coll->o = 0;
	game->w = 0;
	game->h = 0;
	game->e = 0;
	game->p = 0;
	game->c = 0;
	game->collectibles = 0;
	game->p_pos_h = 0;
	game->p_pos_l = 0;
	game->flood_c = 0;
	game->flood_e = 0;
	game->count = 0;
}

int	game_start(t_map *map, char *buf)
{
	t_game	game;

	game_init(&game);
	game.w = map->lenght;
	game.h = map->hight;
	char_count_2(&game, buf);
	game.grid = ft_split(buf, '\n');
	path_finder(&game);
	game.grid = ft_split(buf, '\n');
	game.mlx = mlx_init(game.w * 32, game.h * 32, "DATING", false);
	if (!game.mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	render_map(&game, map, buf);
	mlx_key_hook(game.mlx, &key_hook, &game);
	integrity_check(buf);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	if (game.grid)
		emergency_cleaning(&game);
	return (EXIT_SUCCESS);
}

int	suffix_check(char *filename)
{
	int	i;

	i = 0;
	while (filename[i] != '\0')
		i++;
	if (filename[i - 4] != '.' || filename[i - 3] != 'b'
		|| filename[i - 2] != 'e' || filename[i - 1] != 'r')
		error_function(1);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_printf("wrong number of arguments\n");
		return (1);
	}
	suffix_check(argv[1]);
	map_check(argv[1]);
	return (0);
}
