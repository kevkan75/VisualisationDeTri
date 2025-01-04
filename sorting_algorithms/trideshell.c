#include <stdio.h>
#include <stdlib.h>

// Fonction pour effectuer le tri de Shell
void triShell(int tableau[], int taille, FILE *fichier) {
    // Calcul des écarts pour le tri de Shell
    for (int ecart = taille / 2; ecart > 0; ecart /= 2) {
        for (int i = ecart; i < taille; i++) {
            int temp = tableau[i];
            int j;

            // Déplacer les éléments qui sont plus grands que temp pour créer la place
            for (j = i; j >= ecart && tableau[j - ecart] > temp; j -= ecart) {
                tableau[j] = tableau[j - ecart];
            }
            tableau[j] = temp;

            // Enregistrer l'état du tableau dans le fichier
            fprintf(fichier, "Écart %d : ", ecart);
            for (int k = 0; k < taille; k++) {
                fprintf(fichier, "%d ", tableau[k]);
            }
            fprintf(fichier, "\n");

            // Afficher l'état du tableau à la console
            printf("Écart %d : ", ecart);
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

    // Lire les arguments et initialiser le tableau
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

    // Appeler la fonction de tri de Shell
    triShell(values, n, file);

    // Libérer la mémoire et fermer le fichier
    free(values);
    fclose(file);

    return EXIT_SUCCESS;
}
