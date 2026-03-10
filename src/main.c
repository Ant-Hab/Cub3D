/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:29:42 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/10 16:19:11 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	int		len;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31);
		return (1);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
	{
		printf("Error\nInvalid extension\n");
		return (1);
	}
	if (!parse(&game, argv[1]))
		return (1);
	print_textures(&game);
	print_map(&game);
	debug_validate_parsing(&game);
	play_game(&game, game.map);
	free_game(&game);
	return (0);
}
