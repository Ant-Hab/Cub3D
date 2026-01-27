/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:29:42 by achowdhu          #+#    #+#             */
/*   Updated: 2026/01/27 14:34:54 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Usage: ./cub3D <map.cub>");

	parse_file(argv[1], &game);

	/* TEMP DEBUG */
	printf("NO: %s\n", game.textures.no);
	printf("SO: %s\n", game.textures.so);
	printf("WE: %s\n", game.textures.we);
	printf("EA: %s\n", game.textures.ea);
	printf("F: %d,%d,%d\n", game.floor.r,
		game.floor.g, game.floor.b);
	printf("C: %d,%d,%d\n", game.ceiling.r,
		game.ceiling.g, game.ceiling.b);

	free_game(&game);
	return (0);
}
