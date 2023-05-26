/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:59:27 by msulc             #+#    #+#             */
/*   Updated: 2023/05/23 14:59:29 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	collect(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->collectibles)
	{
		if (game->coll->coll->instances[i].x == game->player->instances[0].x
			&& game->coll->coll->instances[i].y == game->player->instances[0].y)
			game->coll->coll->instances[i].enabled = 0;
		i++;
	}
	if (game->c == 0)
	{
		game->player->instances[0].enabled = 0;
		game->couple->instances[0].enabled = 1;
		game->exitus->instances[0].enabled = 1;
	}
}

void	put_collectible(t_game *game, int y, int i)
{
	mlx_image_to_window(game->mlx, game->coll->coll, (y * 32), (i * 32));
}

void	player_rendering(t_game *game, int y, int i)
{
	mlx_image_to_window(game->mlx, game->couple, (y * 32), (i * 32));
	game->couple->instances[0].enabled = 0;
	mlx_image_to_window(game->mlx, game->player, (y * 32), (i * 32));
	game->p_pos_h = i;
	game->p_pos_l = y;
}

void	while_function(t_game *game, t_map *map, int y, int i)
{
	i = 0;
	while (i < map->hight)
	{
		y = 0;
		while (y < map->lenght)
		{
			if (game->grid[i][y] == '1')
				mlx_image_to_window(game->mlx, game->wall, (y * 32), (i * 32));
			else if (game->grid[i][y] == 'E')
			{
				mlx_image_to_window(game->mlx, \
				game->exitus, (y * 32), (i * 32));
				game->exitus->instances[0].enabled = 0;
			}
			else if (game->grid[i][y] == 'C')
				put_collectible(game, y, i);
			else if (game->grid[i][y] == 'P')
				player_rendering(game, y, i);
			else if (game->grid[i][y] == 'X')
				mlx_image_to_window(game->mlx, game->enemy, (y * 32), (i * 32));
			y++;
		}
		i++;
	}
}

void	render_map(t_game *game, t_map *map, char *buf)
{
	int	i;
	int	y;

	image_loader(game);
	i = 0;
	while (i < map->hight)
	{
		y = 0;
		while (y < map->lenght)
		{
			mlx_image_to_window(game->mlx, game->floor, (y * 32), (i * 32));
			y++;
		}
		i++;
	}
	i = 0;
	while_function(game, map, y, i);
	mlx_image_to_window(game->mlx, game->back, 0, 0);
}
