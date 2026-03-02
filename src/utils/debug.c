/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:13:14 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/02 14:17:59 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_sep(char *title)
{
	printf("\033[1;33m================ %s ================\033[0m\n", title);
}

// void	print_textures(t_game *game)
// {
// 	print_sep("TEXTURES & COLORS");
// 	printf("NO: [%s]\nSO: [%s]\nWE: [%s]\nEA: [%s]\n",
// 		game->texture.no, game->texture.so,
// 		game->texture.we, game->texture.ea);
// 	printf("Floor:   RGB(%d,%d,%d)\n",
// 		game->floor.r, game->floor.g, game->floor.b);
// 	printf("Ceiling: RGB(%d,%d,%d)\n",
// 		game->ceiling.r, game->ceiling.g, game->ceiling.b);
// }

void	print_map(t_map *map)
{
	int	i;
	int	j;

	print_sep("MAP GRID");
	if (!map->grid)
		return ;
	i = -1;
	while (map->grid[++i])
	{
		printf("%03d: ", i);
		j = -1;
		while (map->grid[i][++j])
		{
			if (map->grid[i][j] == '1')
				printf("\033[1;37m1\033[0m");
			else if (ft_strchr("NSEW", map->grid[i][j]))
				printf("\033[1;32m%c\033[0m", map->grid[i][j]);
			else
				printf("%c", map->grid[i][j]);
		}
		printf("\n");
	}
}

// void	debug_validate_parsing(t_game *game)
// {
// 	char	**tmp;

// 	print_sep("VALIDATION CHECK");
// 	if (!game->map.grid)
// 		return ;
// 	tmp = copy_grid(game->map.grid, game->map.height);
// 	if (tmp && !flood_fill(tmp, game->map.p_x, game->map.p_y, game->map.height))
// 		printf("\033[1;32mMap Integrity: CLOSED (Valid)\033[0m\n");
// 	else
// 		printf("\033[1;31mMap Integrity: INVALID\033[0m\n");
// 	free_tab(tmp);
// }
void	print_textures(t_game *game)
{
	print_sep("TEXTURES & COLORS");
	printf("NO: [%s]\nSO: [%s]\nWE: [%s]\nEA: [%s]\n",
		game->texture->no, game->texture->so,
		game->texture->we, game->texture->ea);
	printf("Floor:   RGB(%d,%d,%d)\n",
		game->floor.r, game->floor.g, game->floor.b);
	printf("Ceiling: RGB(%d,%d,%d)\n",
		game->ceiling.r, game->ceiling.g, game->ceiling.b);
}

void	debug_validate_parsing(t_game *game)
{
	char	**tmp;

	print_sep("VALIDATION CHECK");
	if (!game->map || !game->map->grid)
		return ;

	tmp = copy_grid(game->map->grid, game->map->height);
	if (tmp && !flood_fill(tmp,
			game->map->p_x,
			game->map->p_y,
			game->map->height))
		printf("\033[1;32mMap Integrity: CLOSED (Valid)\033[0m\n");
	else
		printf("\033[1;31mMap Integrity: INVALID\033[0m\n");

	free_tab(tmp);
}
