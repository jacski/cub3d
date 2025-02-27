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

void	check_no_player_found(int found_player)
{
	if (!found_player)
	{
		print_error("No player start position found");
		exit(EXIT_FAILURE);
	}
}

void	locate_player(char **map_grid, int rows, int cols, t_game *game)
{
	t_coordinates	coordinates;
	int						found_player;
	int						y;
	int						x;
	char					tile;

	found_player = 0;
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < (int)strlen(map_grid[y]))
		{
			tile = map_grid[y][x];
			coordinates.x = x;
			coordinates.y = y;
			if (is_player_start_position(tile, &coordinates, cols, map_grid))
				check_multiple_players(&found_player, game, &coordinates, tile);
			x++;
		}
		y++;
	}
	check_no_player_found(found_player);
}
