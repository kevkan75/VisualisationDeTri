#include <stdio.h>
#include <stdlib.h>

// Fonction pour effectuer le tri cocktail
void triCocktail(int tableau[], int taille, FILE *fichier) {
    int debut = 0;
    int fin = taille - 1;
    int swap = 1;

    while (swap) {
        swap = 0;

        // Passage de gauche à droite
        for (int i = debut; i < fin; i++) {
            if (tableau[i] > tableau[i + 1]) {
                // Échanger les éléments si nécessaire
                int temp = tableau[i];
                tableau[i] = tableau[i + 1];
                tableau[i + 1] = temp;
                swap = 1;

                // Enregistrer l'état dans le fichier
                fprintf(fichier, "Gauche -> Droite : ");
                for (int j = 0; j < taille; j++) {
                    fprintf(fichier, "%d ", tableau[j]);
                }
                fprintf(fichier, "\n");

                // Affichage pour visualisation
                printf("Gauche -> Droite : ");
                for (int k = 0; k < taille; k++) {
                    printf("%d ", tableau[k]);
                }
                printf("\n");
            }
        }

        // Si aucun échange n'a eu lieu, le tri est terminé
        if (!swap) break;

        swap = 0;
        fin--;

        // Passage de droite à gauche
        for (int i = fin - 1; i >= debut; i--) {
            if (tableau[i] > tableau[i + 1]) {
                // Échanger les éléments si nécessaire
                int temp = tableau[i];
                tableau[i] = tableau[i + 1];
                tableau[i + 1] = temp;
                swap = 1;

                // Enregistrer l'état dans le fichier
                fprintf(fichier, "Droite -> Gauche : ");
                for (int j = 0; j < taille; j++) {
                    fprintf(fichier, "%d ", tableau[j]);
                }
                fprintf(fichier, "\n");

                // Affichage pour visualisation
                printf("Droite -> Gauche : ");
                for (int k = 0; k < taille; k++) {
                    printf("%d ", tableau[k]);
                }
                printf("\n");
            }
        }

        debut++;
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

    // Lecture des arguments et conversion en tableau
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

    // Appeler le tri cocktail
    triCocktail(values, n, file);

    // Libérer la mémoire et fermer le fichier
    free(values);
    fclose(file);

    return EXIT_SUCCESS;
}
