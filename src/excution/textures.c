/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:49:52 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/02 14:44:16 by jaeklee          ###   ########.fr       */
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

	// Free the path strings
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
