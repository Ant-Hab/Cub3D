/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:35:24 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/10 15:37:36 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Locates player, checks for single start, and verifies map closure */
static bool	validate_map(t_map *map)
{
	int	players;

	players = get_player_pos(map);
	if (players == -1 || players != 1)
		return (false);
	return (is_closed(map->grid, map->p_x, map->p_y, map->height));
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
		{
			if (!is_identifier_line(line))
			{
				free(line);
				return (false);
			}
			store_identifier(game, line);
		}
		free(line);
	}
	return (all_identifiers_set(game));
}

/* Helper to print errors, close fd safely, and free game to save lines */
static bool	parse_error(t_game *game, int fd, char *msg)
{
	printf("Error\n%s\n", msg);
	if (fd >= 0)
		close(fd);
	free_game(game);
	return (false);
}

/* One pass parsing: Opens file once, parses IDs, then maps grid sequentially */
bool	parse(t_game *game, char *argv)
{
	int	fd;

	init_game_data(game);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (parse_error(game, -1, "Cannot open map file"));
	if (!parse_identifiers(game, fd))
		return (parse_error(game, fd, "IDs missing or invalid"));
	if (!parse_map_from_fd(game->map, fd))
		return (parse_error(game, fd, "Map parsing failed"));
	close(fd);
	if (!validate_map(game->map))
		return (parse_error(game, -1, "Map invalid"));
	return (true);
}
