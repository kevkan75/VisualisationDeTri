#include <stdio.h>
#include <stdlib.h>

// Fonction pour afficher le tableau
void afficherTableau(int tableau[], int taille) {
    for (int i = 0; i < taille; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");
}

// Fonction pour échanger deux éléments
void echanger(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction pour réorganiser un sous-arbre en tas (entasser)
void entasser(int tableau[], int taille, int indice, FILE *fichier) {
    int plusGrand = indice;
    int gauche = 2 * indice + 1;
    int droite = 2 * indice + 2;

    // Trouver le plus grand élément parmi le nœud et ses enfants
    if (gauche < taille && tableau[gauche] > tableau[plusGrand]) {
        plusGrand = gauche;
    }
    if (droite < taille && tableau[droite] > tableau[plusGrand]) {
        plusGrand = droite;
    }

    // Si le plus grand n'est pas la racine, échanger et entasser récursivement
    if (plusGrand != indice) {
        echanger(&tableau[indice], &tableau[plusGrand]);

        // Enregistrer l'état actuel du tableau dans le fichier
        fprintf(fichier, "Entasser : ");
        for (int i = 0; i < taille; i++) {
            fprintf(fichier, "%d ", tableau[i]);
        }
        fprintf(fichier, "\n");

        printf("Entasser : ");
        afficherTableau(tableau, taille);

        entasser(tableau, taille, plusGrand, fichier);
    }
}

// Fonction pour effectuer le tri par tas
void triParTas(int tableau[], int taille, FILE *fichier) {
    // Construire le tas (réorganiser le tableau)
    for (int i = taille / 2 - 1; i >= 0; i--) {
        entasser(tableau, taille, i, fichier);
    }

    // Extraire un par un les éléments du tas
    for (int i = taille - 1; i > 0; i--) {
        // Échanger la racine actuelle avec la dernière feuille
        echanger(&tableau[0], &tableau[i]);

        // Réorganiser le tas pour exclure l'élément extrait
        entasser(tableau, i, 0, fichier);

        // Enregistrer l'état actuel du tableau dans le fichier
        fprintf(fichier, "Après extraction : ");
        for (int j = 0; j < taille; j++) {
            fprintf(fichier, "%d ", tableau[j]);
        }
        fprintf(fichier, "\n");

        printf("Après extraction : ");
        afficherTableau(tableau, taille);
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

    // Afficher et enregistrer les valeurs initiales
    printf("Valeurs initiales : ");
    afficherTableau(values, n);

    fprintf(file, "Valeurs initiales : ");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", values[i]);
    }
    fprintf(file, "\n");

    // Appeler le tri par tas
    triParTas(values, n, file);

    // Afficher les valeurs triées
    printf("Valeurs triées : ");
    afficherTableau(values, n);

    // Libérer la mémoire et fermer le fichier
    free(values);
    fclose(file);

    return EXIT_SUCCESS;
}
