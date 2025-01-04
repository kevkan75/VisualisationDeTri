#include <stdio.h>
#include <stdlib.h>

// Fonction pour partitionner le tableau
int partition(int arr[], int low, int high, FILE *fichier) {
    int pivot = arr[high]; // Dernier élément comme pivot
    int i = low - 1;       // Index du plus petit élément

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            // Échange des éléments arr[i] et arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Échange de arr[i+1] et arr[high] (pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    // Enregistrer l'état actuel dans le fichier
    fprintf(fichier, "Partition avec pivot %d : ", pivot);
    for (int k = low; k <= high; k++) {
        fprintf(fichier, "%d ", arr[k]);
    }
    fprintf(fichier, "\n");

    // Retourne l'index du pivot
    return i + 1;
}

// Fonction pour le tri rapide (Quick Sort)
void quickSort(int arr[], int low, int high, FILE *fichier) {
    if (low < high) {
        // Partitionnement et obtention du pivot
        int pivot = partition(arr, low, high, fichier);

        // Affichage de l'étape actuelle à la console
        printf("Étape avec pivot %d : ", arr[pivot]);
        for (int i = low; i <= high; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Tri récursif des sous-tableaux
        quickSort(arr, low, pivot - 1, fichier);
        quickSort(arr, pivot + 1, high, fichier);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Erreur : Veuillez fournir des valeurs à trier.\n");
        return EXIT_FAILURE;
    }

    int n = argc - 1;
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Erreur : Allocation mémoire échouée.\n");
        return EXIT_FAILURE;
    }

    // Initialisation du tableau avec les arguments
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    // Ouvrir le fichier de sortie
    FILE *fichier = fopen("output.txt", "w");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier de sortie.\n");
        free(arr);
        return EXIT_FAILURE;
    }

    // Affichage du tableau avant le tri
    printf("Tableau avant le tri : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Appeler le tri rapide
    quickSort(arr, 0, n - 1, fichier);

    // Affichage du tableau après le tri
    printf("Tableau après le tri : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Libérer la mémoire et fermer le fichier
    free(arr);
    fclose(fichier);

    return EXIT_SUCCESS;
}
