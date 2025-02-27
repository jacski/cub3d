/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:29:45 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 19:29:49 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	file_exists(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd >= 0)
	{
		close(fd);
		return (1);
	}
	return (0);
}

int	is_configuration_line(const char *line)
{
	return ((strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 || \
		strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0 || \
		strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0));
}

int	find_first_non_space_index(const char *row)
{
	int	index;

	index = 0;
	while (row[index] == ' ' && row[index] != '\0')
		index++;
	return (index);
}

int	find_last_non_space_index(const char *row)
{
	int	index;

	index = strlen(row) - 1;
	while (index >= 0 && row[index] == ' ')
		index--;
	return (index);
}

void	parse_configuration_line(const char *line, t_config *config)
{
	if (strncmp(line, "NO ", 3) == 0)
		handle_texture_line(line, &config->north_texture, "NO");
	else if (strncmp(line, "SO ", 3) == 0)
		handle_texture_line(line, &config->south_texture, "SO");
	else if (strncmp(line, "WE ", 3) == 0)
		handle_texture_line(line, &config->west_texture, "WE");
	else if (strncmp(line, "EA ", 3) == 0)
		handle_texture_line(line, &config->east_texture, "EA");
	else if (strncmp(line, "F ", 2) == 0)
		handle_color_line(line, config->floor_color, "F");
	else if (strncmp(line, "C ", 2) == 0)
		handle_color_line(line, config->ceiling_color, "C");
	else
	{
		print_error("Unknown configuration element");
		exit(EXIT_FAILURE);
	}
}
