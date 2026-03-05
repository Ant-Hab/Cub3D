/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:09:21 by jaeklee           #+#    #+#             */
/*   Updated: 2026/03/05 14:35:47 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void move_forward_backward(t_game *game, float move)
{
    t_player *p = game->player;
    float next_x, next_y;

    if (game->forward)
    {
        next_x = p->x + p->dir_x * move;
        next_y = p->y + p->dir_y * move;
        if (!is_wall(game, next_x, p->y)) p->x = next_x;
        if (!is_wall(game, p->x, next_y)) p->y = next_y;
    }
    if (game->back)
    {
        next_x = p->x - p->dir_x * move;
        next_y = p->y - p->dir_y * move;
        if (!is_wall(game, next_x, p->y)) p->x = next_x;
        if (!is_wall(game, p->x, next_y)) p->y = next_y;
    }
}
static void	rotate_player(t_player *p, float rot)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;

	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);

	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}
// 좌/우 이동 처리
static void move_left_right(t_game *game, float move)
{
    t_player *p = game->player;
    float next_x, next_y;

    if (game->left)
    {
        next_x = p->x - p->plane_x * move;
        next_y = p->y - p->plane_y * move;
        if (!is_wall(game, next_x, p->y)) p->x = next_x;
        if (!is_wall(game, p->x, next_y)) p->y = next_y;
    }
    if (game->right)
    {
        next_x = p->x + p->plane_x * move;
        next_y = p->y + p->plane_y * move;
        if (!is_wall(game, next_x, p->y)) p->x = next_x;
        if (!is_wall(game, p->x, next_y)) p->y = next_y;
    }
}

// 회전 및 경계 처리
static void rotate_and_clamp(t_game *game)
{
    t_player *p = game->player;

    if (game->rotate_left)
        rotate_player(p, -p->rot_speed);
    if (game->rotate_right)
        rotate_player(p, p->rot_speed);

    // 맵 경계 제한
    if (p->x < 0.01) p->x = 0.01;
    if (p->y < 0.01) p->y = 0.01;
    if (p->x > game->map->width - 0.01) p->x = game->map->width - 0.01;
    if (p->y > game->map->height - 0.01) p->y = game->map->height - 0.01;
}

// 기존 movement 함수에서 분리된 함수 호출
void movement(t_game *game)
{
    float move = game->player->move_speed;

    move_forward_backward(game, move);
    move_left_right(game, move);
    rotate_and_clamp(game);
}
