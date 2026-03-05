/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:31:48 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/05 14:07:49 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void key_press(mlx_key_data_t keydata, void *param)
{
    t_game *game = param;

    if (keydata.action == MLX_PRESS)
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
            mlx_close_window(game->mlx);
    }
    else if (keydata.action == MLX_RELEASE)
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
}

void resize(int width, int height, void *param)
{
    t_game *game;
	
	game = (t_game *)param;
    game->width = width;
    game->height = height;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, width, height);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	raycast(game);
}

void close_window(void *param)
{
	t_game *game = param;

	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	exit(0);
}
