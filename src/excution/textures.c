/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:49:52 by jaeklee           #+#    #+#             */
/*   Updated: 2026/02/24 10:53:35 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_game *game)
{
	game->texture.no = mlx_load_png(game->texture.no);
	if (!game->texture.no_tex)
		error_and_cleanup(game, "Failed to load north texture");

	game->texture.so_tex = mlx_load_png(game->texture.so);
	if (!game->texture.so_tex)
		error_and_cleanup(game, "Failed to load south texture");

	game->texture.we_tex = mlx_load_png(game->texture.we);
	if (!game->texture.we_tex)
		error_and_cleanup(game, "Failed to load west texture");

	game->texture.ea_tex = mlx_load_png(game->texture.ea);
	if (!game->texture.ea_tex)
		error_and_cleanup(game, "Failed to load east texture");
}

void	free_textures(t_game *game)
{
	if (game->texture.no_tex)
		mlx_delete_texture(game->texture.no_tex);
	if (game->texture.so_tex)
		mlx_delete_texture(game->texture.so_tex);
	if (game->texture.we_tex)
		mlx_delete_texture(game->texture.we_tex);
	if (game->texture.ea_tex)
		mlx_delete_texture(game->texture.ea_tex);
}
