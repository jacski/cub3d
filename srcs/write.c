/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:37:04 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 19:37:07 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	write_number_to_buffer(int num, char *buffer, int *index)
{
	int	temp;

	temp = num;
	if (num == 0)
		buffer[(*index)++] = '0';
	else
	{
		while (temp > 0)
		{
			buffer[(*index)++] = '0' + (temp % 10);
			temp /= 10;
		}
	}
}

void	write_int(int num)
{
	char	buffer[12];
	int		index;

	index = 0;
	write_number_to_buffer(num, buffer, &index);
	reverse_buffer(buffer, index);
	buffer[index] = '\0';
	write(STDERR_FILENO, buffer, index);
}

void	print_error(const char *message)
{
	write(STDERR_FILENO, message, strlen(message));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	write_error(const char *message)
{
	write(STDERR_FILENO, message, strlen(message));
}

void	write_error_with_string(const char *message, const char *detail)
{
	write(STDERR_FILENO, message, strlen(message));
	write(STDERR_FILENO, detail, strlen(detail));
	write(STDERR_FILENO, "\n", 1);
}
