/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:17:28 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/01 09:29:33 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_errors(int fd, char **line, t_gnl *string)
{
	ft_memset(string, 0, sizeof(*string));
	if ((fd < 0) || (fd > RLIMIT_NOFILE) || (BUFFER_SIZE < 1) || !(line))
		return (1);
	return (0);
}

static int	add_to_line(t_gnl *string, char **line, char **excess, int new_line)
{
	if (new_line)
		*string->break_line_ptr = '\0';
	string->read[string->read_return] = '\0';
	string->temp = ft_strjoin(*line, string->read);
	if (string->temp == NULL)
		return (ERROR);
	free(*line);
	*line = string->temp;
	if (new_line)
	{
		string->temp = ft_strdup(string->break_line_ptr + 1);
		if (string->temp == NULL)
			return (ERROR);
		free(*excess);
		*excess = string->temp;
	}
	return (READ_LINE);
}

static int	add_excess(char **line, t_gnl *string, char **excess, int new_line)
{
	if (new_line)
		*string->break_line_ptr = '\0';
	string->temp = ft_strjoin(*line, *excess);
	if (string->temp == NULL)
		return (ERROR);
	free(*line);
	*line = string->temp;
	if (new_line)
	{
		string->temp = ft_strdup(string->break_line_ptr + 1);
		if (string->temp == NULL)
			return (ERROR);
	}
	free(*excess);
	if (new_line)
		*excess = string->temp;
	else
		*excess = NULL;
	return (READ_LINE);
}

int			get_next_line(int fd, char **line)
{
	static char		*excess;
	t_gnl			string;

	if ((check_errors(fd, line, &string)) || (*line = ft_strdup("")) == NULL)
		return (-1);
	if (excess != NULL)
	{
		if ((string.break_line_ptr = ft_strchr(excess, '\n')))
			return (add_excess(line, &string, &excess, NEW_LINE));
		if ((add_excess(line, &string, &excess, NO_NEW_LINE)) == ERROR)
			return (ERROR);
	}
	while (((string.read_return = read(fd, string.read, BUFFER_SIZE)) > 0)
			&& !(string.break_line_ptr = ft_strchr(string.read, '\n')))
		if (add_to_line(&string, line, &excess, NO_NEW_LINE) == ERROR)
			return (ERROR);
	if (string.read_return < 1)
	{
		free(excess);
		return (string.read_return);
	}
	return (add_to_line(&string, line, &excess, NEW_LINE));
}
