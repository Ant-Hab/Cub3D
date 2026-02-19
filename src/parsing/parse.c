/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:35:24 by achowdhu          #+#    #+#             */
/*   Updated: 2026/02/19 16:06:47 by achowdhu         ###   ########.fr       */
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
	char	*line;
	t_list	*lst;

	lst = NULL;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (false);
	line = skip_to_map_start(fd);
	while (line)
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(line)));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!lst)
		return (false);
	convert_list_to_grid(lst, map);
	ft_lstclear(&lst, free);
	return (map->grid != NULL);
}

/* Processes file until all 6 texture/color IDs are correctly stored */
static bool	open_identifiers(t_game *game, char *argv)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		if (!all_identifiers_set(game) && !empty_line(line))
			store_identifier(game, line);
		free(line);
		if (all_identifiers_set(game))
			break ;
		line = get_next_line(fd);
	}
	while (all_identifiers_set(game))
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
	close(fd);
	return (all_identifiers_set(game));
}

/* Sets all game pointers to NULL and color values to -1 */
static void	init_game_data(t_game *game)
{
	game->textures.no = NULL;
	game->textures.so = NULL;
	game->textures.we = NULL;
	game->textures.ea = NULL;
	game->floor.r = -1;
	game->ceiling.r = -1;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->mlx = NULL;
	game->win = NULL;
}

/* Initiates full parsing and map verification */
t_game	*parse(char *argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	init_game_data(game);
	if (!open_identifiers(game, argv))
	{
		printf("Error\nIDs missing or invalid\n");
		free_game(game);
		return (NULL);
	}
	if (!parse_map(&game->map, argv) || !validate_map(&game->map))
	{
		printf("Error\nMap invalid\n");
		free_game(game);
		return (NULL);
	}
	return (game);
}
