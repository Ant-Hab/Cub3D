/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:38:15 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/10 15:40:57 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Skips any empty space between IDs and the map grid */
char	*skip_to_map_start(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		if (!empty_line(line))
			return (line);
		free(line);
	}
	return (NULL);
}

/* Picks up exactly where Phase 1 left off and reads grid */
t_list	*read_map_to_list(int fd)
{
	t_list	*lst;
	char	*line;
	char	*tmp;

	lst = NULL;
	line = skip_to_map_start(fd);
	while (line && !empty_line(line))
	{
		tmp = ft_strtrim(line, "\r\n");
		ft_lstadd_back(&lst, ft_lstnew(tmp));
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		if (!empty_line(line))
		{
			ft_lstclear(&lst, free);
			free(line);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (lst);
}

/* Transfers map lines from list to array and calculates maximum width */
void	convert_list_to_grid(t_list *lst, t_map *map)
{
	int		i;
	int		len;
	t_list	*curr;

	map->height = ft_lstsize(lst);
	map->width = 0;
	curr = lst;
	while (curr)
	{
		len = ft_strlen((char *)curr->content);
		if (len > map->width)
			map->width = len;
		curr = curr->next;
	}
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return ;
	curr = lst;
	i = 0;
	while (curr)
	{
		map->grid[i++] = ft_strdup((char *)curr->content);
		curr = curr->next;
	}
}

/* Locates player coordinates and ensures only one start point exists */
int	get_player_pos(t_map *map)
{
	int	x;
	int	y;
	int	p_found;

	p_found = 0;
	y = -1;
	while (map->grid && map->grid[++y])
	{
		x = -1;
		while (map->grid[y][++x])
		{
			if (!ft_strchr("01NSEW ", map->grid[y][x]))
				return (-1);
			if (ft_strchr("NSEW", map->grid[y][x]))
			{
				map->p_x = x;
				map->p_y = y;
				map->start_dir = map->grid[y][x];
				p_found++;
			}
		}
	}
	return (p_found);
}

/* Recursively verifies that the player is fully enclosed by walls */
bool	is_closed(char **grid, int px, int py, int height)
{
	int	y;
	int	x;

	(void)px;
	(void)py;
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (grid[y][++x])
		{
			if (ft_strchr("0NSEW", grid[y][x]))
			{
				if (y == 0 || y == height - 1 || x == 0 || !grid[y][x + 1])
					return (false);
				if (x >= (int)ft_strlen(grid[y - 1]) || grid[y - 1][x] == ' ')
					return (false);
				if (x >= (int)ft_strlen(grid[y + 1]) || grid[y + 1][x] == ' ')
					return (false);
				if (grid[y][x - 1] == ' ' || grid[y][x + 1] == ' ')
					return (false);
			}
		}
	}
	return (true);
}
