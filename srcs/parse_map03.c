/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map03.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:25:02 by jkalinow          #+#    #+#             */
/*   Updated: 2025/03/16 13:25:08 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	t_coordinates			coordinates;
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
