/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thattal <thattal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:47:56 by thattal           #+#    #+#             */
/*   Updated: 2026/04/30 16:48:39 by thattal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(int fd)
{
	char	*line;
	static int	r_bytes;

	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	r_bytes = read(fd, line, BUFFER_SIZE);
	while (r_bytes)
	{
		if ()
	}
}
