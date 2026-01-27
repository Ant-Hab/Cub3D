/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achowdhu <achowdhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:36:38 by achowdhu          #+#    #+#             */
/*   Updated: 2025/08/09 18:45:11 by achowdhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	read_to_buffer(char *buffer, int fd)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (bytes_read);
	buffer[bytes_read] = '\0';
	return (bytes_read);
}

static char	*extract_line(char *line, char *buffer)
{
	char	*temp;
	char	*joined;
	char	*nl;

	nl = ft_strchr(buffer, '\n');
	if (nl)
	{
		temp = ft_substr(buffer, 0, nl - buffer + 1);
		if (!temp)
			return (free(line), NULL);
		ft_memmove(buffer, nl + 1, ft_strlen(nl + 1) + 1);
	}
	else
	{
		temp = ft_strdup(buffer);
		if (!temp)
			return (NULL);
		*buffer = 0;
	}
	if (!line)
		return (temp);
	joined = ft_strjoin(line, temp);
	return (free(line), free(temp), joined);
}

static char	*process_read_loop(int fd, char *buffer, char *line)
{
	char	*temp;

	while (read_to_buffer(buffer, fd) >= 0)
	{
		if (!*buffer)
			return (line);
		if (ft_strchr(buffer, '\n'))
			return (extract_line(line, buffer));
		temp = ft_strjoin(line, buffer);
		if (!temp)
			break ;
		free(line);
		line = temp;
		*buffer = 0;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (*buffer)
	{
		line = extract_line(NULL, buffer);
		if (!line || ft_strchr(line, '\n'))
			return (line);
	}
	temp = process_read_loop(fd, buffer, line);
	if (temp)
		return (temp);
	return (free(line), NULL);
}
