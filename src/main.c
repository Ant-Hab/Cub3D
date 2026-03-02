/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:29:42 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/02 16:03:04 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game_instance;
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

	// parse()가 game_instance를 초기화하도록
	parse(argv[1]);

	/* DEBUG
    // print_textures(&game_instance);
    // print_map(&game_instance);
    */

	// 게임 시작
	play_game(&game_instance, game_instance.map);

	// 게임 종료 후 정리
	free_game(&game_instance);

	return (0);
}
