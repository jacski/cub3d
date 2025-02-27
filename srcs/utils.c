/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:35:26 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 19:35:29 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strdup(const char *str)
{
	size_t	length;
	size_t	i;
	char	*copy;

	if (str == NULL)
		return (NULL);
	length = 0;
	while (str[length])
		length++;
	copy = (char *)malloc(length + 1);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

size_t	ft_strspn(char *s, char *accept)
{
	char	*p;
	char	*a;
	size_t	count;

	count = 0;
	p = s;
	while (*p != '\0')
	{
		a = accept;
		while (*a != '\0')
		{
			if (*p == *a)
				break ;
			a++;
		}
		if (*a == '\0')
			return (count);
		count++;
		p++;
	}
	return (count);
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

char	*trim_spaces(const char *line)
{
	char	*trimmed;
	size_t	len;

	while (isspace(*line))
		line++;
	trimmed = ft_strdup(line);
	if (!trimmed)
		print_error("Memory allocation failed during trimming");
	len = strlen(trimmed);
	while (len > 0 && isspace(trimmed[len - 1]))
	{
		trimmed[len - 1] = '\0';
		len--;
	}
	return (trimmed);
}

void	reverse_buffer(char *buffer, int index)
{
	int		i;
	char	swap;

	i = 0;
	while (i < index / 2)
	{
		swap = buffer[i];
		buffer[i] = buffer[index - i - 1];
		buffer[index - i - 1] = swap;
		i++;
	}
}
