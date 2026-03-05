/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:35:45 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/05 15:07:36 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Prints error message, frees allocated game memory, and exits program */
void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_textures(game);
	if (game->texture)
		free(game->texture);
	if (game->player)
		free(game->player);
	if (game->map)
	{
		if (game->map->grid)
			free_tab(game->map->grid);
		free(game->map);
	}
	if (game->mlx && game->img)
		mlx_delete_image(game->mlx, game->img);
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

/* Checks if a line is empty or contains only whitespace characters */
bool	empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (true);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'
			|| line[i] == '\n' || line[i] == '\r'))
		i++;
	return (line[i] == '\0');
}

/*Picks up exactly where Phase 1 left off and reads grid */
t_list	*read_map_to_list(int fd)
{
	t_list	*lst;
	char	*line;
	char	*tmp;

	lst = NULL;
	line = skip_to_map_start(fd);
	while (line)
	{
		if (empty_line(line))
		{
			free(line);
			break ;
		}
		tmp = ft_strtrim(line, "\r\n");
		ft_lstadd_back(&lst, ft_lstnew(tmp));
		free(line);
		line = get_next_line(fd);
	}
	return (lst);
}
