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

char	*ft_strndup(const char *src, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static void	process_line(char *line_start, char *lines[MAX_LINE_LENGTH], \
	int *line_count)
{
	char	*line_end;

	while (*line_start)
	{
		line_end = line_start;
		while (*line_end && *line_end != '\n')
			line_end++;
		lines[*line_count] = ft_strndup(line_start, line_end - line_start);
		(*line_count)++;
		if (*line_end == '\n')
			line_end++;
		line_start = line_end;
	}
}

void	read_map_lines(int fd, char *lines[1024], int *line_count)
{
	ssize_t	bytes_read;
	char	buffer[MAX_LINE_LENGTH];

	bytes_read = read(fd, buffer, MAX_LINE_LENGTH - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		process_line(buffer, lines, line_count);
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
