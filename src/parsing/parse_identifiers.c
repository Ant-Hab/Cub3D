/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:57:42 by achowdhu          #+#    #+#             */
/*   Updated: 2026/02/26 18:04:02 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check if line is a texture or color identifier */
bool	is_identifier_line(char *line)
{
	char	*tmp;
	bool	res;

	tmp = ft_strtrim(line, " \t\n");
	if (!tmp)
		return (false);
	res = (!ft_strncmp(tmp, "NO ", 3)
			|| !ft_strncmp(tmp, "SO ", 3)
			|| !ft_strncmp(tmp, "WE ", 3)
			|| !ft_strncmp(tmp, "EA ", 3)
			|| !ft_strncmp(tmp, "F ", 2)
			|| !ft_strncmp(tmp, "C ", 2));
	free(tmp);
	return (res);
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

/* Splits line and manages memory for identifier extraction */
void	store_identifier(t_game *game, char *line)
{
	char	**tk;
	char	*path;

	tk = ft_split(line, ' ');
	if (!tk)
		return ;
	if (!tk[0] || !tk[1])
	{
		free_tab(tk);
		return ;
	}
	path = ft_strtrim(tk[1], " \n\t");
	if (path)
	{
		assign_texture(game, tk, path);
		free(path);
	}
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

/* Skip identifier lines and return first map line */
char	*skip_to_map_start(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!empty_line(line)
			&& !is_identifier_line(line))
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}
