*This activity has been created as part of the 42 curriculum by thattal.*

# Get Next Line

![Language](https://img.shields.io/badge/language-C-blue.svg)
![Norm](https://img.shields.io/badge/norminette-passing-brightgreen.svg)
![42](https://img.shields.io/badge/42-curriculum-black.svg)

## Description

`get_next_line` est une fonction écrite en C qui lit un fichier (ou un flux pointé par un descripteur de fichier) **ligne par ligne**, à chaque appel.

L'objectif du projet est double :

- Apprendre à manipuler les **descripteurs de fichiers** et l'appel système `read`.
- Découvrir et maîtriser le concept de **variable statique** en C, qui permet de conserver un état entre plusieurs appels d'une même fonction sans recourir à des variables globales.

Prototype de la fonction :

```c
char *get_next_line(int fd);
```

La fonction retourne la prochaine ligne lue sur le descripteur `fd` (incluant le `\n` final, sauf en fin de fichier), ou `NULL` en cas d'erreur ou lorsqu'il n'y a plus rien à lire.

## Instructions

### Arborescence du projet

```
.
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
└── README.md
```

### Compilation

Le projet se compile avec `cc` et les flags `-Wall -Wextra -Werror`. La taille du buffer utilisée par `read` est définie à la compilation via la macro `BUFFER_SIZE` (une valeur par défaut est définie dans `get_next_line.h` afin que le projet compile aussi sans le flag `-D`).

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

Le projet doit pouvoir compiler **avec ou sans** le flag `-D BUFFER_SIZE`.

### Exemple d'utilisation

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

La fonction fonctionne aussi sur l'entrée standard (`fd = 0`) et sur tout autre descripteur valide (pipe, socket, etc.).

## Algorithme

Le cœur de `get_next_line` repose sur une **variable statique** qui conserve, entre deux appels, ce qui a déjà été lu sur le descripteur de fichier mais pas encore renvoyé à l'appelant. On peut résumer le fonctionnement en trois étapes.

### 1. Remplissage du buffer statique

Tant que la chaîne statique ne contient **pas de `\n`** et que `read` retourne une valeur strictement positive :

- Allouer un buffer temporaire de taille `BUFFER_SIZE + 1`.
- Lire `BUFFER_SIZE` octets sur `fd`.
- Concaténer ce buffer à la chaîne statique (puis libérer l'ancien pointeur pour éviter la fuite mémoire).

On s'arrête dès qu'un `\n` est trouvé : l'idée est de lire **le moins possible** à chaque appel, et non d'avaler tout le fichier en mémoire.

### 2. Extraction de la ligne courante

On parcourt la chaîne statique jusqu'au premier `\n` (ou jusqu'à `\0` si la fin de fichier a été atteinte). On alloue alors une nouvelle chaîne contenant cette portion, **`\n` inclus**, qui sera renvoyée à l'utilisateur.

### 3. Mise à jour du buffer statique

Le contenu restant après le `\n` est conservé dans la variable statique pour le prochain appel. Si plus rien ne reste, la variable est libérée et remise à `NULL`.

### Pourquoi ce choix ?

| Critère | Justification |
|---------|---------------|
| **Variable statique** | Permet de mémoriser le surplus de lecture sans variable globale (interdites par le sujet) ni `lseek` (interdit aussi). |
| **Lecture par blocs de `BUFFER_SIZE`** | Compromis paramétrable : `BUFFER_SIZE=1` fonctionne mais est lent ; `BUFFER_SIZE=10000000` fonctionne aussi mais consomme beaucoup de mémoire d'un coup. |
| **Concaténation incrémentale** | Évite de devoir connaître à l'avance la longueur d'une ligne, qui peut être arbitrairement longue. |
| **Libération systématique des allocations intermédiaires** | Garantit l'absence de fuites mémoire, exigence non-négociable du sujet. |

### Cas particuliers gérés

- Fichier vide → retourne `NULL` dès le premier appel.
- Dernière ligne sans `\n` final → la ligne est retournée sans `\n`, l'appel suivant retourne `NULL`.
- `fd` invalide ou `BUFFER_SIZE <= 0` → retourne `NULL`.
- `read` retourne `-1` → libération de la mémoire et retour `NULL`.

## Resources

Documentation et références utilisées :

- `man 2 read`, `man 3 malloc`, `man 3 free` — pages de manuel des fonctions autorisées.
- 42 Norm — règles de style obligatoires pour les projets en C.
- Brian W. Kernighan & Dennis M. Ritchie, *The C Programming Language* — pour les bases du C et la notion de variable statique.
- Cours et discussions avec mes pairs au cluster sur la gestion mémoire et les descripteurs de fichiers.

### Utilisation de l'IA

Conformément aux consignes du sujet, l'IA n'a **pas** été utilisée pour produire la solution.

Elle a été utilisée uniquement comme outil d'appoint, en dehors de la production de code, pour :

- Reformuler certaines pages de manuel pour mieux comprendre `read` et le comportement des descripteurs.
- Discuter de l'intérêt et des limites des variables statiques en C, sans demander d'implémentation.
- Relire et structurer ce README.

Aucune partie du code de `get_next_line.c` ou `get_next_line_utils.c` n'a été générée par une IA : l'algorithme, la structure du code et la gestion mémoire ont été conçus et écrits à la main, dans l'esprit de la pédagogie 42.
