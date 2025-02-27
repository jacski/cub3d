/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:11:00 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 19:11:05 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	copy_map_to_temp(char temp_map[MAX_ROWS][MAX_COLS], char *map[], \
		int rows, int cols)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		strncpy(temp_map[i], map[i], cols);
		i++;
	}
}

int	find_map_start(char **lines, int line_count)
{
	int		i;
	char	*non_space;

	i = 0;
	while (i < line_count)
	{
		non_space = lines[i] + ft_strspn(lines[i], " \t");
		if (*non_space == '1' || *non_space == '0')
			return (i);
		i++;
	}
	print_error("No valid map found in the file");
	return (-1);
}

void	calculate_map_dimensions(char **lines, int map_start, int line_count, \
		t_map_size *size)
{
	int	i;
	int	line_length;

	size->rows = 0;
	size->cols = 0;
	i = map_start;
	while (i < line_count)
	{
		line_length = strlen(lines[i]);
		if (line_length > 0)
		{
			if (size->cols < line_length)
				size->cols = line_length;
			(size->rows)++;
		}
		i++;
	}
}

char	**extract_map(char **lines, int line_count, int *rows, int *cols)
{
	t_map_size	size;	
	int			map_start;
	int			i;
	char		**map;

	map_start = find_map_start(lines, line_count);
	calculate_map_dimensions(lines, map_start, line_count, &size);
	*rows = size.rows;
	*cols = size.cols;
	map = malloc((size.rows) * sizeof(char *));
	if (!map)
		print_error("Memory allocation failed for map");
	i = 0;
	while (i < size.rows)
	{
		map[i] = ft_strdup(lines[map_start + i]);
		if (!map[i])
			print_error("Memory allocation failed for map line");
		i++;
	}
	return (map);
}
