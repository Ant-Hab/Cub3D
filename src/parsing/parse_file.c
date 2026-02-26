/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:35:24 by achowdhu          #+#    #+#             */
/*   Updated: 2026/02/17 14:52:00 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_file_type(char *path, t_game *game)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		error_exit(game, "Invalid file type: expected .cub");
}

static void	parse_metadata(int fd, t_game *game)
{
	(void)fd;
	(void)game;
	/* Logic for textures and colors goes here */
}

static void	parse_map_data(int fd, t_game *game)
{
	(void)fd;
	(void)game;
	/* Logic for the grid and flood fill goes here */
}

void	parse(char *path, t_game *game)
{
	int	fd;

	check_file_type(path, game);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(game, NULL);
	parse_metadata(fd, game);
	parse_map_data(fd, game);
	close(fd);
}
