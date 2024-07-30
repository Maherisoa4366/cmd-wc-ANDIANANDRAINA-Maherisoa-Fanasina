#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Prototypes des fonctions
void count_lines(FILE *file, int *line_count);
void count_words(FILE *file, int *word_count);
void count_chars(FILE *file, int *char_count);

int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [-l|-w|-c] <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Ouverture du fichier
    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Variables pour stocker les résultats
    int line_count = 0, word_count = 0, char_count = 0;

    // Exécution des fonctions selon l'option choisie
    if (strcmp(argv[1], "-l") == 0) {
        count_lines(file, &line_count);
        printf("Nombre de lignes: %d\n", line_count);
    } else if (strcmp(argv[1], "-w") == 0) {
        count_words(file, &word_count);
        printf("Nombre de mots: %d\n", word_count);
    } else if (strcmp(argv[1], "-c") == 0) {
        count_chars(file, &char_count);
        printf("Nombre de caractères: %d\n", char_count);
    } else {
        fprintf(stderr, "Option invalide: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Fermeture du fichier
    fclose(file);
    return 0;
}

// Fonction pour compter les lignes
void count_lines(FILE *file, int *line_count) {
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            (*line_count)++;
        }
    }
    // Remettre le pointeur au début du fichier
    rewind(file);
}

// Fonction pour compter les mots
void count_words(FILE *file, int *word_count) {
    char ch;
    int in_word = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            (*word_count)++;
        }
    }
    // Remettre le pointeur au début du fichier
    rewind(file);
}

// Fonction pour compter les caractères
void count_chars(FILE *file, int *char_count) {
    while (fgetc(file) != EOF) {
        (*char_count)++;
    }
    // Remettre le pointeur au début du fichier
    rewind(file);
}