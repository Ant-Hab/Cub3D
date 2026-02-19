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
# include <stdbool.h>
# include "../libft/include/libft.h"

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
	int		p_x;
	int		p_y;
}	t_map;

typedef struct s_game
{
	t_texture	textures;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	void		*mlx;
	void		*win;
}	t_game;

/* Parsing */
t_game	*parse(char *argv);
bool	is_identifier_line(char *line);
void	store_identifier(t_game *game, char *line);
bool	all_identifiers_set(t_game *game);
char	*skip_to_map_start(int fd);
void	store_color(t_color *color, char *path);
void	convert_list_to_grid(t_list *lst, t_map *map);
char	**copy_grid(char **grid, int height);
int		get_player_pos(t_map *map);
bool	is_closed(char **grid, int x, int y, int height);

/* Utils */
void	error_exit(t_game *game, char *msg);
void	free_game(t_game *game);
void	free_tab(char **tab);
int		flood_fill(char **copy, int x, int y, int max_y);
bool	empty_line(char *line);


/* Debug */
void	print_textures(t_game *game);
void	print_map(t_map *map);
void    debug_validate_parsing(t_game *game);

#endif

// refer Data Structure

// typedef struct s_player
// {
// 	double	x;
// 	double	y;
// 	char	view;
// 	double	dir_x;
// 	double	dir_y;
// 	double	plane_x;
// 	double	plane_y;
// }	t_player;

// typedef struct s_map
// {
// 	char			**chart;
// 	int				max_x;
// 	int				max_y;
// 	int				start_line;
// 	t_player		*player;
// 	uint32_t		floor_color;
// 	uint32_t		ceil_color;
// 	char			*north;
// 	char			*south;
// 	char			*west;
// 	char			*east;
// 	mlx_texture_t	*north_tex;
// 	mlx_texture_t	*south_tex;
// 	mlx_texture_t	*west_tex;
// 	mlx_texture_t	*east_tex;
// }	t_map;

// typedef struct s_game
// {
// 	t_map		*map;
// 	t_player	*player;
// 	mlx_t		*mlx;
// 	mlx_image_t	*img;
// 	int			width;
// 	int			height;
// 	bool		forward;
// 	bool		back;
// 	bool		left;
// 	bool		right;
// 	bool		rotate_left;
// 	bool		rotate_right;
// }	t_game;

// typedef struct s_ray_dir
// {
// 	double	camera_x;
// 	double	dir_x;
// 	double	dir_y;
// 	int		map_x;
// 	int		map_y;
// 	double	side_dist_x;
// 	double	side_dist_y;
// 	double	delta_dist_x;
// 	double	delta_dist_y;
// 	int		step_x;
// 	int		step_y;
// 	int		hit_wall;
// 	int		side;
// }	t_ray_dir;

// typedef struct s_ray_wall
// {
// 	double	perp_dist;
// 	int		line_height;
// 	int		start_draw;
// 	int		end_draw;
// 	int		texture;
// }	t_ray_wall;

// typedef struct s_ray
// {
// 	t_ray_dir	dir;
// 	t_ray_wall	wall;
// }	t_ray;
