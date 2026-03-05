/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:05:22 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/05 17:05:42 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling(t_game *game, int x, int draw_top)
{
	int	y;
	int	ceil_color;

	y = 0;
	ceil_color = (game->ceiling.r << 24) | (game->ceiling.g << 16)
		| (game->ceiling.b << 8) | 255;
	while (y < draw_top)
	{
		mlx_put_pixel(game->img, x, y, ceil_color);
		y++;
	}
}

static mlx_texture_t	*get_wall_texture(t_ray *ray, t_game *game)
{
	if (ray->wall_texture == game->texture->no)
		return (game->texture->no_tex);
	if (ray->wall_texture == game->texture->so)
		return (game->texture->so_tex);
	if (ray->wall_texture == game->texture->we)
		return (game->texture->we_tex);
	if (ray->wall_texture == game->texture->ea)
		return (game->texture->ea_tex);
	return (NULL);
}

static void	draw_wall(t_ray *ray, t_game *game, int x, int tex_x)
{
	int				y;
	int				tex_y;
	int				color;
	mlx_texture_t	*tex;

	tex = get_wall_texture(ray, game);
	y = ray->draw_top;
	while (y <= ray->draw_bottom)
	{
		tex_y = get_texture_row(y, ray, tex);
		color = get_texture_color(tex, tex_x, tex_y);
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

static void	draw_floor(t_game *game, int x, int draw_bottom)
{
	int	y;
	int	floor_color;

	y = draw_bottom + 1;
	floor_color = (game->floor.r << 24) | (game->floor.g << 16)
		| (game->floor.b << 8) | 255;
	while (y < game->height)
	{
		mlx_put_pixel(game->img, x, y, floor_color);
		y++;
	}
}

void	draw_ray_column(t_ray *ray, t_game *game, int x)
{
	mlx_texture_t	*tex;
	int				tex_x;

	tex = texture_selection(ray, game);
	tex_x = get_texture_column(ray, tex, game->player);
	draw_ceiling(game, x, ray->draw_top);
	draw_wall(ray, game, x, tex_x);
	draw_floor(game, x, ray->draw_bottom);
}
