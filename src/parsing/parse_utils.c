/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:27:50 by achowdhu          #+#    #+#             */
/*   Updated: 2026/03/10 15:38:35 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Sets all game pointers to NULL and color values to -1 */
void	init_game_data(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->texture = malloc(sizeof(t_texture));
	game->map = malloc(sizeof(t_map));
	game->player = malloc(sizeof(t_player));
	if (!game->texture || !game->map || !game->player)
		error_exit(game, "Malloc failed");
	ft_bzero(game->texture, sizeof(t_texture));
	ft_bzero(game->map, sizeof(t_map));
	ft_bzero(game->player, sizeof(t_player));
	game->floor.r = -1;
	game->ceiling.r = -1;
}

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
