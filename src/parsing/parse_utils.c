/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:27:50 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/10 14:06:17 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Convert RGB string to integer values */
void	store_color(t_color *color, char *path)
{
	char	**rgb;
	int		i;
	int		commas;

	i = -1;
	commas = 0;
	while (path[++i])
	{
		if (path[i] == ',')
			commas++;
		else if (!ft_isdigit(path[i]) && path[i] != ' ' && path[i] != '\t')
			return ;
	}
	if (commas != 2)
		return ;
	rgb = ft_split(path, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_tab(rgb));
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r > 255 || color->g > 255 || color->b > 255)
		color->r = -1;
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
