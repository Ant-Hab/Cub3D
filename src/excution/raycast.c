/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:25:59 by jaeklee           #+#    #+#             */
/*   Updated: 2026/02/24 15:35:35 by achowdhu         ###   ########.fr       */
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
	ray->camera_x =  2.0 * i / (double)game->width - 1.0;
	ray->dir_x = game->player->dir_x + game->player->plane_x
		* ray->camera_x;
	ray->dir_y = game->player->dir_y + game->player->plane_y
		* ray->camera_x;
	ray->player_x = game->player->x;
	ray->player_y = game->player->y;
	ray->del_dist_x = fabs(1 / ray->dir_x);
	ray->del_dist_y = fabs(1 / ray->dir_y);
	ray->hit_wall = 0;
	ray->hit_axis = 0;
}
