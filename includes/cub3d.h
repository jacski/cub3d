/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:01:43 by jkalinow          #+#    #+#             */
/*   Updated: 2025/01/15 14:01:45 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <ctype.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include "../minilibx-linux/mlx.h"
//# include "../libft/libft.h"

# define MAX_LINE_LENGTH 1024
# define MAX_ROWS 100
# define MAX_COLS 100
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define FOV_ANGLE 1.047
# define TILE_SIZE 64 
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define ESC_KEY 65307

# define ROTATION_SPEED 0.05f
# define PLAYER_RADIUS 0.2f

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	angle;
	float	speed;
	float	rot_speed;
}	t_player;

typedef struct s_config
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	t_map	map;
}	t_config;

typedef struct s_game
{
	int			screen_width;
	int			screen_height;
	t_config	config;
	int			is_running;
	void		*mlx;
	void		*win;
	void		*renderer;
	t_player	player;
	int			floor_color;
	int			ceiling_color;
	int			texture_width;
	int			texture_height;
	void		*textures_img[4];
	uint32_t	*textures[4];
	void		*img;
	char		*img_data;
	int			img_width;
	int			img_height;
}	t_game;

typedef enum t_wall_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_wall_direction;

typedef struct s_ray
{
	float				x;
	float				y;
	float				angle;
	float				distance;
	int					hit_vertical;
	int					hit;
	float				hit_x;
	float				hit_y;
	t_wall_direction	wall_dir;
}	t_ray;

typedef struct s_intersection
{
	float	x;
	float	y;
	float	distance;
	int		is_valid;
}	t_intersection;

typedef struct s_column_info
{
	float	ray_angle;
	t_ray	ray;
	int		wall_top;
	int		wall_bottom;
	int		wall_height;
	float	perp_wall_dist;
}	t_column_info;

typedef struct s_column
{
	int		x;
	int		wall_top;
	int		wall_bottom;
	t_ray	ray;
}	t_column;

typedef struct s_ray_params
{
	float	distance;
	int		hit_vertical;
	float	hit_x;
	float	hit_y;
	int		wall_dir;
}	t_ray_params;

typedef struct s_intercept_params
{
	float	start_x;
	float	start_y;
	float	angle;
}	t_intercept_params;

typedef struct s_ray_step
{
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
}	t_ray_step;

typedef struct s_intersection_params
{
	t_intersection		*result;
	t_game				*game;
	t_intercept_params	*params;
	float				next_x;
	float				next_y;
}	t_intersection_params;

typedef struct s_coordinates
{
	int	x;
	int	y;
}	t_coordinates;

typedef struct s_map_size
{
	int	rows;
	int	cols;
}	t_map_size;

char			*ft_strdup(const char *str);
size_t			ft_strspn(char *s, char *accept);
void			print_error(const char *message);
char			*trim_spaces(const char *line);
char			*parse_texture_path(const char *line);
int				is_digit(char c);
int				parse_color_component(const char *str, int *value);
void			write_number_to_buffer(int num, char *buffer, int *index);
void			reverse_buffer(char *buffer, int index);
void			write_int(int num);
void			write_error(const char *message);
void			write_error_with_string(const char *message, \
				const char *detail);
int				check_missing_comma(const char *line, int i);
int				parse_color_component_and_validate(const char *line, \
					int *i, int *color, int j);
int				parse_color(const char *line, int *color);
int				file_exists(const char *path);
void			handle_texture_line(const char *line, char **texture, \
				const char *texture_name);
void			handle_color_line(const char *line, int *color, \
				const char *color_name);
void			parse_configuration_line(const char *line, t_config *config);
int				is_configuration_line(const char *line);
int				find_first_non_space_index(const char *row);
int				find_last_non_space_index(const char *row);
void			copy_map_to_temp(char temp_map[MAX_ROWS][MAX_COLS], \
				char *map[], int rows, int cols);
int				validate_map_characters(char temp_map[MAX_ROWS][MAX_COLS], \
				char *map[], int rows, int cols);
int				is_map_boundary_invalid(char temp_map[MAX_ROWS][MAX_COLS], \
		t_coordinates *c, int rows, t_coordinates *se);
int				check_map_cell(t_coordinates *c, t_coordinates *se, \
		char temp_map[MAX_ROWS][MAX_COLS], int *has_start);
int				validate_map_boundaries(char temp_map[MAX_ROWS][MAX_COLS], \
				char *map[], t_map_size *size, int *has_start);
int				validate_map(char *map[], int rows, int cols);
int				find_map_start(char **lines, int line_count);
void			calculate_map_dimensions(char **lines, int map_start, \
				int line_count, t_map_size *size);
char			**extract_map(char **lines, int line_count, int *rows, \
				int *cols);
void			read_map_lines(int fd, char *lines[1024], int *line_count);
void			read_map_file(const char *file_path, char *lines[1024], \
				int *line_count);
void			parse_map_config(char *lines[1024], int line_count, \
				t_game *game);
void			extract_and_validate_map(char *lines[1024], int line_count, \
				t_game *game);
void			set_player_angle(t_game *game, char tile);
int				is_player_start_position(char tile, t_coordinates *coordinates, \
					int cols, char **map_grid);
void			assign_player_position(t_game *game, int x, int y, char tile);
void			check_multiple_players(int *found_player, t_game *game, \
				t_coordinates *coordinates, char tile);
void			check_no_player_found(int found_player);
void			locate_player(char **map_grid, int rows, int cols, \
				t_game *game);
void			parse_map_file(const char *file_path, t_game *game);
void			free_textures(t_game *game);
void			free_map_grid(t_config *config);
void			free_textures_c(t_config *config);
void			cleanup_game(t_game *game);
void			load_texture(t_game *game, const char *path, int texture_index);
void			initialize_textures(t_game *game);
void			validate_game_config(t_config *config);
void			setup_game(t_game *game);
int				is_wall(float x, float y, t_game *game);
int				is_within_map(float x, float y, t_game *game);
float			calculate_distance(float x1, float y1, float x2, float y2);
void			init_vert_horiz_intersection(t_intersection *vert);
void			calculate_intercepts(t_intercept_params *params, \
				t_ray_step *step, int *facing_up);
float			get_checked_y(float next_y, float angle);
int				update_intersection_if_wall(t_intersection_params \
					*inter_params);
int				check_wall_and_update(t_intersection_params *inter_params, \
					float next_x, float next_y, float check_y);
t_intersection	traverse_horizontal_ray(t_game *game, \
		t_intercept_params *params, t_ray_step *step);
t_intersection	calculate_horizontal_intersection(t_game *game, \
		t_intercept_params *params);
int				is_facing_right(float angle);
void			set_vertical_start_x(t_intersection *vert, float start_x, \
				int facing_right);
void			set_vertical_start_y(t_intersection *vert, float start_x, \
				float start_y, float angle);
void			calculate_vertical_steps(float *x_step, float *y_step, \
				float angle, int facing_right);
float			get_wall_check_x(float vert_x, int facing_right);
int				check_vertical_wall_collision(t_intersection *vert, \
			t_game *game, float check_x);
t_intersection	calculate_vertical_intersection(t_game *game, float start_x, \
	float start_y, float angle);
float			normalize_angle(float angle);
void			set_ray_distance(t_ray_params *params, float distance);
void			set_ray_hit_info(t_ray_params *params, int hit_vertical, \
			float hit_x, float hit_y);
void			set_wall_direction(t_ray_params *params, float angle, \
			int is_vertical);
void			init_ray(t_ray *ray, t_ray_params *params);
void			set_ray_params(t_ray_params *ray_params, \
			t_intersection *intersection, int hit_vertical, \
				float angle);
t_ray			cast_ray(t_game *game, float start_x, float start_y, \
				float angle);
int				can_move(t_game *game, float new_x, float new_y);
void			move_player(t_game *game, float delta_x, float delta_y);
void			handle_movement(int key, t_game *game);
void			handle_rotation(int key, t_game *game);
int				handle_input(int key, t_game *game);
void			init_mlx_and_dimensions(t_game *game);
void			init_player(t_game *game);
void			init_config(t_game *game);
void			init_game(t_game *game);
void			clear_screen(t_game *game, uint32_t background_color);
void			put_pixel(t_game *game, int x, int y, uint32_t color);
uint32_t		rgb_to_uint32(int r, int g, int b);
void			draw_ceiling(t_game *game, int x, int y);
void			draw_floor(t_game *game, int x, int y);
t_column_info	calculate_column_info(t_game *game, int x);
void			draw_ceiling_and_floor(t_game *game, int x, int wall_top, \
		int wall_bottom);
void			draw_wall_texture(t_game *game, t_column col, void *texture);
void			render_column(t_game *game, int x);
int				game_loop(t_game *game);
int				handle_exit(t_game *game);
int				handle_keypress(int key, t_game *game);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
int				validate_arguments(int argc, char *filename);
int				start_game(t_game *game, char *map_file);
int				main(int argc, char **argv);

#endif
