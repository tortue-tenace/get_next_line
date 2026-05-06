#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

// Déclaration de la fonction get_next_line (au cas où elle n'est pas dans le header exact avec ce prototype)
char *get_next_line(int fd);

int main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		count;

	count = 1;
	// S'il y a un argument, on lit ce fichier, sinon on lit test.txt par défaut
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = open("test.txt", O_RDONLY);

	if (fd < 0)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (1);
	}

	printf("=== DEBUT DE LA LECTURE ===\n\n");

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Ligne %d : %s", count, line);
		free(line);
		count++;
	}

	printf("\n=== FIN DE LA LECTURE ===\n");
	close(fd);
	return (0);
}
