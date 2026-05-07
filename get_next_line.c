/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thattal <thattal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:05:32 by thattal           #+#    #+#             */
/*   Updated: 2026/05/06 14:10:00 by thattal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char **output, char *s1, char *s2)
{
	char	*nstr;

	if (!s2)
		return (s1);
	nstr = malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!nstr)
		return (NULL);
	ft_memset(nstr, 0, ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_memmove(nstr, s1, ft_strlen(s1));
	ft_memmove(nstr + ft_strlen(s1), s2, ft_strlen(s2));
	free(s1);
	*output = nstr;
	return (nstr);
}

char	*ft_strchr(char *string, char find)
{
	int	i;

	i = 0;
	while (string && string[i])
	{
		if (string[i] == find)
			return (&string[i]);
		i++;
	}
	return (NULL);
}

int	ft_split_line(char **line, char **keep)
{
	char	*temp;
	int		len;

	if (!*keep || !**keep)
		return (*line = NULL, 0);
	len = 0;
	while ((*keep)[len] && (*keep)[len] != '\n')
		len++;
	len += ((*keep)[len] == '\n');
	*line = malloc(len + 1);
	if (!*line)
		return (0);
	ft_memmove(*line, *keep, len);
	(*line)[len] = '\0';
	temp = NULL;
	if ((*keep)[len])
	{
		temp = malloc(ft_strlen(*keep + len) + 1);
		if (temp)
			ft_memmove(temp, *keep + len, ft_strlen(*keep + len) + 1);
	}
	free(*keep);
	*keep = temp;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*keep = NULL;
	char		*buffer;
	char		*line;
	int			return_val;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (ft_strchr(keep, '\n') == NULL)
	{
		return_val = read(fd, buffer, BUFFER_SIZE);
		if (return_val <= 0)
			break ;
		buffer[return_val] = '\0';
		ft_strjoin(&keep, keep, buffer);
	}
	free(buffer);
	ft_split_line(&line, &keep);
	return (line);
}
