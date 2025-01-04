#include <stdio.h>
#include <stdlib.h>

// Fonction pour effectuer le tri pair-impair
void triPairImpair(int arr[], int n, FILE *fichier) {
    int trie = 0; // Indicateur pour savoir si le tableau est trié

    while (!trie) {
        trie = 1;

        // Comparaison et échange des éléments pairs
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                // Échanger les éléments pairs
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                trie = 0;

                // Enregistrer l'état du tableau dans le fichier
                fprintf(fichier, "Étape (pairs) : ");
                for (int j = 0; j < n; j++) {
                    fprintf(fichier, "%d ", arr[j]);
                }
                fprintf(fichier, "\n");
            }
        }

        // Comparaison et échange des éléments impairs
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                // Échanger les éléments impairs
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                trie = 0;

                // Enregistrer l'état du tableau dans le fichier
                fprintf(fichier, "Étape (impairs) : ");
                for (int j = 0; j < n; j++) {
                    fprintf(fichier, "%d ", arr[j]);
                }
                fprintf(fichier, "\n");

                // Afficher l'état du tableau à la console
                printf("Étape (impairs) : ");
                for (int k = 0; k < n; k++) {
                    printf("%d ", arr[k]);
                }
                printf("\n");
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Erreur : Veuillez fournir les valeurs à trier comme arguments.\n");
        return EXIT_FAILURE;
    }

    int n = argc - 1;
    int *values = malloc(n * sizeof(int));
    if (values == NULL) {
        fprintf(stderr, "Erreur : Allocation mémoire échouée.\n");
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

    // Ouvrir le fichier de sortie
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier de sortie.\n");
        free(values);
        return EXIT_FAILURE;
    }

    // Enregistrer les valeurs initiales dans le fichier
    fprintf(outputFile, "Valeurs initiales : ");
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%d ", values[i]);
    }
    fprintf(outputFile, "\n");

    // Appeler le tri pair-impair
    triPairImpair(values, n, outputFile);

    // Afficher les valeurs triées
    printf("Valeurs triées : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    // Fermer le fichier et libérer la mémoire
    fclose(outputFile);
    free(values);

    return EXIT_SUCCESS;
}
