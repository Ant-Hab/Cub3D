/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:29:42 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/03 10:22:19 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	main(int argc, char **argv)
// {
// 	t_game	*game;
// 	int		len;

// 	if (argc != 2)
// 	{
// 		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31);
// 		return (1);
// 	}
// 	len = ft_strlen(argv[1]);
// 	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
// 	{
// 		printf("Error\nInvalid extension\n");
// 		return (1);
// 	}
// 	game = parse(argv[1], &game);
// 	if (game)
// 	{	
// 		play_game(game, game->map);
// 		// print_textures(game);
// 		// print_map(&game->map);
// 		free_game(game);
// 	}
// 	return (0);
// }
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
	printf("debug0\n");
	// parse()가 game_instance를 초기화하도록
	parse(argv[1]);
	printf("debug22\n");
	// 게임 시작
	play_game(&game, game.map);

	// 게임 종료 후 정리
	free_game(&game);

	return (0);
}
