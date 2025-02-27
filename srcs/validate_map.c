/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:09:01 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 19:09:04 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_map_characters(char temp_map[MAX_ROWS][MAX_COLS], char *map[], \
		int rows, int cols)
{
	int	i;
	int	j;
	int	start_index;
	int	end_index;

	i = 0;
	while (i < rows)
	{
		start_index = find_first_non_space_index(map[i]);
		end_index = find_last_non_space_index(map[i]);
		j = 0;
		while (j < cols)
		{
			if (j >= start_index && j <= end_index && \
				temp_map[i][j] != '1' && temp_map[i][j] != '0' && \
				temp_map[i][j] != 'W' && temp_map[i][j] != 'E' && \
				temp_map[i][j] != 'S' && temp_map[i][j] != 'N' && \
				temp_map[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_map_boundary_invalid(char temp_map[MAX_ROWS][MAX_COLS], \
		t_coordinates *c, int rows, t_coordinates *se)
{
	return (c->x == 0 || c->x == rows - 1 || c->y == se->x || c->y == se->y || \
		temp_map[c->x][c->y - 1] == ' ' || temp_map[c->x][c->y + 1] == ' ' || \
		!temp_map[c->x + 1][c->y] || !temp_map[c->x - 1][c->y] || \
		temp_map[c->x - 1][c->y] == ' ' || temp_map[c->x + 1][c->y] == ' ');
}

int	check_map_cell(t_coordinates *c, t_coordinates *se, \
		char temp_map[MAX_ROWS][MAX_COLS], int *has_start)
{
	if (temp_map[c->x][c->y] == '0' || temp_map[c->x][c->y] == 'W' || \
		temp_map[c->x][c->y] == 'E' || temp_map[c->x][c->y] == 'N' || \
		temp_map[c->x][c->y] == 'S')
	{
		if (is_map_boundary_invalid(temp_map, c, se->x, se))
			return (0);
	}
	if (temp_map[c->x][c->y] == 'S' || temp_map[c->x][c->y] == 'E' || \
		temp_map[c->x][c->y] == 'W' || temp_map[c->x][c->y] == 'N')
		(*has_start)++;
	return (1);
}

int	validate_map_boundaries(char temp_map[MAX_ROWS][MAX_COLS], char *map[], \
		t_map_size *size, int *has_start)
{
	t_coordinates	c;
	t_coordinates	se;

	c.x = 0;
	while (c.x < size->rows)
	{
		se.x = find_first_non_space_index(map[c.x]);
		se.y = find_last_non_space_index(map[c.x]);
		c.y = 0;
		while (c.y < size->cols)
		{
			if (!check_map_cell(&c, &se, temp_map, has_start))
				return (0);
			c.y++;
		}
		c.x++;
	}
	return (1);
}

int	validate_map(char *map[], int rows, int cols)
{
	t_map_size	size;
	char		temp_map[MAX_ROWS][MAX_COLS];
	int			has_start;

	has_start = 0;
	size.rows = rows;
	size.cols = cols;
	copy_map_to_temp(temp_map, map, rows, cols);
	if (!validate_map_characters(temp_map, map, rows, cols))
		return (0);
	if (!validate_map_boundaries(temp_map, map, &size, &has_start))
		return (0);
	return (has_start == 1);
}
