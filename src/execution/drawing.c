/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:05:22 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/05 14:59:13 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	argb(int a, int r, int g, int b)
{
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

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

// 벽 텍스처 그리기
static void	draw_wall(t_ray *ray, t_game *game, int x, mlx_texture_t *tex,
		int tex_x)
{
	int	y;
	int	tex_y;
	int	color;

	y = ray->draw_top;
	while (y <= ray->draw_bottom)
	{
		tex_y = get_texture_row(y, ray, tex);
		color = get_texture_color(tex, tex_x, tex_y);
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

// 바닥 그리기
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

// 기존 draw_ray_column에서 분리된 함수 호출
void	draw_ray_column(t_ray *ray, t_game *game, int x)
{
	mlx_texture_t	*tex;
	int				tex_x;

	tex = texture_selection(ray, game);
	tex_x = get_texture_column(ray, tex, game->player);
	draw_ceiling(game, x, ray->draw_top);
	draw_wall(ray, game, x, tex, tex_x);
	draw_floor(game, x, ray->draw_bottom);
}
