#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PERSONNES 8

typedef struct {
    int matrice[MAX_PERSONNES][MAX_PERSONNES];
    char personnes[MAX_PERSONNES];
    int nb_personnes;
} ReseauSocial;

void initialiserReseau(ReseauSocial *reseau) {
    int i, j;
    for (i = 0; i < MAX_PERSONNES; i++) {
        for (j = 0; j < MAX_PERSONNES; j++) {
            reseau->matrice[i][j] = 0;
        }
    }
    reseau->nb_personnes = 0;
}
void amisPersonne(ReseauSocial *reseau, char nomPersonne) {
    int i, indexPersonne;
    for (i = 0; i < reseau->nb_personnes; i++) {
        if (reseau->personnes[i] == nomPersonne) {
            indexPersonne = i;
            break;
        }
    }
    printf("Amis de %c : ", nomPersonne);
    for (i = 0; i < reseau->nb_personnes; i++) {
        if (i != indexPersonne && reseau->matrice[indexPersonne][i] != 0) {
            printf("%c ", reseau->personnes[i]);
        }
    }
    printf("\n");
}

void ajouterPersonne(ReseauSocial *reseau, char nomPersonne, int amities[MAX_PERSONNES]) {
    int i;
    reseau->personnes[reseau->nb_personnes] = nomPersonne;
    for (i = 0; i < reseau->nb_personnes; i++) {
        reseau->matrice[reseau->nb_personnes][i] = amities[i];
        reseau->matrice[i][reseau->nb_personnes] = amities[i];
    }
    reseau->nb_personnes++;
}

void cheminAmitie(ReseauSocial *reseau, char personneDepart, char personneArrivee) {
    int i, j;
    int visited[MAX_PERSONNES];
    int queue[MAX_PERSONNES];
    int front = 0, rear = 0;

    for (i = 0; i < reseau->nb_personnes; i++) {
        visited[i] = 0;
    }

    for (i = 0; i < reseau->nb_personnes; i++) {
        if (reseau->personnes[i] == personneDepart) {
            front = rear = 0;
            visited[i] = 1;
            queue[rear++] = i;

            while (front != rear) {
                int current = queue[front++];
                printf("%c ", reseau->personnes[current]);

                if (reseau->personnes[current] == personneArrivee) {
                    printf("\nChemin d'amitié trouvé!\n");
                    return;
                }

                for (j = 0; j < reseau->nb_personnes; j++) {
                    if (reseau->matrice[current][j] && !visited[j]) {
                        visited[j] = 1;
                        queue[rear++] = j;
                    }
                }
            }
        }
    }

    printf("\nPas de chemin d'amitié trouvé.\n");
}
void supprimerPersonne(ReseauSocial *reseau, char nomPersonne) {
    int i, j, indexPersonne;
    for (i = 0; i < reseau->nb_personnes; i++) {
        if (reseau->personnes[i] == nomPersonne) {
            indexPersonne = i;
            break;
        }
    }
    for (i = indexPersonne; i < reseau->nb_personnes - 1; i++) {
        reseau->personnes[i] = reseau->personnes[i + 1];
    }
    for (i = indexPersonne; i < reseau->nb_personnes - 1; i++) {
        for (j = 0; j < reseau->nb_personnes; j++) {
            reseau->matrice[i][j] = reseau->matrice[i + 1][j];
            reseau->matrice[j][i] = reseau->matrice[j][i + 1];
        }
    }
    reseau->nb_personnes--;
}

int main() {
    ReseauSocial reseau;
    initialiserReseau(&reseau);

    // Ajouter des personnes avec des intensités d'amitié
    ajouterPersonne(&reseau, 'A', (int[]){0, 1, 0, 1});
    ajouterPersonne(&reseau, 'B', (int[]){1, 0, 1, 1});
    ajouterPersonne(&reseau, 'C', (int[]){0, 1, 0, 0,});
    ajouterPersonne(&reseau, 'D', (int[]){1, 1, 0, 0});
   

            amisPersonne(&reseau, 'A');



    // Recherche d'un chemin d'amitié entre deux personnes
    cheminAmitie(&reseau, 'A', 'C');

    return 0;
}
