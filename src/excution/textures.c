/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:49:52 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/05 13:58:26 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void load_textures(t_game *game)
{
    if (!game->texture)
        return;

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

void	free_textures(t_game *game)
{
	if (!game->texture)
		return;

	if (game->texture->no_tex)
		mlx_delete_texture(game->texture->no_tex);
	if (game->texture->so_tex)
		mlx_delete_texture(game->texture->so_tex);
	if (game->texture->we_tex)
		mlx_delete_texture(game->texture->we_tex);
	if (game->texture->ea_tex)
		mlx_delete_texture(game->texture->ea_tex);
	if (game->texture->no)
		free(game->texture->no);
	if (game->texture->so)
		free(game->texture->so);
	if (game->texture->we)
		free(game->texture->we);
	if (game->texture->ea)
		free(game->texture->ea);

	free(game->texture);
	game->texture = NULL;
}

/* 레이가 충돌한 벽에 맞는 텍스처 선택 */
mlx_texture_t *texture_selection(t_ray *ray, t_game *game)
{
	if (ray->hit_axis == 0) // 세로벽
	{
		if (ray->step_x > 0)
			return game->texture->we_tex;
		else
			return game->texture->ea_tex;
	}
	else // 가로벽
	{
		if (ray->step_y > 0)
			return game->texture->no_tex;
		else
			return game->texture->so_tex;
	}
}

/* 레이가 맞은 벽에서 텍스처의 컬럼 선택 */
int get_texture_column(t_ray *ray, mlx_texture_t *tex, t_player *player)
{
	double wall_x;

	if (ray->hit_axis == 0) // 세로벽
		wall_x = player->y + ray->distance * ray->dir_y;
	else // 가로벽
		wall_x = player->x + ray->distance * ray->dir_x;

	wall_x -= floor(wall_x); // 벽에서 x좌표만 가져오기
	int tex_x = (int)(wall_x * (double)tex->width);

	if ((ray->hit_axis == 0 && ray->dir_x > 0) ||
		(ray->hit_axis == 1 && ray->dir_y < 0))
		tex_x = (int)tex->width - tex_x - 1;

	return tex_x;
}

/* 스크린 y 위치에 따른 텍스처 row 계산 */
int get_texture_row(int y, t_ray *ray, mlx_texture_t *tex)
{
	int wall_height = ray->draw_bottom - ray->draw_top + 1;
	int tex_height = (int)tex->height;
	int tex_y = (y - ray->draw_top) * tex_height / wall_height;

	if (tex_y < 0) tex_y = 0;
	if (tex_y >= tex_height) tex_y = tex_height - 1;

	return tex_y;
}

int get_texture_color(mlx_texture_t *tex, int x, int y)
{
    int i = (y * tex->width + x) * 4;
    unsigned char r = tex->pixels[i + 0];
    unsigned char g = tex->pixels[i + 1];
    unsigned char b = tex->pixels[i + 2];
    unsigned char a = tex->pixels[i + 3]; // 텍스처에 alpha 없으면 255

    return (r << 24) | (g << 16) | (b << 8) | a; // MLX42 RGBA 포맷
}
