/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:29:42 by achowdhu          #+#    #+#             */
/*   Updated: 2026/02/17 14:52:54 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game_data(t_game *game)
{
	game->textures.no = NULL;
	game->textures.so = NULL;
	game->textures.we = NULL;
	game->textures.ea = NULL;
	game->floor.r = -1;
	game->floor.g = -1;
	game->floor.b = -1;
	game->ceiling.r = -1;
	game->ceiling.g = -1;
	game->ceiling.b = -1;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3d <map.cub>\n");
		return (1);
	}
	init_game_data(&game);
	parse(argv[1], &game);
	setup_run_game(&game);
	free_game(&game);
	return (0);
}
