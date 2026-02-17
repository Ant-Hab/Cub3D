/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:26:12 by achowdhu          #+#    #+#             */
/*   Updated: 2026/01/27 14:26:30 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_game
{
	t_texture	textures;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
}	t_game;

/* Parsing */
void	parse(char *path, t_game *game);

/* Game Logic */
void	setup_run_game(t_game *game);

/* Utils & Memory */
void	error_exit(t_game *game, char *msg);
void	free_game(t_game *game);

#endif
