/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:43:12 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 18:43:15 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_column_info	calculate_column_info(t_game *game, int x)
{
	t_column_info	info;
	float			camera_x;
	float			perp_wall_dist;
	int				wall_height;

	camera_x = (2.0f * x / game->screen_width) - 1.0f;
	info.ray_angle = normalize_angle(game->player.angle + atan(camera_x * \
		tan(FOV_ANGLE / 2)));
	info.ray = cast_ray(game, game->player.pos_x, game->player.pos_y, \
		info.ray_angle);
	perp_wall_dist = info.ray.distance;
	wall_height = game->screen_height / perp_wall_dist;
	info.wall_top = (game->screen_height / 2) - (wall_height / 2);
	info.wall_bottom = info.wall_top + wall_height;
	return (info);
}

void	draw_ceiling_and_floor(t_game *game, int x, int wall_top, \
		int wall_bottom)
{
	int	y;

	y = 0;
	while (y < wall_top)
	{
		draw_ceiling(game, x, y);
		y++;
	}
	y = wall_bottom;
	while (y < game->screen_height)
	{
		draw_floor(game, x, y);
		y++;
	}
}

void	draw_wall_texture(t_game *game, t_column col, void *texture)
{
	uint32_t	*texture_data;
	uint32_t	color;
	int			tex_x;
	int			tex_y;
	int			y;

	texture_data = (uint32_t *)texture;
	if (col.ray.hit_vertical)
		tex_x = ((int)(col.ray.hit_y * TILE_SIZE) % TILE_SIZE);
	else
		tex_x = ((int)(col.ray.hit_x * TILE_SIZE) % TILE_SIZE);
	tex_x = (tex_x * TILE_SIZE) / TILE_SIZE;
	y = col.wall_top;
	while (y < col.wall_bottom)
	{
		tex_y = ((y - col.wall_top) * game->texture_height) / \
			(col.wall_bottom - col.wall_top);
		color = texture_data[tex_y * game->texture_width + tex_x];
		put_pixel(game, col.x, y, color);
		y++;
	}
}

void	render_column(t_game *game, int x)
{
	uint32_t		*texture;
	t_column		col;
	t_column_info	info;

	info = calculate_column_info(game, x);
	col.x = x;
	col.wall_top = info.wall_top;
	col.wall_bottom = info.wall_bottom;
	col.ray = info.ray;
	if (info.ray.wall_dir == NORTH)
		texture = game->textures[0];
	else if (info.ray.wall_dir == SOUTH)
		texture = game->textures[1];
	else if (info.ray.wall_dir == WEST)
		texture = game->textures[2];
	else
		texture = game->textures[3];
	draw_ceiling_and_floor(game, x, info.wall_top, info.wall_bottom);
	draw_wall_texture(game, col, texture);
}
