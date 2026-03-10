/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:13:44 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/10 16:47:47 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_x >= game->map->width
		|| map_y >= game->map->height)
		return (1);
	if (game->map->grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	movement(game);
	raycast(game);
}

void	play_game(t_game *game, t_map *map)
{
	init_graphics(game);
	init_game_state(game, map);
	load_textures(game);
	mlx_resize_hook(game->mlx, resize, game);
	mlx_key_hook(game->mlx, key_press, game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_close_hook(game->mlx, close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
