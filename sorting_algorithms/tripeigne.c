#include <stdio.h>
#include <stdlib.h>

// Fonction pour effectuer le tri peigne
void triPeigne(int tableau[], int taille, FILE *fichier) {
    int ecart = taille;
    int swap = 1;

    while (ecart > 1 || swap) {
        // Réduction de l'écart avec le facteur de réduction 1.3 (approximé à 10/13)
        if (ecart > 1) {
            ecart = (ecart * 10) / 13;
        }

        swap = 0;

        // Parcours du tableau avec l'écart actuel
        for (int i = 0; i < taille - ecart; i++) {
            if (tableau[i] > tableau[i + ecart]) {
                // Échange des éléments si nécessaire
                int temp = tableau[i];
                tableau[i] = tableau[i + ecart];
                tableau[i + ecart] = temp;
                swap = 1;

                // Enregistrer l'état actuel du tableau dans le fichier
                fprintf(fichier, "État après échange (écart = %d) : ", ecart);
                for (int j = 0; j < taille; j++) {
                    fprintf(fichier, "%d ", tableau[j]);
                }
                fprintf(fichier, "\n");

                // Afficher l'état actuel à la console
                printf("État après échange (écart = %d) : ", ecart);
                for (int k = 0; k < taille; k++) {
                    printf("%d ", tableau[k]);
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

    // Afficher et enregistrer les valeurs initiales
    printf("Valeurs initiales : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    fprintf(file, "Valeurs initiales : ");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", values[i]);
    }
    fprintf(file, "\n");

    // Appeler le tri peigne
    triPeigne(values, n, file);

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
