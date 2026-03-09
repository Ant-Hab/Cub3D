/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:27:50 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/09 14:55:14 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Convert RGB string to integer values */
void	store_color(t_color *color, char *path)
{
	char	**rgb;

	rgb = ft_split(path, ',');
	if (!rgb)
		return ;
	if (rgb[0] && rgb[1] && rgb[2])
	{
		color->r = ft_atoi(rgb[0]);
		color->g = ft_atoi(rgb[1]);
		color->b = ft_atoi(rgb[2]);
	}
	free_tab(rgb);
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

/* Duplicates the grid into a new array for flood-fill validation */
char	**copy_grid(char **grid, int height)
{
	char	**copy;
	int		i;

	if (!grid)
		return (NULL);
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i <= height)
		copy[i++] = NULL;
	i = 0;
	while (i < height && grid[i])
	{
		copy[i] = ft_strdup(grid[i]);
		if (!copy[i])
			return (free_tab(copy), NULL);
		i++;
	}
	return (copy);
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
				return (-1); /* Invalid character found! */
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
bool	is_closed(char **grid, int x, int y, int height)
{
	if (y < 0 || y >= height || x < 0 || !grid[y])
		return (false);
	if (x >= (int)ft_strlen(grid[y]))
		return (false);
	if (grid[y][x] == ' ')
		return (false);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (true);
	grid[y][x] = 'V';
	if (!is_closed(grid, x + 1, y, height))
		return (false);
	if (!is_closed(grid, x - 1, y, height))
		return (false);
	if (!is_closed(grid, x, y + 1, height))
		return (false);
	if (!is_closed(grid, x, y - 1, height))
		return (false);
	return (true);
}
