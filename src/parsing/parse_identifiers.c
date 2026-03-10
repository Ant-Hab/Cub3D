/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:57:42 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/10 15:37:52 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check if line is a texture or color identifier */
bool	is_identifier_line(char *line)
{
	if (!line)
		return (false);
	while (*line == ' ' || *line == '\t')
		line++;
	if (!ft_strncmp(line, "NO", 2) && (line[2] == ' ' || line[2] == '\t'))
		return (true);
	if (!ft_strncmp(line, "SO", 2) && (line[2] == ' ' || line[2] == '\t'))
		return (true);
	if (!ft_strncmp(line, "WE", 2) && (line[2] == ' ' || line[2] == '\t'))
		return (true);
	if (!ft_strncmp(line, "EA", 2) && (line[2] == ' ' || line[2] == '\t'))
		return (true);
	if (!ft_strncmp(line, "F", 1) && (line[1] == ' ' || line[1] == '\t'))
		return (true);
	if (!ft_strncmp(line, "C", 1) && (line[1] == ' ' || line[1] == '\t'))
		return (true);
	return (false);
}

/* Matches identifier to the correct struct member and duplicates path */
static void	assign_texture(t_game *game, char **tk, char *path)
{
	if (!ft_strcmp(tk[0], "NO"))
	{
		free(game->texture->no);
		game->texture->no = ft_strdup(path);
	}
	else if (!ft_strcmp(tk[0], "SO"))
	{
		free(game->texture->so);
		game->texture->so = ft_strdup(path);
	}
	else if (!ft_strcmp(tk[0], "WE"))
	{
		free(game->texture->we);
		game->texture->we = ft_strdup(path);
	}
	else if (!ft_strcmp(tk[0], "EA"))
	{
		free(game->texture->ea);
		game->texture->ea = ft_strdup(path);
	}
	else if (!ft_strcmp(tk[0], "F"))
		store_color(&game->floor, path);
	else if (!ft_strcmp(tk[0], "C"))
		store_color(&game->ceiling, path);
}

/* Helper to check permissions and assign the path, keeping Norminette happy */
static void	handle_path(t_game *game, char **tk)
{
	char	*path;
	int		fd;

	path = ft_strtrim(tk[1], " \n\r");
	if (!path)
		return ;
	if (tk[0][0] != 'F' && tk[0][0] != 'C')
	{
		fd = open(path, O_RDONLY);
		if (fd >= 0)
		{
			close(fd);
			assign_texture(game, tk, path);
		}
	}
	else
		assign_texture(game, tk, path);
	free(path);
}

/* Splits line, checks file permissions, and manages identifier extraction */
void	store_identifier(t_game *game, char *line)
{
	char	**tk;
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
	}
	tk = ft_split(line, ' ');
	if (!tk || !tk[0] || !tk[1])
	{
		free_tab(tk);
		return ;
	}
	handle_path(game, tk);
	free_tab(tk);
}

/* Check if all required identifiers are set */
bool	all_identifiers_set(t_game *game)
{
	if (!game->texture->no || !game->texture->so
		|| !game->texture->we || !game->texture->ea)
		return (false);
	if (game->floor.r == -1 || game->ceiling.r == -1)
		return (false);
	return (true);
}
