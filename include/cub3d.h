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
# include <../MLX42/include/MLX42/MLX42.h>

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


typedef struct s_player
{
	// 현재 위치 (x, y)
	float	x;
	float	y;

	// 방향 벡터
	float	dir_x;
	float	dir_y;

	// 카메라 평면 벡터 (2D 레이캐스팅용)
	float	plane_x;
	float	plane_y;

	// 이동/회전 속도
	float	move_speed;
	float	rot_speed;

}	t_player;

typedef struct s_ray
{
	// 현재 레이가 위치한 맵 칸
	int		map_x;
	int		map_y;
	// 레이 방향 벡터
	double	dir_x;
	double	dir_y;
	// DDA에서 레이가 한 칸 이동할 때 실제로 이동하는 거리 delta_distance
	double	del_dist_x;
	double	del_dist_y;
	// 다음 격자선까지 거리
	double	side_dist_x;
	double	side_dist_y;
	// 이동 방향 (-1 or 1)
	int		step_x;
	int		step_y;
	// 벽 충돌 여부
	int		hit_wall;
	// 어떤 축의 벽인지 (0 = x, 1 = y)
	int		hit_axis;
	char	*wall_texture;
	double	distance;    // 플레이어~벽 직선 거리
	int		pixel_height; // 화면에서 벽 높이
	int		draw_top;     // 화면에서 그릴 시작점
	int		draw_bottom;  // 화면에서 그릴 끝점
	char	*texture_id;
}	t_ray;

/* Main engine controller holding all data and MiniLibX pointers */
typedef struct s_game
{
	t_texture	*texture;
	t_color		floor;
	t_color		ceiling;
	t_map		*map;
	t_player	*player;      // player struct inneed
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			width;
	int			height;

	// key 
	bool		forward;
	bool		back;
	bool		left;
	bool		right;
	bool		rotate_left;
	bool		rotate_right;
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
t_list	*read_map_to_list(int fd);

/* Utils */
void	error_exit(t_game *game, char *msg);
void	free_game(t_game *game);
void	free_tab(char **tab);
int		flood_fill(char **copy, int x, int y, int max_y);
bool	empty_line(char *line);

/* Debug */
void	print_textures(t_game *game);
void	print_map(t_map *map);
void	debug_validate_parsing(t_game *game);


/* Excution*/
void 	play_game(t_game *game, t_map *map);
void	load_textures(t_game *game);

/* free */
void	error_exit(t_game *game, char *msg);
void	free_textures(t_game *game);

/* utils*/
int key_press(mlx_key_data_t keydata, void *param);
int resize(int width, int height, void *param);
void close_window(void *param);
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
