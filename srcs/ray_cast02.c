/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:55:45 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 18:55:48 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_ray_hit_info(t_ray_params *params, int hit_vertical, float hit_x, \
		float hit_y)
{
	params->hit_vertical = hit_vertical;
	params->hit_x = hit_x;
	params->hit_y = hit_y;
}

void	set_wall_direction(t_ray_params *params, float angle, int is_vertical)
{
	if (is_vertical)
	{
		if (angle < M_PI_2 || angle > 3 * M_PI_2)
			params->wall_dir = WEST;
		else
			params->wall_dir = EAST;
	}
	else
	{
		if (angle > 0 && angle < M_PI)
			params->wall_dir = SOUTH;
		else
			params->wall_dir = NORTH;
	}
}

void	init_ray(t_ray *ray, t_ray_params *params)
{
	ray->distance = params->distance;
	ray->hit_vertical = params->hit_vertical;
	ray->hit_x = params->hit_x;
	ray->hit_y = params->hit_y;
	ray->wall_dir = params->wall_dir;
}

void	set_ray_params(t_ray_params *ray_params, t_intersection *intersection, \
		int hit_vertical, float angle)
{
	set_ray_distance(ray_params, intersection->distance);
	set_ray_hit_info(ray_params, hit_vertical, intersection->x, \
		intersection->y);
	set_wall_direction(ray_params, angle, hit_vertical);
}


t_ray	cast_ray(t_game *game, float start_x, float start_y, float angle)
{
	t_intersection		horizontal;
	t_intersection		vertical;
	t_ray				ray;
	t_ray_params		ray_params;
	t_intercept_params	inter_params;

	inter_params.start_x = start_x;
	inter_params.start_y = start_y;
	inter_params.angle = angle;
	angle = normalize_angle(angle);
	horizontal = calculate_horizontal_intersection(game, &inter_params);
	vertical = calculate_vertical_intersection(game, start_x, start_y, angle);
	if (!horizontal.is_valid || (vertical.is_valid && vertical.distance < \
			horizontal.distance))
		set_ray_params(&ray_params, &vertical, 1, angle);
	else
		set_ray_params(&ray_params, &horizontal, 0, angle);
	init_ray(&ray, &ray_params);
	return (ray);
}
