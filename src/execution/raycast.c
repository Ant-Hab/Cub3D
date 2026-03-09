/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:25:59 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/09 17:16:55 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_move(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->x - ray->map_x) * ray->del_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->x)
			* ray->del_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->y - ray->map_y) * ray->del_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->y)
			* ray->del_dist_y;
	}
}

static void	check_wall_and_bounds(t_game *game, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_y < 0 || ray->map_x >= game->map->width
		|| ray->map_y >= game->map->height)
	{
		ray->hit_wall = 1;
		ray->wall_texture = game->texture->no;
		return ;
	}
	if (is_wall(game, ray->map_x, ray->map_y))
	{
		ray->hit_wall = 1;
		if (ray->hit_axis == 0)
		{
			if (ray->step_x > 0)
				ray->wall_texture = game->texture->we;
			else
				ray->wall_texture = game->texture->ea;
		}
		else
		{
			if (ray->step_y > 0)
				ray->wall_texture = game->texture->no;
			else
				ray->wall_texture = game->texture->so;
		}
	}
}

void	dda_and_wall(t_game *game, t_ray *ray)
{
	while (ray->hit_wall == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->del_dist_x;
			ray->map_x += ray->step_x;
			ray->hit_axis = 0;
		}
		else
		{
			ray->side_dist_y += ray->del_dist_y;
			ray->map_y += ray->step_y;
			ray->hit_axis = 1;
		}
		check_wall_and_bounds(game, ray);
		if (ray->hit_wall && (ray->map_x < 0 || ray->map_y < 0
				|| ray->map_x >= game->map->width
				|| ray->map_y >= game->map->height))
			break ;
	}
}

void	calculate_wall(t_game *game, t_ray *ray)
{
	if (ray->hit_axis == 0)
		ray->distance = ray->side_dist_x - ray->del_dist_x;
	else
		ray->distance = ray->side_dist_y - ray->del_dist_y;
	if (ray->distance < 0.9)
		ray->distance = 0.9;
	ray->pixel_height = (int)(game->height / ray->distance);
	ray->draw_top = (game->height / 2) - (ray->pixel_height / 2);
	ray->draw_bottom = (game->height / 2) + (ray->pixel_height / 2);
	if (ray->draw_top < 0)
		ray->draw_top = 0;
	if (ray->draw_bottom >= game->height)
		ray->draw_bottom = game->height - 1;
}

void	raycast(t_game *game)
{
	int		i;
	t_ray	ray;

	i = 0;
	while (i < game->width)
	{
		init_ray(game, &ray, i);
		init_ray_move(game, &ray);
		dda_and_wall(game, &ray);
		calculate_wall(game, &ray);
		draw_ray_column(&ray, game, i);
		i++;
	}
}
