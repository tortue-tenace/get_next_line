/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thattal <thattal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:36:37 by thattal           #+#    #+#             */
/*   Updated: 2026/05/04 15:50:24 by thattal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

size_t	ft_strlen(char	*s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char **output, char *s1, char *s2)
{
	char	*nstr;
	int		i;

	i = 0;
	if (!s2)
		return (s1);
	nstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	ft_memset(nstr, 0, ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_memmove(nstr, s1, ft_strlen(s1));
	ft_memmove(nstr + ft_strlen(s1), s2, ft_strlen(s2));
	free(s1);
	*output = nstr;
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
	
}

char	*get_next_line(int fd)
{
	static char	*keep = NULL;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	int			return_val;

	while (ft_strchr(keep, '\n') == NULL)
	{
		return_val = read(fd, buffer, BUFFER_SIZE);
		if (return_val <= 0)
			break;
		buffer[return_val] = '\0';
		ft_strjoin(&keep, keep, buffer);
    }
	ft_split_line(&line, &keep); 
	return (line);
}
