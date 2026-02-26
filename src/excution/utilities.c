/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:31:48 by jaeklee           #+#    #+#             */
/*   Updated: 2026/02/26 17:00:42 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	if (!game)
		return;

	// 텍스처 먼저 해제 (mlx 필요)
	free_textures(game);

	// 이미지 해제
	if (game->img)
		mlx_delete_image(game->mlx, game->img);

	// map 해제
	if (game->map)
	{
		if (game->map->grid)
			free_tab(game->map->grid);
		free(game->map);
	}

	// MLX 종료 (제일 마지막)
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

int key_press(mlx_key_data_t keydata, void *param)
{
	t_game *game = (t_game *)param;

	// 키를 눌렀을 때
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W)
			game->forward = true;
		else if (keydata.key == MLX_KEY_S)
			game->back = true;
		else if (keydata.key == MLX_KEY_A)
			game->left = true;
		else if (keydata.key == MLX_KEY_D)
			game->right = true;
		else if (keydata.key == MLX_KEY_LEFT)
			game->rotate_left = true;
		else if (keydata.key == MLX_KEY_RIGHT)
			game->rotate_right = true;
		else if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx); // ESC 누르면 창 종료
	}
	// 키를 뗐을 때
	if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_W)
			game->forward = false;
		else if (keydata.key == MLX_KEY_S)
			game->back = false;
		else if (keydata.key == MLX_KEY_A)
			game->left = false;
		else if (keydata.key == MLX_KEY_D)
			game->right = false;
		else if (keydata.key == MLX_KEY_LEFT)
			game->rotate_left = false;
		else if (keydata.key == MLX_KEY_RIGHT)
			game->rotate_right = false;
	}

	return (0);
}

int resize(int width, int height, void *param)
{
	t_game *game = (t_game *)param;

	// 게임 화면 크기 업데이트
	game->width = width;
	game->height = height;

	// 이미지 다시 생성
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, width, height);

	return (0);
}
void close_window(void *param)
{
	t_game *game = (t_game *)param;

	// 게임 종료 전 리소스 해제
	free_game(game);

	// 창 닫기
	mlx_close_window(game->mlx);
}
