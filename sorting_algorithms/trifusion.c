#include <stdio.h>
#include <stdlib.h>

// Fonction pour fusionner deux sous-tableaux
void fusion(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Création des tableaux temporaires
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Copie des données dans L[] et R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Fusion des tableaux L[] et R[] dans arr[l..r]
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copie des éléments restants de L[], s'il y en a
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copie des éléments restants de R[], s'il y en a
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Libération de la mémoire temporaire
    free(L);
    free(R);
}

// Fonction pour le tri fusion non récursif
void triFusionNonRecursif(int arr[], int n, FILE *fichier) {
    for (int taille_actuelle = 1; taille_actuelle <= n - 1; taille_actuelle = 2 * taille_actuelle) {
        for (int l = 0; l < n - 1; l += 2 * taille_actuelle) {
            int m = l + taille_actuelle - 1;
            int r = (l + 2 * taille_actuelle - 1 < n - 1) ? (l + 2 * taille_actuelle - 1) : (n - 1);

            // Fusion des sous-tableaux arr[l..m] et arr[m+1..r]
            fusion(arr, l, m, r);

            // Afficher l'état du tableau après chaque fusion
            fprintf(fichier, "Fusion : ");
            for (int i = 0; i < n; i++) {
                fprintf(fichier, "%d ", arr[i]);
            }
            fprintf(fichier, "\n");

            printf("Fusion : ");
            for (int i = 0; i < n; i++) {
                printf("%d ", arr[i]);
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

    // Ouverture du fichier de sortie
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

    // Appeler le tri fusion
    triFusionNonRecursif(values, n, file);

    // Libérer la mémoire et fermer le fichier
    free(values);
    fclose(file);

    return EXIT_SUCCESS;
}
