/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:23:14 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 19:23:16 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_color_component(const char *str, int *value)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (!is_digit(str[i]))
		return (0);
	while (is_digit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		if (num > 255)
			return (0);
		i++;
	}
	*value = num;
	return (i);
}

void	handle_color_line(const char *line, int *color, \
		const char *color_name)
{
	if (color[0] != -1)
	{
		write_error_with_string("Multiple occurrences of color (%s)", \
			color_name);
		exit(EXIT_FAILURE);
	}
	if (!parse_color(line + 2, color))
	{
		write_error_with_string("Invalid color format for %s", color_name);
		exit(EXIT_FAILURE);
	}
}

int	check_missing_comma(const char *line, int i)
{
	if (line[i] != ',')
	{
		write_error("Error: Invalid color format, missing ',' at position ");
		write_int(i);
		write_error("\n");
		return (0);
	}
	return (1);
}

int	parse_color_component_and_validate(const char *line, int *i, int *color, \
		int j)
{
	int	len;

	len = parse_color_component(line + *i, &color[j]);
	if (len == 0)
	{
		write_error("Error: Invalid color value at component ");
		write_int(j + 1);
		write_error("\n");
		return (0);
	}
	if (color[j] < 0 || color[j] > 255)
	{
		write_error("Error: Invalid color value at component ");
		write_int(j + 1);
		write_error(" (must be 0-255)\n");
		return (0);
	}
	*i += len;
	return (1);
}

int	parse_color(const char *line, int *color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		if (!parse_color_component_and_validate(line, &i, color, j))
			return (0);
		if (j < 2)
		{
			if (!check_missing_comma(line, i))
				return (0);
			i++;
		}
		j++;
	}
	if (line[i] != '\0')
	{
		write_error("Error: Extra characters found after color definition\n");
		return (0);
	}
	return (1);
}
