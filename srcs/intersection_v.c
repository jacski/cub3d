/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_v.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:59:45 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 18:59:48 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_vertical_start_y(t_intersection *vert, float start_x, \
		float start_y, float angle)
{
	vert->y = start_y + (vert->x - start_x) * tan(angle);
}

void	calculate_vertical_steps(float *x_step, float *y_step, float angle, \
		int facing_right)
{
	if (facing_right)
		*x_step = -1;
	else
		*x_step = 1;
	*y_step = (*x_step) * tan(angle);
}

float	get_wall_check_x(float vert_x, int facing_right)
{
	if (facing_right)
		return (vert_x - 1);
	return (vert_x);
}

int	check_vertical_wall_collision(t_intersection *vert, t_game *game, \
		float check_x)
{
	if (is_wall(check_x, vert->y, game))
	{
		vert->is_valid = 1;
		return (1);
	}
	return (0);
}

t_intersection	calculate_vertical_intersection(t_game *game, float start_x, \
	float start_y, float angle)
{
	t_intersection	vert;
	float			x_step;
	float			y_step;
	int				facing_right;
	float			check_x;

	init_vert_horiz_intersection(&vert);
	facing_right = is_facing_right(angle);
	set_vertical_start_x(&vert, start_x, facing_right);
	set_vertical_start_y(&vert, start_x, start_y, angle);
	calculate_vertical_steps(&x_step, &y_step, angle, facing_right);
	while (is_within_map(vert.x, vert.y, game))
	{
		check_x = get_wall_check_x(vert.x, facing_right);
		if (check_vertical_wall_collision(&vert, game, check_x))
		{
			vert.distance = calculate_distance(start_x, start_y, vert.x, \
				vert.y) * cos(angle - game->player.angle);
			return (vert);
		}
		vert.x += x_step;
		vert.y += y_step;
	}
	return (vert);
}
