/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:57:32 by msulc             #+#    #+#             */
/*   Updated: 2023/05/23 14:57:35 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_up(t_game *game)
{
	if (game->grid[game->p_pos_h - 1][game->p_pos_l] == '1'
	|| (game->grid[game->p_pos_h - 1][game->p_pos_l] == 'X' && game->c == 0))
		return ;
	else if (game->grid[game->p_pos_h - 1][game->p_pos_l] == 'X' && game->c > 0)
		beaten_by_husband(game);
	else
	{
		game->player->instances[0].y -= 32;
		game->couple->instances[0].y = game->player->instances[0].y;
		game->p_pos_h -= 1;
		game->count++;
		bonus_count(game);
		ft_printf("number of moves: %d\n", game->count);
		if (game->grid[game->p_pos_h][game->p_pos_l] == 'C')
		{
			game->c--;
			collect(game);
			game->grid[game->p_pos_h][game->p_pos_l] = 'P';
		}
		if (game->grid[game->p_pos_h][game->p_pos_l] == 'E' && game->c == 0)
		{
			ft_printf("And They Lived Happily Ever After\n");
			final_cleaning(game);
		}
	}
}

void	move_down(t_game *game)
{
	if (game->grid[game->p_pos_h + 1][game->p_pos_l] == '1'
	|| (game->grid[game->p_pos_h + 1][game->p_pos_l] == 'X' && game->c == 0))
		return ;
	else if (game->grid[game->p_pos_h + 1][game->p_pos_l] == 'X' && game->c > 0)
		beaten_by_husband(game);
	else
	{
		game->player->instances[0].y += 32;
		game->couple->instances[0].y = game->player->instances[0].y;
		game->p_pos_h += 1;
		game->count++;
		bonus_count(game);
		ft_printf("number of moves: %d\n", game->count);
		if (game->grid[game->p_pos_h][game->p_pos_l] == 'C')
		{
			game->c--;
			collect(game);
			game->grid[game->p_pos_h][game->p_pos_l] = '0';
		}
		if (game->grid[game->p_pos_h][game->p_pos_l] == 'E' && game->c == 0)
		{
			ft_printf("And They Lived Happily Ever After\n");
			final_cleaning(game);
		}
	}
}

void	move_left(t_game *game)
{
	if (game->grid[game->p_pos_h][game->p_pos_l - 1] == '1'
	|| (game->grid[game->p_pos_h][game->p_pos_l - 1] == 'X' && game->c == 0))
		return ;
	else if (game->grid[game->p_pos_h][game->p_pos_l - 1] == 'X' && game->c > 0)
		beaten_by_husband(game);
	else
	{
		game->player->instances[0].x -= 32;
		game->couple->instances[0].x = game->player->instances[0].x;
		game->p_pos_l -= 1;
		game->count++;
		bonus_count(game);
		ft_printf("number of moves: %d\n", game->count);
		if (game->grid[game->p_pos_h][game->p_pos_l] == 'C')
		{
			game->c--;
			collect(game);
			game->grid[game->p_pos_h][game->p_pos_l] = '0';
		}
		if (game->grid[game->p_pos_h][game->p_pos_l] == 'E' && game->c == 0)
		{
			ft_printf("And They Lived Happily Ever After\n");
			final_cleaning(game);
		}
	}
}

void	move_right(t_game *game)
{
	if (game->grid[game->p_pos_h][game->p_pos_l + 1] == '1'
	|| (game->grid[game->p_pos_h][game->p_pos_l + 1] == 'X' && game->c == 0))
		return ;
	else if (game->grid[game->p_pos_h][game->p_pos_l + 1] == 'X' && game->c > 0)
		beaten_by_husband(game);
	else
	{
		game->player->instances[0].x += 32;
		game->couple->instances[0].x = game->player->instances[0].x;
		game->p_pos_l += 1;
		game->count++;
		bonus_count(game);
		ft_printf("number of moves: %d\n", game->count);
		if (game->grid[game->p_pos_h][game->p_pos_l] == 'C')
		{
			game->c--;
			collect(game);
			game->grid[game->p_pos_h][game->p_pos_l] = '0';
		}
		if (game->grid[game->p_pos_h][game->p_pos_l] == 'E' && game->c == 0)
		{
			ft_printf("And They Lived Happily Ever After\n");
			final_cleaning(game);
		}
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		final_cleaning(game);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_up(game);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_down(game);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_left(game);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_right(game);
}
