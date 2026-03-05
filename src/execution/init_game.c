/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:09:19 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/05 17:05:30 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// MLX42 및 이미지 초기화만 담당
void	init_graphics(t_game *game)
{
	game->width = WIDTH;
	game->height = HEIGHT;
	game->mlx = mlx_init(game->width, game->height, "cub3D", true);
	if (!game->mlx)
		error_exit(game, "MLX inifailed");
	game->img = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->img)
		error_exit(game, "Image creation failed");
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		error_exit(game, "Image display failed");
}

void	init_game_state(t_game *game, t_map *map)
{
	game->map = map;
	if (!game->player)
		error_exit(game, "Player malloc failed");
	game->player->x = map->p_x + 0.5f;
	game->player->y = map->p_y + 0.5f;
	game->player->move_speed = 0.1f;
	game->player->rot_speed = 0.05f;
	init_player_direction(game->player, map->start_dir);
	game->forward = false;
	game->back = false;
	game->left = false;
	game->right = false;
	game->rotate_left = false;
	game->rotate_right = false;
}

void	init_player_direction(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
	}
	else if (dir == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
	}
	else if (dir == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
	}
	else if (dir == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
	}
	p->plane_x = -p->dir_y * 0.66f;
	p->plane_y = p->dir_x * 0.66f;
}

void	init_ray(t_game *game, t_ray *ray, int i)
{
	double	camera_x;

	camera_x = 2.0 * i / (double)game->width - 1.0;
	ray->dir_x = game->player->dir_x + game->player->plane_x * camera_x;
	ray->dir_y = game->player->dir_y + game->player->plane_y * camera_x;
	ray->map_x = (int)game->player->x;
	ray->map_y = (int)game->player->y;
	if (ray->dir_x == 0)
		ray->del_dist_x = 1e30;
	else
		ray->del_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->del_dist_y = 1e30;
	else
		ray->del_dist_y = fabs(1 / ray->dir_y);
	ray->hit_wall = 0;
	ray->hit_axis = 0;
}

int	argb(int a, int r, int g, int b)
{
	return ((a << 24) | (r << 16) | (g << 8) | b);
}
