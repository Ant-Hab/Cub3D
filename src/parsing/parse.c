/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:35:24 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/05 14:42:55 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Locates player, checks for single start, and verifies map closure */
static bool	validate_map(t_map *map)
{
	char	**tmp;
	bool	closed;
	int		players;

	players = get_player_pos(map);
	if (players != 1)
		return (false);
	tmp = copy_grid(map->grid, map->height);
	if (!tmp)
		return (false);
	closed = is_closed(tmp, map->p_x, map->p_y, map->height);
	free_tab(tmp);
	return (closed);
}

/* Converts list to grid directly using the fd passed from phase 1 */
static bool	parse_map_from_fd(t_map *map, int fd)
{
	t_list	*lst;

	lst = read_map_to_list(fd);
	if (!lst)
		return (false);
	convert_list_to_grid(lst, map);
	ft_lstclear(&lst, free);
	if (map->grid == NULL || map->grid[0] == NULL)
		return (false);
	return (true);
}

/* Phase 1: Reads until all 6 identifiers are set */
static bool	parse_identifiers(t_game *game, int fd)
{
	char	*line;

	while (!all_identifiers_set(game))
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!empty_line(line))
			store_identifier(game, line);
		free(line);
	}
	return (all_identifiers_set(game));
}

/* Sets all game pointers to NULL and color values to -1 */
void	init_game_data(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->texture = malloc(sizeof(t_texture));
	game->map = malloc(sizeof(t_map));
	game->player = malloc(sizeof(t_player));
	if (!game->texture || !game->map || !game->player)
		error_exit(game, "Malloc failed");
	ft_bzero(game->texture, sizeof(t_texture));
	ft_bzero(game->map, sizeof(t_map));
	ft_bzero(game->player, sizeof(t_player));
	game->floor.r = -1;
	game->ceiling.r = -1;
}

/* Opens the file once, reads textures and colors, then reads the map */
bool	parse(t_game *game, char *argv)
{
	int	fd;

	init_game_data(game);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (free_game(game), false);
	if (!parse_identifiers(game, fd))
	{
		printf("Error\nIDs missing or invalid\n");
		return (close(fd), free_game(game), false);
	}
	if (!parse_map_from_fd(game->map, fd))
	{
		printf("Error\nMap parsing failed\n");
		return (close(fd), free_game(game), false);
	}
	close(fd);
	if (!validate_map(game->map))
	{
		printf("Error\nMap invalid\n");
		return (free_game(game), false);
	}
	return (true);
}
