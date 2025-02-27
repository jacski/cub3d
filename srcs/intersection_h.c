/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_h.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:59:12 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 18:59:18 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	get_checked_y(float next_y, float angle)
{
	if (angle > 0 && angle < M_PI)
		return (next_y - 1);
	return (next_y);
}

int	update_intersection_if_wall(t_intersection_params *inter_params)
{
	inter_params->result->x = inter_params->next_x;
	inter_params->result->y = inter_params->next_y;
	inter_params->result->distance = calculate_distance(\
	inter_params->params->start_x, inter_params->params->start_y, \
	inter_params->next_x, inter_params->next_y) \
	* cos(inter_params->params->angle - inter_params->game->player.angle);
	inter_params->result->is_valid = 1;
	return (1);
}

int	check_wall_and_update(t_intersection_params *inter_params, float next_x, \
		float next_y, float check_y)
{
	inter_params->next_x = next_x;
	inter_params->next_y = next_y;
	if (is_wall(next_x, check_y, inter_params->game))
	{
		if (update_intersection_if_wall(inter_params))
			return (1);
	}
	return (0);
}

t_intersection	traverse_horizontal_ray(t_game *game, \
		t_intercept_params *params, t_ray_step *step)
{
	t_intersection			result;
	t_intersection_params	inter_params;
	float					next_x;
	float					next_y;
	float					check_y;

	init_vert_horiz_intersection(&result);
	next_x = step->x_intercept;
	next_y = step->y_intercept;
	inter_params.result = &result;
	inter_params.game = game;
	inter_params.params = params;
	while (is_within_map(next_x, next_y, game))
	{
		check_y = get_checked_y(next_y, params->angle);
		if (check_y < 0 || check_y >= game->config.map.height)
			break ;
		if (check_wall_and_update(&inter_params, next_x, next_y, check_y))
			return (*(inter_params.result));
		next_x += step->x_step;
		next_y += step->y_step;
	}
	return (result);
}

t_intersection	calculate_horizontal_intersection(t_game *game, \
		t_intercept_params *params)
{
	t_intersection	result;
	t_ray_step		step;
	int				facing_up;

	init_vert_horiz_intersection(&result);
	calculate_intercepts(params, &step, &facing_up);
	result = traverse_horizontal_ray(game, params, &step);
	return (result);
}
