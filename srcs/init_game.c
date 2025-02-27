/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:46:17 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 18:46:21 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*parse_texture_path(const char *line)
{
	char	*trimmed;

	trimmed = trim_spaces(line);
	if (!trimmed || strlen(trimmed) == 0)
		print_error("Empty texture path");
	return (trimmed);
}

void	init_mlx_and_dimensions(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		perror("Error initializing MLX");
		exit(EXIT_FAILURE);
	}
	game->screen_width = WIN_WIDTH;
	game->screen_height = WIN_HEIGHT;
	game->texture_width = TEXTURE_WIDTH;
	game->texture_height = TEXTURE_HEIGHT;
}

void	init_player(t_game *game)
{
	game->player.pos_x = 2.0f;
	game->player.pos_y = 2.0f;
	game->player.dir_x = -1.0f;
	game->player.dir_y = 0.0f;
	game->player.plane_x = 0.0f;
	game->player.plane_y = 0.66f;
	game->player.angle = M_PI / 2;
	game->player.speed = 0.5f;
}

void	init_config(t_game *game)
{
	game->config.north_texture = NULL;
	game->config.south_texture = NULL;
	game->config.west_texture = NULL;
	game->config.east_texture = NULL;
	game->config.map.grid = NULL;
	game->config.map.width = 0;
	game->config.map.height = 0;
	game->config.floor_color[0] = -1;
	game->config.floor_color[1] = -1;
	game->config.floor_color[2] = -1;
	game->config.ceiling_color[0] = -1;
	game->config.ceiling_color[1] = -1;
	game->config.ceiling_color[2] = -1;
}

void	init_game(t_game *game)
{
	init_mlx_and_dimensions(game);
	init_player(game);
	init_config(game);
}
