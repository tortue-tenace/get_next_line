#include <stdlib.h>
#include "gnl.h"

void	ft_memset(char *zone, char sym, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		zone[i] = sym;
		i++;
	}
}

char	ft_strchr(char *string, char find)
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

int	ft_strlen(char *string)
{
	int	i;

	i = 0;
	while (string && string[i])
		i++;
	return (i);
}

void	ft_memmove(char *destination, char *source, int total)
{
	int	i;
	
	i = 0;
	while (i < total)
	{
		destination[i] = source[i];
		i++;
	}
}

int	ft_join(char **output, char *s1, char *s2)
//s1 partie gauche, s2 partie droite
//output en double pointeur pour pouvoir modifier dans gnl
//l'adresse de ce pointeur
{
	int	len_s1;
	int	new_len;
	char	*exit_str;

	len_s1 = ft_strlen(s1);
	new_len =  len_s1 + ft_strlen(s2) + 1;
	exit_str = (char *)malloc(sizeof(char) * new_len);
	if (exit_str == NULL)
		return (1);
	ft_memset(exit_str, 0, new_len);
	ft_memmove(exit_str, s1, len_s1);
	ft_memmove(exit_str + len_s1, s2, ft_strlen(s2));
	free(s1);	
	*output = exit_str;
	return (0);
}

int	ft_split_ret(char **final_line, char *current, char **save)
{
	int	len_left;
	int	len_right;
	char	*return_char;

	return_char = ft_strchr(current, '\n');
	if (return_char == NULL)
	{
		*final_line = current;
		return (0);
	}
	len_left = current - return_char + 2;
	*final_line = malloc(sizeof(char) * len_left);
	if (*final_line == NULL)
		return (1);
	ft_memset(*final_line, 0, len_left);
	ft_memmove(*final_line, current, len_left - 1);
	len_right = ft_strlen(return_char + 1) + 1;
	if (len_right == 1)
	{
		*save = NULL;
		return (0);
	}	
	*save = malloc(sizeof(char) * len_right);
	if (*save == NULL)
	{
		free(*final_line);
		return (1);
	}
	ft_memset(*save, 0, len_right);
	ft_memmove(*save, return_char = 1, len_right - 1);
	return (0);
}

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*exit_str;
	int		return_val;
	static char	*keep = NULL;

	//conditions de base
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, exit_str, 0) < 0)
		return (NULL);	
	ft_memset(buffer, 0, BUFFER_SIZE + 1);
	exit_str = keep;
	while (ft_strchr(exit_str, '\n') == NULL)
		if (return_val == 0)
		       break;	
		if (return_val == -1)
			//gerer le cas de merde
		if (ft_join(&exit_str, exit_str, buffer))
			//gerer cas de merde	
	}
	if (ft_split_ret(&exit_str, exit_str, &keep));
		//gerer cas de merde
	return (exit_str);	
	//joindre les bouts de buffer jusqu'a ce que le buffer contienne
	//un retour a la ligne ou que read envoie 0 
	
	//une fois la boucle terminee split le resultat sur le premier retour a la 
	//ligne et renvoyer le resultat;
	//garder le reste du buffer dans keep
}
