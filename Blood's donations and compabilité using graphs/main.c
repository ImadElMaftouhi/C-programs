//
// Created by: Imad EL Maftouhi on 25/12/2023
//

//Conception
/* afin de representer ce graphe dans C, on peut utiliser les representations suivants:
    -les matrices d'adjacenes  -> preferables 
    -Les matrices d'incidences -> Non preferables ( 8 lignes et 32 colonnes !)
    -Les listes des successeurs -> Favorisable pour la minimisation de memoire mais difficile. 

Nous on doit implementer une matrice d'adjacences, c'est que matrice carrée n*n tel que n = card(X)

                                      i/j | 1 2 3 4 5 6 7 8
                                    ------|---------------- 
                                        1 | . . . . . . . . 
                                        2 | . . . . . . . . 
                                        3 | . . . . . . . . 
                                        4 | . . . . . . . . 
                                        5 | . . . . . . . . 
                                        6 | . . . . . . . . 
                                        7 | . . . . . . . . 
                                        8 | . . . . . . . . 

    Si x_i est sommet initiale d'une relation (x_i ; x_j ) => On doit mettre 1, sinon on donne 0
    Si pas de relation entre x_i et x_j, on doit mettre un zero a leur intersection

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Fonction que va initliaser la matrice d'adjacence de notre graphe,
 * @param n : Le nombre des sommets dans le graphe
 * @return  : Une matrice de n x n dimension.
 */
int* matrice_adjacence(int n) {
    int* matrice = (int*)malloc(n * n * sizeof(int));

    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n ; j++) {
            printf("valeur de la case [%d][%d]: ", i+1, j+1);
            scanf("%d", (matrice + i * n + j));

            while ( *(matrice + i * n + j) != 1 && *(matrice + i * n + j) != 0) {
                printf("Choix doivent etre soit 1 soit 0, ressayer: ");
                scanf("%d", (matrice + i * n + j));
            }
        }
    }
    return matrice;
}

/**
 * Fonction qui affiche les valeurs stockées dans la matrice d'adjacence en indiquant au header les groupe sanguine
 * @param matrice : La matrice d'adjacence
 * @param n : La taille de la matrice, c'est le nombre des sommets dans le graph.
 */
void affichier_matrice_adjacence(int *matrice, int n){
    char type_sang[][5] = {"AB+", "AB-", "A+", "A-", "B+", "B-", "O+", "O-"};

    // Print header with blood types
    printf("\t");
    for (int i = 0; i < n; i++) {
        printf("%s\t", type_sang[i]);
    }

    for ( int i = 0 ; i < n ; i++){
        printf("\n%s\t", type_sang[i]);
        for ( int j = 0 ; j < n ; j++){
            printf("%d\t", *(matrice + i*n + j));
        }
    }
    printf("\n");
}

/**
 * Compter le nombres des predecessors d'un sommet donnée indiquée par son index
 * @param matrice : matrice d'adjacence
 * @param noeud : L'indice de notre sommet ( commandment par 1 )
 * @param n : la taille de la matrice.
 * @return : Le nombre total des successeurs de noeud
 */
int count_pred(int* matrice, int noeud, int n){
    noeud-=1;
    int counter = 0;
    for ( int i = 0 ; i < n ; i++){
        if ( *(matrice+i*n+noeud) == 1){
            counter++;
        }
    }
    return counter;
}

/**
 * Compter le nombres des successeurs d'un sommet donnée indiquée par son index
 * @param matrice : matrice d'adjacence
 * @param noeud : L'indice de notre sommet ( commencement par 1 )
 * @param n : la taille de la matrice.
 * @return : Le nombre total des successeurs de noeud
 */
int succ_count(int* matrice, int noeud, int n){
    noeud-=1;
    int count = 0;
    for ( int i = 0 ; i < n ; i++){
        if ( *(matrice + i + noeud *n  ) ){
            count++;
        }
    }
    return count;
}

/**
 * Fonction qui afficher les groups sanguine qui peuvent recevoire des sang depuis un groupe specifiéé
 * C'est l'ensemble des successeurs d'un noeud
 * @param matrice : La matrice d'adjacence
 * @param noeud : Indice de groupe sanguin ( commencent par 1 )
 * @param n : La taille de la matrice ( nombre total des sommets )
 * @return : un variable de type <<string>> qui contient des informations sur les successors
 */
char* show_succ(int* matrice, int noeud, int n) {
    noeud -= 1;
    char type_sang[][5] = {"AB+", "AB-", "A+", "A-", "B+", "B-", "O+", "O-"};

    char* succ = (char*)malloc(256);  // Allocate a reasonable buffer size
    succ[0] = '\0';

    for (int i = 0; i < n; i++) {
        if (*(matrice + i + noeud * n) == 1) {
            strcat(succ, type_sang[i]);
            strcat(succ, " ; ");
        }
    }

    return succ;
}

/**
 * Fonction qui afficher les groups sanguine qui peuvent partager du sang a un groupe specifique
 * C'est l'ensemble des predecessors d'un noeud
 * @param matrice : La matrice d'adjacence
 * @param noeud : Indice de groupe sanguin ( commencent par 1 )
 * @param n : La taille de la matrice ( nombre total des sommets )
 * @return : un variable de type <<string>> qui contient des informations sur les predecessors
 */
char* show_pred(int* matrice, int noeud, int n) {
    noeud -= 1;
    char type_sang[][5] = {"AB+", "AB-", "A+", "A-", "B+", "B-", "O+", "O-"};

    char* pred = (char*)malloc(256);  // Allocate a reasonable buffer size
    pred[0] = '\0';

    for (int i = 0; i < n; i++) {
        if (*(matrice + i * n + noeud) == 1) {
            strcat(pred, type_sang[i]);
            strcat(pred, " ; ");
        }
    }

    return pred;
}



int menu(){
    printf("\nVoici un petit menu pour vous aidez a naviguer: \n"
           "\n1. Definir  la matrice d'adjacence."
           "\n2. Affichier la matrice d'adjacence."
           "\n3. Affichier l'ensemble des predecesseurs d'un noeud."
           "\n4. Affichier l'ensemble des successeurs d'un noeud."
           "\n5. Quitter le programme."
           "\n\tChoix => ");
    int n; scanf("%d", &n); return n;
};


int main() {
    int n;
    printf("Nombre des sommets dans le graphe: ");
    scanf("%d", &n);

    while (n <= 0) {
        printf("Input non valide, graphe avec %d noeud pas possible.\nRessayer!\n", n);
        scanf("%d", &n);
    }

    int* matr_adj = matrice_adjacence(n);

    printf("\nVoici la matrice d'adjacence: \n ");
    affichier_matrice_adjacence(matr_adj, n);
    
    printf("\nChoisir un groupe sanguin: "
            "\n1. AB+ | 2. AB- | 3. A+  | 4. A-  |  5. B+  |  6. B-   |   7. O+  | 8.  O-  \n");
    int choix_typ_sang;
    scanf("%d", &choix_typ_sang);

    printf("\n\n\tVoici le nombre total des Predecesseurs de ce noeud. -> "
            "%d \n", count_pred(matr_adj, choix_typ_sang, n));

    printf("\nListe of predecesseurs: %s\n", show_pred(matr_adj, choix_typ_sang, n));


    printf("\n\n\tVoici le nombre total des Successeurs de ce noeud. -> "
            "%d \n", succ_count(matr_adj, choix_typ_sang, n));

    printf("\nListe of successeurs: %s\n", show_succ(matr_adj, choix_typ_sang, n));



    free(matr_adj);  
    return 0;
}

