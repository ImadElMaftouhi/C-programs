//
// Created by: Imad EL Maftouhi on 01/01/2024
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define INFINITY 9999


/*------------------------------------------------ S T R U C T U R E -------------------------------------------------*/

typedef struct voisinage{
    int poid;
    int sommet;
    struct voisinage* next;
}voisinage;

typedef struct graphe{
    int sommets;
    struct voisinage* list[MAX];
}graphe;


/*---------------------------------------------  F O N C T I O N S ---------------------------------------------------*/

graphe* init_graphe(int NbrSommet){
    graphe* temp = (graphe* )malloc(sizeof(struct graphe));
    temp->sommets = NbrSommet;

    for ( int i = 0 ; i < MAX ; i++ ){
        temp->list[i] = NULL;
    }
    return temp;
}


void AjouterElement(graphe* G){
    if ( G == NULL ){printf("Graphe est encore NULL"); return;}
    int poid;
    voisinage* ptr = NULL;

    for( int i = 0 ; i < G->sommets ; i++){
//        if ( i == sommet-1)
//            continue;
        ptr = G->list[G->sommets];
        printf("Quel-est le poid de la relation entre le sommet %d et %d ( 0 si pas de relations)? => ", G->sommets+1, i+1);
        scanf("%d", &poid);

        if ( poid == 0)
            continue;

        voisinage *temp = (voisinage*)malloc(sizeof(voisinage));
        if ( temp == NULL ){
            printf("Allocation de memoire echoue. Retourne... ");
            return;
        }

        temp->poid = poid;
        temp->next = NULL;
        temp->sommet = i;

        if ( ptr == NULL){
            G->list[G->sommets] = temp;
            continue;
        }else {
            while (ptr->next != NULL) {
                ptr = ptr->next;
            }
            ptr->next = temp;
            continue;
        }
    }
    G->sommets++;
}


void AjouterElement2(graphe* G, int source, int sommet, int poid) {
    if (G == NULL) {
        printf("Graphe est encore NULL");
        return;
    }

    if (poid == 0 || poid == INFINITY){
        return;
    }

    voisinage* temp = (voisinage*)malloc(sizeof(voisinage));
    if (temp == NULL) {
        printf("Allocation de memoire echoue. Retourne... ");
        return;
    }

    temp->poid = poid;
    temp->next = NULL;
    temp->sommet = sommet;

    voisinage* ptr = G->list[source];

    if (ptr == NULL) {
        G->list[source] = temp;
    } else {
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
}


void SupprimerSommet(graphe* G, int sommet){
    sommet--;
    int flag = 0;
    voisinage* ptr1 = NULL;

    for ( int i = 0 ; i < G->sommets ; i++) {
        if (sommet == i)
            continue;
        ptr1 = G->list[i];

        if (ptr1 == NULL) {
            printf("NULL vertex detected, check your graph please!\n");
            continue;
        }

        if (ptr1->sommet == sommet) {
            G->list[i] = G->list[i]->next;
            free(ptr1);
            continue;
        }

        while (ptr1->next != NULL) {
            if (ptr1->next->sommet == sommet) {
                voisinage* temp = ptr1->next;
                ptr1->next = ptr1->next->next;
                free(temp);
                flag = 1;
                break;
            }
            ptr1 = ptr1->next;
        }

        if (flag)
            continue;

        if (ptr1->sommet == sommet) {
            free(ptr1);
            continue;
        }
    }
    voisinage* current = G->list[sommet];
    while (current != NULL) {
        voisinage* temp = current;
        current = current->next;
        free(temp);
    }

    for (int i = sommet + 1; i < G->sommets; i++) {
        G->list[i - 1] = G->list[i];
    }

    G->list[G->sommets - 1] = NULL;

    G->sommets--;
}



void AfficherGraphe(graphe* G) {
    if (G == NULL) {
        printf("Graphe est NULL\n");
        return;
    }

    printf("Adjacency List Representation:\n");

    for (int i = 0; i < G->sommets; i++) {
        printf("Vertex %d: ", i + 1);
        voisinage* ptr = G->list[i];

        while (ptr != NULL) {
            printf("(%d, %d) ", ptr->sommet + 1, ptr->poid);
            ptr = ptr->next;
        }

        printf("\n");
    }
}


void AfficherVoisinage(graphe* G, int sommet){
    if ( G == NULL) {
        printf("Graphe est encore null!\n");
        return;
    }
    voisinage* ptr = G->list[sommet-1];
    if (ptr == NULL){
        printf("Ce sommet ne contient pas de voisinage.\n");
        return;
    }
    printf("Les voisinages de sommet numero %d sont: ", sommet);
    while ( ptr != NULL ){
        printf("\n\tNumero de sommet : %d  | \t Poid de relation : %d", ptr->sommet+1, ptr->poid);
        ptr = ptr->next;
    }
}

void VerifierTrajet(graphe* G, int source, int destination) {
    if (G == NULL) {
        printf("Graphe est NULL\n");
        return;
    }

    if (source < 1 || source > G->sommets || destination < 1 || destination > G->sommets) {
        printf("Sommet(s) invalide(s)\n");
        return;
    }

    voisinage* ptr = G->list[source - 1];
    while (ptr != NULL) {
        if (ptr->sommet + 1 == destination) {
            printf("\nIl existe un vol direct entre les villes %d et %d.", source, destination);
            return;
        }
        ptr = ptr->next;
    }

    for (int i = 0; i < G->sommets; i++) {
        if (i + 1 != source && i + 1 != destination) {
            ptr = G->list[source - 1];
            while (ptr != NULL) {
                if (ptr->sommet + 1 == i + 1) {
                    voisinage* ptr2 = G->list[i];
                    while (ptr2 != NULL) {
                        if (ptr2->sommet + 1 == destination) {
                            printf("Il existe un trajet indirect entre les villes %d et %d via la ville %d.\n", source, destination, i + 1);
                            return;
                        }
                        ptr2 = ptr2->next;
                    }
                }
                ptr = ptr->next;
            }
        }
    }

    printf("Il n'existe pas de vol direct ou indirect entre les villes %d et %d.\n", source, destination);
}


/*---------------------------------------------------- M A I N -------------------------------------------------------*/

int main(){

    graphe* G = init_graphe(8);

    int matrix[8][8] = {
            {0, 6, INFINITY, 2, INFINITY,INFINITY,8,INFINITY},
            {6, 0, 4, 1, 2, INFINITY, 2, INFINITY},
            {INFINITY, 4, 0 , INFINITY, 8, 1, INFINITY},
            {2, 1 , INFINITY, 0 , 1, INFINITY, INFINITY, INFINITY},
            {INFINITY, 2, 8, 1, 0, 9 , INFINITY, INFINITY},
            {INFINITY, INFINITY, 1, INFINITY, 9, 0, INFINITY, 2},
            {8 ,2 ,3 , INFINITY, INFINITY, INFINITY, 0 , 7},
            {INFINITY, INFINITY,INFINITY, INFINITY,INFINITY, 2,7, 0}
    };


    for ( int i = 0 ; i < 8 ; i++){
        for ( int j = 0 ; j < 8 ; j++){
            AjouterElement2(G, i, j, matrix[i][j]);
        }
    }


    AfficherGraphe(G);

    SupprimerSommet(G,2);

    printf("\nAfter deleting : \n");

    AfficherGraphe(G);

    AjouterElement(G);

    printf("\nAfter adding : \n");

    AfficherGraphe(G);

    AfficherVoisinage(G, 4);

    VerifierTrajet(G, 1, 5);
    VerifierTrajet(G, 1, 2);
    VerifierTrajet(G, 3, 7);


    return 0;
}