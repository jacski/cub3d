/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:14:49 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 18:15:39 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	read_map_lines(int fd, char *lines[1024], int *line_count)
{
	ssize_t	bytes_read;
	char	buffer[MAX_LINE_LENGTH];
	char	*line;

	bytes_read = read(fd, buffer, MAX_LINE_LENGTH - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		line = strtok(buffer, "\n");
		while (line)
		{
			lines[*line_count] = ft_strdup(line);
			(*line_count)++;
			line = strtok(NULL, "\n");
		}
		bytes_read = read(fd, buffer, MAX_LINE_LENGTH - 1);
	}
	if (bytes_read < 0)
	{
		print_error("Failed to read map file");
		exit(EXIT_FAILURE);
	}
}

void	read_map_file(const char *file_path, char *lines[1024], int *line_count)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		print_error("Failed to open map file");
		exit(EXIT_FAILURE);
	}
	read_map_lines(fd, lines, line_count);
	close(fd);
}

void	parse_map_config(char *lines[1024], int line_count, t_game *game)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		if (is_configuration_line(lines[i]))
			parse_configuration_line(lines[i], &game->config);
		i++;
	}
}

void	extract_and_validate_map(char *lines[1024], int line_count, \
		t_game *game)
{
	int		rows;
	int		cols;
	char	**map_grid;

	map_grid = extract_map(lines, line_count, &rows, &cols);
	if (!validate_map(map_grid, rows, cols))
	{
		print_error("Invalid map structure");
		exit(EXIT_FAILURE);
	}
	game->config.map.grid = map_grid;
	game->config.map.width = cols;
	game->config.map.height = rows;
}

void	set_player_angle(t_game *game, char tile)
{
	if (tile == 'N')
		game->player.angle = (float)M_PI / 2;
	else if (tile == 'S')
		game->player.angle = (float)3 * M_PI / 2;
	else if (tile == 'E')
		game->player.angle = (float)0;
	else if (tile == 'W')
		game->player.angle = (float)M_PI;
}
