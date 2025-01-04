#include <stdio.h>
#include <stdlib.h>

// Fonction pour effectuer le tri par insertion
void tri_insertion(int arr[], int n, FILE *fichier) {
    for (int i = 1; i < n; i++) {
        int cle = arr[i]; // Élément à insérer
        int j = i - 1;

        // Déplace les éléments plus grands que la clé vers la droite
        while (j >= 0 && arr[j] > cle) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = cle;

        // Enregistre l'état du tableau dans le fichier
        fprintf(fichier, "Étape %d : ", i);
        for (int k = 0; k < n; k++) {
            fprintf(fichier, "%d ", arr[k]);
        }
        fprintf(fichier, "\n");

        // Affiche l'état du tableau à la console
        printf("Étape %d : ", i);
        for (int k = 0; k < n; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");
    }
}

// Fonction pour afficher un tableau
void afficher_tableau(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
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
    afficher_tableau(values, n);

    // Enregistrer les valeurs initiales dans le fichier
    fprintf(file, "Valeurs initiales : ");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", values[i]);
    }
    fprintf(file, "\n");

    // Appeler le tri par insertion
    tri_insertion(values, n, file);

    // Afficher les valeurs triées
    printf("Valeurs triées : ");
    afficher_tableau(values, n);

    // Libérer la mémoire et fermer le fichier
    free(values);
    fclose(file);

    return EXIT_SUCCESS;
}
