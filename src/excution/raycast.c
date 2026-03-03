/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:25:59 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/03 10:57:27 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	init_ray(t_game *game, t_ray *ray, int i)
{
	double	camera_x;

	camera_x = 2.0 * i / (double)game->width - 1.0; 

	ray->dir_x = game->player->dir_x
		+ game->player->plane_x * camera_x;
	ray->dir_y = game->player->dir_y
		+ game->player->plane_y * camera_x;
	ray->map_x = (int)game->player->x; // the location of player in the map
	ray->map_y = (int)game->player->y;
	if (ray->dir_x == 0)
		ray->del_dist_x = 1e30; //the distance required to move one grid cell
	else
		ray->del_dist_x = fabs(1 / ray->dir_x); // delta_distance

	if (ray->dir_y == 0)
		ray->del_dist_y = 1e30;
	else
		ray->del_dist_y = fabs(1 / ray->dir_y);

	ray->hit_wall = 0;
	ray->hit_axis = 0;
}

void	init_ray_move(t_game *game,t_ray *ray)
{
	if (ray->dir_x < 0) // x
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
	if (ray->dir_y < 0) // y
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

void	dda_and_wall(t_game *game, t_ray *ray)
{
	while (ray->hit_wall == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->del_dist_x; // 다음 X선까지 거리 증가
			ray->map_x += ray->step_x;           // X 방향 이동
			ray->hit_axis = 0;                   // 세로벽 가능
		}
		else
		{
			ray->side_dist_y += ray->del_dist_y; // 다음 Y선까지 거리 증가
			ray->map_y += ray->step_y;           // Y 방향 이동
			ray->hit_axis = 1;                   // 가로벽 가능
		}
		if (is_wall(game, ray->map_x, ray->map_y))
		{
			ray->hit_wall = 1;
			if (ray->hit_axis == 0)  // 세로벽
			{
				if (ray->step_x > 0)
					ray->wall_texture = game->texture->we;
				else
					ray->wall_texture = game->texture->ea;
			}
			else  // 가로벽
			{
				if (ray->step_y > 0)
					ray->wall_texture = game->texture->no;
				else
					ray->wall_texture = game->texture->so;
			}
		}
	}
}

void calculate_wall( t_game *game, t_ray *ray)
{
	if (ray->hit_axis == 0)
		ray->distance = ray->side_dist_x - ray->del_dist_x;
	else
		ray->distance = ray->side_dist_y - ray->del_dist_y;
	ray->pixel_height = (int)(game->height / ray->distance);
	ray->draw_top = (game->height / 2) - (ray->pixel_height / 2);
	ray->draw_bottom = (game->height / 2) + (ray->pixel_height / 2);
}
void	draw_ray_column(t_ray *ray, t_game *game, int x)
{
	mlx_texture_t *tex = texture_selection(ray, game);
	int tex_x = get_texture_column(ray, tex, game->player);
	int y;

	for (y = 0; y < ray->draw_top; y++)
	{
		mlx_put_pixel(game->img, x, y,
			(game->ceiling.r << 16) | (game->ceiling.g << 8) | game->ceiling.b);
	}

	for (y = ray->draw_top; y <= ray->draw_bottom; y++)
	{
		int tex_y = get_texture_row(y, ray, tex);
		int color = get_texture_color(tex, tex_x, tex_y);
		mlx_put_pixel(game->img, x, y, color);
	}

	for (y = ray->draw_bottom + 1; y < game->height; y++)
	{
		mlx_put_pixel(game->img, x, y,
			(game->floor.r << 16) | (game->floor.g << 8) | game->floor.b);
	}
}
void raycast(t_game *game)
{
    int i;
    t_ray ray;
	
    i = 0;
    while (i < game->width)
    {
        init_ray(game, &ray, i);
        init_ray_move(game, &ray);
        dda_and_wall(game, &ray);
        calculate_wall( game, &ray);
        draw_ray_column(&ray, game, i);
        i++;
    }
}
