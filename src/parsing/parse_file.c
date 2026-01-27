/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:35:24 by achowdhu          #+#    #+#             */
/*   Updated: 2026/01/27 14:35:28 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game(t_game *game)
{
	game->textures.no = NULL;
	game->textures.so = NULL;
	game->textures.we = NULL;
	game->textures.ea = NULL;
	game->map.grid = NULL;
}

void	parse_file(char *path, t_game *game)
{
	int	fd;

	init_game(game);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file");

	/* STEP 1: parse textures & colors */
	/* STEP 2: parse map */
	/* STEP 3: validate map */

	close(fd);
}
