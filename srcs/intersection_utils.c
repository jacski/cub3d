/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:00:19 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 19:00:22 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_vert_horiz_intersection(t_intersection *vert)
{
	vert->distance = INFINITY;
	vert->is_valid = 0;
	vert->x = 0;
	vert->y = 0;
}

void	calculate_intercepts(t_intercept_params *params, t_ray_step *step, \
		int *facing_up)
{
	*facing_up = params->angle > 0 && params->angle < M_PI;
	if (*facing_up)
		step->y_intercept = floor(params->start_y);
	else
		step->y_intercept = floor(params->start_y) + 1;
	step->x_intercept = params->start_x + (step->y_intercept - \
		params->start_y) / tan(params->angle);
	step->y_step = 1;
	if (*facing_up)
		step->y_step *= -1;
	step->x_step = -1 / tan(params->angle);
	if (!*facing_up)
		step->x_step *= -1;
}

int	is_facing_right(float angle)
{
	if (angle < M_PI_2 || angle > 3 * M_PI_2)
		return (1);
	return (0);
}

void	set_vertical_start_x(t_intersection *vert, float start_x, \
		int facing_right)
{
	if (facing_right)
		vert->x = floor(start_x);
	else
		vert->x = floor(start_x) + 1;
}
