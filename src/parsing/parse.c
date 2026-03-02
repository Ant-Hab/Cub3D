/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:35:24 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/02 16:38:33 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Locates player, checks for single start, and verifies map closure */
static bool	validate_map(t_map *map)
{
	char	**tmp;
	bool	closed;

	if (get_player_pos(map) != 1)
		return (false);
	tmp = copy_grid(map->grid, map->height);
	if (!tmp)
		return (false);
	closed = is_closed(tmp, map->p_x, map->p_y, map->height);
	free_tab(tmp);
	return (closed);
}

/* Stores map lines in a list, then converts to a 2D grid */
static bool	parse_map(t_map *map, char *argv)
{
	int		fd;
	t_list	*lst;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (false);
	lst = read_map_to_list(fd);
	close(fd);
	if (!lst)
		return (false);
	convert_list_to_grid(lst, map);
	ft_lstclear(&lst, free);
	if (map->grid == NULL)
		return (false);
	return (true);
}

/* Processes file until all 6 texture/color IDs are correctly stored */
static bool	open_identifiers(t_game *game, char *argv)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (false);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!all_identifiers_set(game) && !empty_line(line))
			store_identifier(game, line);
		free(line);
		if (all_identifiers_set(game))
			break ;
	}
	close(fd);
	return (all_identifiers_set(game));
}

/* Sets all game pointers to NULL and color values to -1 */
static void	init_game_data(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->floor.r = -1;
	game->ceiling.r = -1;
	game->map->width = 0;
	printf("debug111\n");/// here is the segfault
	game->map->height = 0;
	
}

/* Initiates full parsing and map verification */
t_game	*parse(char *argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	printf("debug1\n");
	init_game_data(game);
	if (!open_identifiers(game, argv))
	{
		printf("Error\nIDs missing or invalid\n");
		return (free_game(game), NULL);
	}
	printf("debug2\n");
	if (!parse_map(game->map, argv))
	{
		printf("Error\nMap parsing failed\n");
		return (free_game(game), NULL);
	}
	printf("debug3\n");
	if (!validate_map(game->map))
	{
		printf("Error\nMap invalid\n");
		return (free_game(game), NULL);
	}
	return (game);
}
