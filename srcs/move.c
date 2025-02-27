/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:49:23 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 18:49:27 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	can_move(t_game *game, float new_x, float new_y)
{
	float	cx;
	float	cy;
	float	check_points[5][2];
	int		i;

	check_points[0][0] = new_x;
	check_points[0][1] = new_y;
	check_points[1][0] = new_x - PLAYER_RADIUS;
	check_points[1][1] = new_y - PLAYER_RADIUS;
	check_points[2][0] = new_x + PLAYER_RADIUS;
	check_points[2][1] = new_y - PLAYER_RADIUS;
	check_points[3][0] = new_x - PLAYER_RADIUS;
	check_points[3][1] = new_y + PLAYER_RADIUS;
	check_points[4][0] = new_x + PLAYER_RADIUS;
	check_points[4][1] = new_y + PLAYER_RADIUS;
	i = 0;
	while (i < 5)
	{
		cx = check_points[i][0];
		cy = check_points[i][1];
		if (is_wall(cx, cy, game))
			return (0);
		i++;
	}
	return (1);
}

void	move_player(t_game *game, float delta_x, float delta_y)
{
	float	new_x;
	float	new_y;

	new_x = game->player.pos_x + delta_x;
	new_y = game->player.pos_y + delta_y;
	if (can_move(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void	handle_movement(int key, t_game *game)
{
	float	speed;

	speed = game->player.speed;
	if (key == W_KEY)
		move_player(game, -game->player.dir_x * speed, \
			-game->player.dir_y * speed);
	if (key == S_KEY)
		move_player(game, game->player.dir_x * speed, \
			game->player.dir_y * speed);
	if (key == D_KEY)
		move_player(game, game->player.dir_y * speed, \
			-game->player.dir_x * speed);
	if (key == A_KEY)
		move_player(game, -game->player.dir_y * speed, \
			game->player.dir_x * speed);
}

void	handle_rotation(int key, t_game *game)
{
	if (key == LEFT_KEY)
	{
		game->player.angle -= ROTATION_SPEED;
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
	}
	if (key == RIGHT_KEY)
	{
		game->player.angle += ROTATION_SPEED;
		if (game->player.angle > 2 * M_PI)
			game->player.angle -= 2 * M_PI;
	}
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}

int	handle_input(int key, t_game *game)
{
	handle_movement(key, game);
	handle_rotation(key, game);
	if (key == ESC_KEY)
	{
		cleanup_game(game);
		printf("Escape key pressed. Exiting game.\n");
		exit(EXIT_SUCCESS);
	}
	return (0);
}
