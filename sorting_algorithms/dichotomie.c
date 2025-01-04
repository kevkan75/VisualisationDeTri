#include <stdio.h>
#include <stdlib.h>

// Fonction de tri par dichotomie
void dichotomySort(int arr[], int n, FILE *outputFile) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Recherche dichotomique pour trouver la position correcte
        int left = 0, right = i - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2; // Évite les dépassements d'entiers
            if (arr[mid] < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Décale les éléments pour insérer la clé
        for (j = i - 1; j >= left; j--) {
            arr[j + 1] = arr[j];
        }
        arr[left] = key;

        // Affichage de l'état actuel du tableau
        printf("Étape %d:\n", i);
        for (int k = 0; k < n; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n\n");  // Saut de ligne après chaque étape

        // Écriture dans le fichier
        fprintf(outputFile, "Étape %d:\n", i);
        for (int k = 0; k < n; k++) {
            fprintf(outputFile, "%d ", arr[k]);
        }
        fprintf(outputFile, "\n\n");  // Saut de ligne dans le fichier
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Erreur: Veuillez fournir les valeurs à trier comme arguments.\n");
        return EXIT_FAILURE;
    }

    int n = argc - 1;
    int *values = malloc(n * sizeof(int));
    if (values == NULL) {
        fprintf(stderr, "Erreur: Allocation mémoire échouée.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        values[i] = atoi(argv[i + 1]);
    }

    printf("Valeurs initiales :\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\n\n");

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Erreur: Impossible d'ouvrir le fichier de sortie.\n");
        free(values);
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Valeurs initiales :\n");
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%d ", values[i]);
    }
    fprintf(outputFile, "\n\n");

    dichotomySort(values, n, outputFile);

    fclose(outputFile);
    free(values);
    return EXIT_SUCCESS;
}
