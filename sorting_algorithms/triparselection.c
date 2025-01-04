#include <stdio.h>
#include <stdlib.h>

// Fonction pour effectuer le tri par sélection
void triSelection(int tableau[], int taille, FILE *fichier) {
    for (int i = 0; i < taille - 1; i++) {
        int minIdx = i;

        // Trouver l'indice du plus petit élément à partir de i
        for (int j = i + 1; j < taille; j++) {
            if (tableau[j] < tableau[minIdx]) {
                minIdx = j;
            }
        }

        // Échanger les éléments si minIdx est différent de i
        if (minIdx != i) {
            int temp = tableau[i];
            tableau[i] = tableau[minIdx];
            tableau[minIdx] = temp;

            // Enregistrer l'état du tableau dans le fichier
            fprintf(fichier, "Étape %d : ", i + 1);
            for (int k = 0; k < taille; k++) {
                fprintf(fichier, "%d ", tableau[k]);
            }
            fprintf(fichier, "\n");

            // Afficher l'état du tableau à la console
            printf("Étape %d : ", i + 1);
            for (int k = 0; k < taille; k++) {
                printf("%d ", tableau[k]);
            }
            printf("\n");
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

    // Initialiser le tableau à partir des arguments
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

    // Appeler le tri par sélection
    triSelection(values, n, file);

    // Afficher les valeurs triées
    printf("Valeurs triées : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    // Libérer la mémoire et fermer le fichier
    free(values);
    fclose(file);

    return EXIT_SUCCESS;
}
