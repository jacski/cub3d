/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:12:48 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 18:12:55 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_exit(t_game *game)
{
	cleanup_game(game);
	exit(EXIT_SUCCESS);
}

int	handle_keypress(int key, t_game *game)
{
	handle_input(key, game);
	return (0);
}


void	parse_map_file(const char *file_path, t_game *game)
{
	char	*lines[1024];
	int		line_count;
	int		i;

	line_count = 0;
	read_map_file(file_path, lines, &line_count);
	parse_map_config(lines, line_count, game);
	extract_and_validate_map(lines, line_count, game);
	locate_player(game->config.map.grid, game->config.map.height, \
		game->config.map.width, game);
	i = 0;
	while (i < line_count)
	{
		free(lines[i]);
		i++;
	}
}

int	game_loop(t_game *game)
{
	int	x;

	x = 0;
	clear_screen(game, 0x000000);
	while (x < game->screen_width)
	{
		render_column(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!validate_arguments(argc, argv[1]) || !start_game(&game, argv[1]))
		return (EXIT_FAILURE);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 1L << 17, handle_exit, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (EXIT_SUCCESS);
}
