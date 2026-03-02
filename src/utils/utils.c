/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:35:45 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/02 16:40:21 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Prints error message, frees allocated game memory, and exits program */

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
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	else
		perror("System Error");
	if (game)
		free_game(game);
	exit(1);
}

/* Frees a NULL-terminated array of strings */
void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/* Frees all dynamically allocated members inside game struct */
// void	free_game(t_game *game)
// {
// 	if (!game)
// 		return ;
// 	if (game->textures.no)
// 		free(game->textures.no);
// 	if (game->textures.so)
// 		free(game->textures.so);
// 	if (game->textures.we)
// 		free(game->textures.we);
// 	if (game->textures.ea)
// 		free(game->textures.ea);
// 	if (game->map.grid)
// 		free_tab(game->map.grid);
// 	free(game);
// }

/* Performs recursive flood fill to verify map is fully enclosed */
int	flood_fill(char **copy, int x, int y, int max_y)
{
	if (y < 0 || y >= max_y || x < 0 || !copy[y] || !copy[y][x]
		|| copy[y][x] == ' ')
		return (1);
	if (copy[y][x] == '1' || copy[y][x] == 'V')
		return (0);
	copy[y][x] = 'V';
	if (flood_fill(copy, x + 1, y, max_y))
		return (1);
	if (flood_fill(copy, x - 1, y, max_y))
		return (1);
	if (flood_fill(copy, x, y + 1, max_y))
		return (1);
	if (flood_fill(copy, x, y - 1, max_y))
		return (1);
	return (0);
}

/* Checks if a line is empty or contains only whitespace characters */
bool	empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (true);
	while (line[i] && (line[i] == ' '
			|| line[i] == '\t'
			|| line[i] == '\n'))
		i++;
	return (line[i] == '\0');
}
