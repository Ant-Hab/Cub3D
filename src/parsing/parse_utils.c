/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:07:18 by achowdhu          #+#    #+#             */
/*   Updated: 2026/02/19 15:54:33 by achowdhu         ###   ########.fr       */
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
	t_list	*curr;

	map->height = ft_lstsize(lst);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return ;
	curr = lst;
	i = 0;
	while (curr)
	{
		map->grid[i] = ft_strdup(curr->content);
		if ((int)ft_strlen(map->grid[i]) > map->width)
			map->width = ft_strlen(map->grid[i]);
		i++;
		curr = curr->next;
	}
	map->grid[i] = NULL;
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
	while (i < height && grid[i])
	{
		copy[i] = ft_strdup(grid[i]);
		if (!copy[i])
		{
			free_tab(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/* Locates player coordinates and ensures only one start point exists */
int	get_player_pos(t_map *map)
{
	int	x;
	int	y;
	int	p_found;

	y = -1;
	p_found = 0;
	while (map->grid[++y])
	{
		x = -1;
		while (map->grid[y][++x])
		{
			if (ft_strchr("NSEW", map->grid[y][x]))
			{
				p_found++;
				map->p_x = x;
				map->p_y = y;
			}
		}
	}
	return (p_found);
}

/* Recursively verifies that the player is fully enclosed by walls */
bool	is_closed(char **grid, int x, int y, int height)
{
	if (y < 0 || y >= height || x < 0 || !grid[y] || !grid[y][x]
		|| grid[y][x] == ' ')
		return (false);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (true);
	grid[y][x] = 'V';
	return (is_closed(grid, x + 1, y, height)
		&& is_closed(grid, x - 1, y, height)
		&& is_closed(grid, x, y + 1, height)
		&& is_closed(grid, x, y - 1, height));
}
