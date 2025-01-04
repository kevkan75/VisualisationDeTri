#include <stdio.h>
#include <stdlib.h>

// Fonction pour effectuer le tri Gnome
void triGnome(int tableau[], int taille, FILE *fichier) {
    int index = 0;

    while (index < taille) {
        if (index == 0 || tableau[index] >= tableau[index - 1]) {
            index++;
        } else {
            // Échanger les éléments si nécessaire
            int temp = tableau[index];
            tableau[index] = tableau[index - 1];
            tableau[index - 1] = temp;

            // Enregistrer l'état actuel dans le fichier
            fprintf(fichier, "Étape %d : ", index);
            for (int j = 0; j < taille; j++) {
                fprintf(fichier, "%d ", tableau[j]);
            }
            fprintf(fichier, "\n");

            // Afficher l'état actuel à la console
            printf("Étape %d : ", index);
            for (int k = 0; k < taille; k++) {
                printf("%d ", tableau[k]);
            }
            printf("\n");

            index--;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Erreur : Veuillez fournir les valeurs à trier comme arguments.\n");
        return EXIT_FAILURE;
    }

    // Ouvrir le fichier de sortie
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier de sortie.\n");
        return EXIT_FAILURE;
    }

    // Lecture des arguments et initialisation du tableau
    int n = argc - 1;
    int *values = malloc(n * sizeof(int));
    if (values == NULL) {
        fprintf(stderr, "Erreur : Allocation mémoire échouée.\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        values[i] = atoi(argv[i + 1]);
    }

    // Afficher les valeurs initiales
    printf("Valeurs initiales : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    // Enregistrer les valeurs initiales dans le fichier
    fprintf(file, "Valeurs initiales : ");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", values[i]);
    }
    fprintf(file, "\n");

    // Appeler le tri Gnome
    triGnome(values, n, file);

    // Libérer la mémoire et fermer le fichier
    free(values);
    fclose(file);

    return EXIT_SUCCESS;
}
