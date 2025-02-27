/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:29:17 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 18:29:20 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_texture(t_game *game, const char *path, int texture_index)
{
	void	*img;
	int		info[3];

	img = mlx_xpm_file_to_image(game->mlx, (char *)path, &info[0], &info[1]);
	if (!img)
	{
		write(2, "Error: Failed to load texture\n", 30);
		cleanup_game(game);
		exit(EXIT_FAILURE);
	}
	game->texture_width = info[0];
	game->texture_height = info[1];
	game->textures[texture_index] = (uint32_t *)mlx_get_data_addr(img, \
		&info[2], &info[1], &info[0]);
}

void	initialize_textures(t_game *game)
{
	load_texture(game, game->config.north_texture, 0);
	load_texture(game, game->config.south_texture, 1);
	load_texture(game, game->config.west_texture, 2);
	load_texture(game, game->config.east_texture, 3);
}

void	handle_texture_line(const char *line, char **texture, \
		const char *texture_name)
{
	char	*texture_path;

	if (*texture != NULL)
	{
		write_error_with_string("Multiple occurrences of texture (%s)", \
			texture_name);
		exit(EXIT_FAILURE);
	}
	texture_path = parse_texture_path(line + 3);
	if (!file_exists(texture_path))
	{
		write_error_with_string("Error: Texture file does not exist: ", \
			texture_path);
		free(texture_path);
		exit(EXIT_FAILURE);
	}
	*texture = texture_path;
}

void	validate_game_config(t_config *config)
{
	int	i;

	if (!config->north_texture || !config->south_texture || \
		!config->west_texture || !config->east_texture)
	{
		print_error("Error: Missing texture paths in configuration");
		exit(EXIT_FAILURE);
	}
	if (!config->map.grid)
	{
		print_error("Error: Map data is not initialized.");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < 3)
	{
		if (config->floor_color[i] < 0 || config->floor_color[i] > 255 || \
		config->ceiling_color[i] < 0 || config->ceiling_color[i] > 255)
		{
			print_error("Error: Invalid floor or ceiling colors");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	setup_game(t_game *game)
{
	t_config	*config;
	int			bpp;
	int			size_line;
	int			endian;

	config = &game->config;
	game->img = mlx_new_image(game->mlx, game->screen_width, \
		game->screen_height);
	if (!game->img)
	{
		print_error("Failed to create image");
		exit(EXIT_FAILURE);
	}
	game->img_data = mlx_get_data_addr(game->img, &bpp, &size_line, &endian);
	if (!game->img_data)
	{
		print_error("Failed to get image data address");
		exit(EXIT_FAILURE);
	}
	validate_game_config(config);
}
