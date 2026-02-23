/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:09:19 by jaeklee           #+#    #+#             */
/*   Updated: 2026/02/23 16:31:08 by jaeklee          ###   ########.fr       */
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

void	init_game_state(t_game *game, t_map *map)
{
	game->map = map;

	// player 생성
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		error_exit(game, "Player malloc failed");

	// 위치 설정 (중앙 정렬)
	game->player->x = map->p_x + 0.5f;
	game->player->y = map->p_y + 0.5f;

	game->player->move_speed = 0.1f;
	game->player->rot_speed = 0.05f;

	// 방향 설정
	init_player_direction(game->player, map->start_dir);

	// 키 상태 초기화
	game->forward = false;
	game->back = false;
	game->left = false;
	game->right = false;
	game->rotate_left = false;
	game->rotate_right = false;
}

void	init_player_direction(t_player *p, char dir)
{
	if (dir == 'N')
		(p->dir_x = 0, p->dir_y = -1);
	else if (dir == 'S')
		(p->dir_x = 0, p->dir_y = 1);
	else if (dir == 'E')
		(p->dir_x = 1, p->dir_y = 0);
	else if (dir == 'W')
		(p->dir_x = -1, p->dir_y = 0);

	// 카메라 평면은 방향 벡터의 수직 벡터
	p->plane_x = -p->dir_y * 0.66f;
	p->plane_y = p->dir_x * 0.66f;
}

// void	init_player_direction(t_player *player, char dir)
// {
// 	if (dir == 'N')
// 	{
// 		player->dir_x = 0;
// 		player->dir_y = -1;
// 		player->plane_x = 0.66f;
// 		player->plane_y = 0;
// 	}
// 	else if (dir == 'S')
// 	{
// 		player->dir_x = 0;
// 		player->dir_y = 1;
// 		player->plane_x = -0.66f;
// 		player->plane_y = 0;
// 	}
// 	else if (dir == 'E')
// 	{
// 		player->dir_x = 1;
// 		player->dir_y = 0;
// 		player->plane_x = 0;
// 		player->plane_y = 0.66f;
// 	}
// 	else if (dir == 'W')
// 	{
// 		player->dir_x = -1;
// 		player->dir_y = 0;
// 		player->plane_x = 0;
// 		player->plane_y = -0.66f;
// 	}
// }
