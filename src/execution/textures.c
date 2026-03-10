/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:49:52 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/10 15:27:14 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_game *game)
{
	if (!game->texture)
		return ;
	game->texture->no_tex = mlx_load_png(game->texture->no);
	if (!game->texture->no_tex)
		error_exit(game, "Failed to load north texture");
	game->texture->so_tex = mlx_load_png(game->texture->so);
	if (!game->texture->so_tex)
		error_exit(game, "Failed to load north texture");
	game->texture->we_tex = mlx_load_png(game->texture->we);
	if (!game->texture->we_tex)
		error_exit(game, "Failed to load north texture");
	game->texture->ea_tex = mlx_load_png(game->texture->ea);
	if (!game->texture->ea_tex)
		error_exit(game, "Failed to load north texture");
}

mlx_texture_t	*texture_selection(t_ray *ray, t_game *game)
{
	if (ray->hit_axis == 0)
	{
		if (ray->step_x > 0)
			return (game->texture->we_tex);
		else
			return (game->texture->ea_tex);
	}
	else
	{
		if (ray->step_y > 0)
			return (game->texture->no_tex);
		else
			return (game->texture->so_tex);
	}
}

int	get_texture_column(t_ray *ray, mlx_texture_t *tex, t_player *player)
{
	double	wall_x;
	int		tex_x;

	if (ray->hit_axis == 0)
		wall_x = player->y + ray->distance * ray->dir_y;
	else
		wall_x = player->x + ray->distance * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->hit_axis == 0 && ray->dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->hit_axis == 1 && ray->dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

int	get_texture_color(mlx_texture_t *tex, int x, int y)
{
	int				i;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;

	if (x < 0)
		x = 0;
	if (x >= (int)tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= (int)tex->height)
		y = tex->height - 1;
	i = (y * tex->width + x) * 4;
	r = tex->pixels[i + 0];
	g = tex->pixels[i + 1];
	b = tex->pixels[i + 2];
	a = tex->pixels[i + 3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
