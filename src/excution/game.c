/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:13:44 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/02 14:24:33 by jaeklee          ###   ########.fr       */
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

static void	rotate_player(t_player *p, float rot)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;

	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);

	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}
void	movement(t_game *game)
{
	t_player	*p;
	float		move;

	p = game->player;
	move = p->move_speed;

	if (game->forward)
	{
		if (!is_wall(game, p->x + p->dir_x * move, p->y))
			p->x += p->dir_x * move;
		if (!is_wall(game, p->x, p->y + p->dir_y * move))
			p->y += p->dir_y * move;
	}
	if (game->back)
	{
		if (!is_wall(game, p->x - p->dir_x * move, p->y))
			p->x -= p->dir_x * move;
		if (!is_wall(game, p->x, p->y - p->dir_y * move))
			p->y -= p->dir_y * move;
	}
	if (game->left)
	{
		if (!is_wall(game, p->x - p->plane_x * move, p->y))
			p->x -= p->plane_x * move;
		if (!is_wall(game, p->x, p->y - p->plane_y * move))
			p->y -= p->plane_y * move;
	}
	if (game->right)
	{
		if (!is_wall(game, p->x + p->plane_x * move, p->y))
			p->x += p->plane_x * move;
		if (!is_wall(game, p->x, p->y + p->plane_y * move))
			p->y += p->plane_y * move;
	}
	if (game->rotate_left)
		rotate_player(p, -p->rot_speed);
	if (game->rotate_right)
		rotate_player(p, p->rot_speed);
}

static inline int rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw(t_game *game)
{
	int	x;
	int	y;
	int	ceil_color;
	int	floor_color;

	ceil_color = rgba(game->ceiling.r,
					  game->ceiling.g,
					  game->ceiling.b, 255);
	floor_color = rgba(game->floor.r,
					   game->floor.g,
					   game->floor.b, 255);

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (y < game->height / 2)
				mlx_put_pixel(game->img, x, y, ceil_color);
			else
				mlx_put_pixel(game->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	movement(game);
	draw(game);
	// raycast(game, game->map);
}


void play_game(t_game *game, t_map *map)
{
	init_graphics(game);
	init_game_state(game, map);
	load_textures(game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_key_hook(game->mlx, key_press, game);
	mlx_resize_hook(game->mlx, resize, game);
	mlx_close_hook(game->mlx, close_window, game);
	mlx_loop(game->mlx);
}
