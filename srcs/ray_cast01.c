/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:55:36 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 18:55:40 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(float x, float y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(x);
	map_y = (int)floor(y);
	if (map_x < 0 || map_x >= game->config.map.width || \
		map_y < 0 || map_y >= game->config.map.height)
		return (0);
	return (game->config.map.grid[map_y][map_x] == '1');
}

int	is_within_map(float x, float y, t_game *game)
{
	int		grid_x;
	int		grid_y;
	char	cell;

	if (!game || !game->config.map.grid)
		return (0);
	grid_x = (int)floor(x);
	grid_y = (int)floor(y);
	if (grid_x < 0 || grid_x >= game->config.map.width || \
		grid_y < 0 || grid_y >= game->config.map.height || \
		!game->config.map.grid[grid_y])
		return (0);
	if (grid_x >= (int)strlen(game->config.map.grid[grid_y]))
		return (0);
	cell = game->config.map.grid[grid_y][grid_x];
	return (cell == '0' || cell == '1' || cell == 'N' || \
		cell == 'S' || cell == 'W' || cell == 'E');
}

float	calculate_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	set_ray_distance(t_ray_params *params, float distance)
{
	params->distance = distance;
}
