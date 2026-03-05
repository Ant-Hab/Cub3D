/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:13:44 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/05 14:35:38 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, float x, float y)
{
	int	map_x = (int)x;
	int	map_y = (int)y;

	if (map_x < 0 || map_y < 0
		|| map_x >= game->map->width
		|| map_y >= game->map->height)
		return (1);
	if (game->map->grid[map_y][map_x] == '1')
		return (1);
	return (0);
}


// void movement(t_game *game)
// {
// 	t_player *p = game->player;
// 	float move = p->move_speed;
// 	float next_x, next_y;

// 	if (game->forward)
// 	{
// 		next_x = p->x + p->dir_x * move;
// 		next_y = p->y + p->dir_y * move;

// 		if (!is_wall(game, next_x, p->y))
// 			p->x = next_x;
// 		if (!is_wall(game, p->x, next_y))
// 			p->y = next_y;
// 	}
// 	if (game->back)
// 	{
// 		next_x = p->x - p->dir_x * move;
// 		next_y = p->y - p->dir_y * move;

// 		if (!is_wall(game, next_x, p->y))
// 			p->x = next_x;
// 		if (!is_wall(game, p->x, next_y))
// 			p->y = next_y;
// 	}
// 	if (game->left)
// 	{
// 		next_x = p->x - p->plane_x * move;
// 		next_y = p->y - p->plane_y * move;

// 		if (!is_wall(game, next_x, p->y))
// 			p->x = next_x;
// 		if (!is_wall(game, p->x, next_y))
// 			p->y = next_y;
// 	}
// 	if (game->right)
// 	{
// 		next_x = p->x + p->plane_x * move;
// 		next_y = p->y + p->plane_y * move;

// 		if (!is_wall(game, next_x, p->y))
// 			p->x = next_x;
// 		if (!is_wall(game, p->x, next_y))
// 			p->y = next_y;
// 	}
// 	if (game->rotate_left)
// 		rotate_player(p, -p->rot_speed);
// 	if (game->rotate_right)
// 		rotate_player(p, p->rot_speed);
// 	if (p->x < 0.01) p->x = 0.01;
// 	if (p->y < 0.01) p->y = 0.01;
// 	if (p->x > game->map->width - 0.01) p->x = game->map->width - 0.01;
// 	if (p->y > game->map->height - 0.01) p->y = game->map->height - 0.01;
// }


void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	movement(game);
	raycast(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}



void play_game(t_game *game, t_map *map)
{
	init_graphics(game);
	init_game_state(game, map);
	load_textures(game);
	mlx_resize_hook(game->mlx, resize, game);
	mlx_key_hook(game->mlx, key_press, game);
	mlx_close_hook(game->mlx, close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	printf("debug2\n");
	mlx_loop(game->mlx);
	printf("debug3\n");
}
