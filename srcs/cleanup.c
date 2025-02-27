/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:39:38 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 19:39:41 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i])
		{
			free(game->textures[i]);
			game->textures[i] = NULL;
		}
		i++;
	}
}

void	free_map_grid(t_config *config)
{
	int	i;

	if (config->map.grid)
	{
		i = 0;
		while (i < config->map.height)
		{
			free(config->map.grid[i]);
			i++;
		}
		free(config->map.grid);
		config->map.grid = NULL;
	}
}

void	free_textures_c(t_config *config)
{
	if (config->north_texture)
	{
		free(config->north_texture);
		config->north_texture = NULL;
	}
	if (config->south_texture)
	{
		free(config->south_texture);
		config->south_texture = NULL;
	}
	if (config->west_texture)
	{
		free(config->west_texture);
		config->west_texture = NULL;
	}
	if (config->east_texture)
	{
		free(config->east_texture);
		config->east_texture = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	free_map_grid(&game->config);
	free_textures_c(&game->config);
	if (game->img)
	{
		mlx_destroy_image(game->mlx, game->img);
		game->img = NULL;
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}
