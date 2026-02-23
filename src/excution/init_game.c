/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:09:19 by jaeklee           #+#    #+#             */
/*   Updated: 2026/02/23 15:06:45 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_game(t_game *game, t_map *map)
{
	init_graphics(game);
	init_game_state(game, map);
}

// MLX42 및 이미지 초기화만 담당
void	init_graphics(t_game *game)
{
	game->width = WIDTH;
	game->height = HEIGHT;

	// MLX42 초기화
	game->mlx = mlx_init(game->width, game->height, "cub3D", true);
	if (!game->mlx)
		error_exit(game, "MLX inifailed");

	// 이미지 생성
	game->img = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->img)
		error_exit(game, "Image creation failed");

	// 이미지 윈도우에 붙이기
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		error_exit(game, "Image display failed");
}

// 게임 상태 초기화 + 지도/플레이어 세팅
void	init_game_state(t_game *game, t_map *map)
{
	// 지도와 플레이어 연결
	game->map = map;
	game->player = map->player;

	// 키 상태 초기화
	game->forward = false;
	game->back = false;
	game->left = false;
	game->right = false;
	game->rotate_left = false;
	game->rotate_right = false;

	// 플레이어 초기 방향 설정
	init_player_north_south(game->player);
	init_player_east_west(game->player);
}

