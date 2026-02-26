/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:27:50 by achowdhu          #+#    #+#             */
/*   Updated: 2026/02/26 17:45:27 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return ;
	curr = lst;
	i = 0;
	while (curr)
	{
		map->grid[i] = ft_strdup(curr->content);
		if (!map->grid[i])
		{
			free_tab(map->grid);
			map->grid = NULL;
			return ;
		}
		if ((int)ft_strlen(map->grid[i]) > map->width)
			map->width = ft_strlen(map->grid[i]);
		i++;
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
		{
			free_tab(copy);
			return (NULL);
		}
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
	int	row_len;

	if (y < 0 || y >= height || !grid[y])
		return (false);
	row_len = (int)ft_strlen(grid[y]);
	if (x < 0 || x >= row_len || grid[y][x] == ' ')
		return (false);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (true);
	grid[y][x] = 'V';
	if (!is_closed(grid, x + 1, y, height)
		|| !is_closed(grid, x - 1, y, height)
		|| !is_closed(grid, x, y + 1, height)
		|| !is_closed(grid, x, y - 1, height))
		return (false);
	return (true);
}

/* Helper to read file lines into a list */
t_list	*read_map_to_list(int fd)
{
	t_list	*lst;
	t_list	*new_node;
	char	*line;

	lst = NULL;
	line = skip_to_map_start(fd);
	while (line)
	{
		new_node = ft_lstnew(ft_strdup(line));
		if (!new_node)
		{
			free(line);
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, new_node);
		free(line);
		line = get_next_line(fd);
	}
	return (lst);
}
