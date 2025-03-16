/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:18:31 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 18:18:36 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	extract_and_validate_map(char *lines[1024], int line_count, \
		t_game *game)
{
	int		rows;
	int		cols;
	char	**map_grid;

	map_grid = extract_map(lines, line_count, &rows, &cols);
	if (!map_grid)
	{
		print_error("Failed to extract map");
		exit(EXIT_FAILURE);
	}
	if (!validate_map(map_grid, rows, cols))
	{
		print_error("Invalid map structure");
		exit(EXIT_FAILURE);
	}
	game->config.map.grid = map_grid;
	game->config.map.width = cols;
	game->config.map.height = rows;
}

void	set_player_angle(t_game *game, char tile)
{
	if (tile == 'N')
		game->player.angle = (float)M_PI / 2;
	else if (tile == 'S')
		game->player.angle = (float)3 * M_PI / 2;
	else if (tile == 'E')
		game->player.angle = (float)0;
	else if (tile == 'W')
		game->player.angle = (float)M_PI;
}

int	is_player_start_position(char tile, t_coordinates *coordinates, \
		int cols, char **map_grid)
{
	int	x;
	int	y;

	x = coordinates->x;
	y = coordinates->y;
	return ((tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W') && \
		x != 0 && x != cols - 1 && map_grid[y][x - 1] != ' ' && \
		map_grid[y][x + 1] != ' ');
}

void	assign_player_position(t_game *game, int x, int y, char tile)
{
	game->player.pos_x = (float)x + 0.5f;
	game->player.pos_y = (float)y + 0.5f;
	set_player_angle(game, tile);
	game->config.map.grid[y][x] = '0';
}

void	check_multiple_players(int *found_player, t_game *game, \
		t_coordinates *coordinates, char tile)
{
	if (*found_player)
	{
		print_error("Multiple player start positions found");
		exit(EXIT_FAILURE);
	}
	assign_player_position(game, coordinates->x, coordinates->y, tile);
	*found_player = 1;
}
