/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:25:59 by jaeklee           #+#    #+#             */
/*   Updated: 2026/02/26 14:12:36 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void raycast(t_game *game, t_map *map)
{
	int	i;
	t_ray *ray;
	
	i = 0;
	while (i < game->width)
	{
		init_ray(game,ray,i);
	}
}

void	init_ray(t_game *game, t_ray *ray, int i)
{
	double	camera_x;

	camera_x = 2.0 * i / (double)game->width - 1.0;

	// 레이 방향 벡터 계산
	ray->dir_x = game->player->dir_x
		+ game->player->plane_x * camera_x;
	ray->dir_y = game->player->dir_y
		+ game->player->plane_y * camera_x;

	// 현재 플레이어가 위치한 맵 칸
	ray->map_x = (int)game->player->x;
	ray->map_y = (int)game->player->y;

	// 한 칸 이동 시 증가 거리 계산
	if (ray->dir_x == 0)
		ray->del_dist_x = 1e30;
	else
		ray->del_dist_x = fabs(1 / ray->dir_x);

	if (ray->dir_y == 0)
		ray->del_dist_y = 1e30;
	else
		ray->del_dist_y = fabs(1 / ray->dir_y);

	// 5️⃣ 초기화
	ray->hit_wall = 0;
	ray->hit_axis = 0;
}

void	init_ray_move(t_ray *ray, t_game *game)
{
	// X 방향
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->x - ray->map_x)
			* ray->del_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->x)
			* ray->del_dist_x;
	}
	// Y 방향
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->y - ray->map_y)
			* ray->del_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->y)
			* ray->del_dist_y;
	}
}
