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
# define WIDTH 1920
# define HEIGHT 1080

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

/* Wall texture file paths (North, South, West, East) */
typedef struct s_texture
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;

	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*we_tex;
	mlx_texture_t	*ea_tex;

}	t_texture;

/* RGB color components for floor and ceiling rendering */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;
typedef struct s_player
{

	float	x;
	float	y;

	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	move_speed;
	float	rot_speed;

}	t_player;

/* Map data including the 2D grid, dimensions, and player spawn */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		p_x;
	int		p_y;
	t_player *player;
	char	start_dir;
}	t_map;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	dir_x;
	double	dir_y;
	double	del_dist_x;
	double	del_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit_wall;
	int		hit_axis;
	char	*wall_texture;
	double	distance;
	int		pixel_height;
	int		draw_top;
	int		draw_bottom;
	char	*texture_id;
}	t_ray;

/* Main engine controller holding all data and MiniLibX pointers */
typedef struct s_game
{
	t_texture	*texture;
	t_color		floor;
	t_color		ceiling;
	t_map		*map;
	t_player	*player;
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			width;
	int			height;
	bool		forward;
	bool		back;
	bool		left;
	bool		right;
	bool		rotate_left;
	bool		rotate_right;
}	t_game;


/* Parsing */
bool	parse(t_game *game, char *argv);
bool	is_identifier_line(char *line);
void	store_identifier(t_game *game, char *line);
bool	all_identifiers_set(t_game *game);
char	*skip_to_map_start(int fd);
t_list	*read_map_to_list(int fd);
void	convert_list_to_grid(t_list *lst, t_map *map);
int		get_player_pos(t_map *map);
bool	is_closed(char **grid, int x, int y, int height);
void	init_game_data(t_game *game);
void	store_color(t_color *color, char *path);

/* Utils */
void	free_game(t_game *game);
void	error_exit(t_game *game, char *msg);
void	free_tab(char **tab);
bool	empty_line(char *line);

/* Debug */
void	print_textures(t_game *game);
void	print_map(t_game *game);
void	debug_validate_parsing(t_game *game);

/* Excution*/
void 	play_game(t_game *game, t_map *map);
void	load_textures(t_game *game);
void	init_graphics(t_game *game);
void	init_game_state(t_game *game, t_map *map);
void	init_player_direction(t_player *p, char dir);
/* raycast*/
void 	raycast(t_game *game);
void	draw_ray_column(t_ray *ray, t_game *game, int x);
void 	calculate_wall( t_game *game, t_ray *ray);
void	dda_and_wall(t_game *game, t_ray *ray);
void	init_ray_move(t_game *game,t_ray *ray);
void	init_ray(t_game *game, t_ray *ray, int i);
int 	is_wall(t_game *game, float x, float y);
int 	rgba(int r, int g, int b, int a);
void	movement(t_game *game);
/*mlx*/
mlx_texture_t *texture_selection(t_ray *ray, t_game *game);
int get_texture_column(t_ray *ray, mlx_texture_t *tex, t_player *player);
int get_texture_row(int y, t_ray *ray, mlx_texture_t *tex);
int get_texture_color(mlx_texture_t *tex, int x, int y);
/* free */
void	error_exit(t_game *game, char *msg);
void	free_textures(t_game *game);

/* utils*/
void key_press(mlx_key_data_t keydata, void *param);
void resize(int width, int height, void *param);
void close_window(void *param);

#endif
