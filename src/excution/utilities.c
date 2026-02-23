/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:31:48 by jaeklee           #+#    #+#             */
/*   Updated: 2026/02/23 15:02:28 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	if (!game)
		return;

	// map 해제
	if (game->map)
	{
		if (game->map->grid)
			free_tab(game->map->grid);  // char **grid 해제
		free(game->map);
	}

	// 이미지 해제
	if (game->img)
		mlx_delete_image(game->mlx, game->img);

	// MLX 윈도우 해제
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void	error_exit(t_game *game, char *msg)
{
	if (msg)
		fprintf(stderr, "Error: %s\n", msg);

	// 게임 관련 메모리 해제
	if (game)
		free_game(game);

	exit(EXIT_FAILURE);
}
