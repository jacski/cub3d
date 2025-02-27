/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:23:05 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/16 15:23:07 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] != '\0' && str1[i] == str2[i] && i < n - 1)
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

int	validate_arguments(int argc, char *filename)
{
	int	len;

	if (argc != 2)
	{
		write(2, "Usage: ./cub3D <map_file>\n", 26);
		return (0);
	}
	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		write(2, "Error: Map file must have a .cub extension\n", 43);
		return (0);
	}
	return (1);
}

int	start_game(t_game *game, char *map_file)
{
	init_game(game);
	parse_map_file(map_file, game);
	setup_game(game);
	initialize_textures(game);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->win)
	{
		write(2, "Failed to create MLX window\n", 28);
		cleanup_game(game);
		return (0);
	}
	return (1);
}
