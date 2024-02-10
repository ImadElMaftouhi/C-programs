//
// Created by imadt on 11/25/2023.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//--------------------------------------------------Structure---------------------------------------------------------//

typedef struct artiste{
    char nom[100];
    char nationnalite[100];
    struct artiste* next;
}artiste;

typedef struct chanson{
    char titre[100];
    float duree;
    artiste* ar;
    struct chanson* link;
}chanson;

chanson* biblio = NULL; //global.
chanson* tail = NULL; //global.

//------------------------------------------DECLARATION DES FONCTIONS-------------------------------------------------//

void memory_message();
chanson* ajouterChanson();
void ajouterArtiste(chanson* ch);
void getArtisteData(artiste* artiste);
void afficherBiblio();
chanson* ChercherArtiste(char artiste[]);
void ChercherLong();
void ChercherNat();
void freeMemory();
int supprimer();
int menu();


//-----------------------------------------------------MAIN-----------------------------------------------------------//


int main(){
    switch ( menu() ){
        case 1:
            tail = ajouterChanson();
            return main();
        case 2:
            if ( supprimer() ) { return main(); }
            else
            {
                printf("\nError! titre non trouvée.");
                return main();
            }
        case 3:
            ChercherNat();
            return main();
        case 4:
            ChercherLong();
            return main();
        case 5:
            afficherBiblio();
            return main();
        case 6:
            printf("\nNom d'artiste a chercher --> ");
            char nom[100]; scanf(" %[^\n]", nom);
            if ( ChercherArtiste(nom) ){
                printf("\nVotre artiste apparait dans %s", ChercherArtiste(nom)->titre);
            }
            else
            {
                puts("\nArtiste non trouvée!");
                return main();
            }
        case 0:
            printf("\nAu revoir.");
    }

    freeMemory();
    return 0;
}

//---------------------------------------------------Fonction---------------------------------------------------------//


chanson* ajouterChanson(){
    chanson* temp = malloc (sizeof( chanson ));
    temp->ar = NULL;
    if (temp == NULL){
        memory_message();
        exit(errno);
    }
    printf("\nTitre de chanson: ");
    scanf(" %[^\n]", temp->titre);

    ajouterArtiste(temp);

    printf("\nDuree du chanson: ");
    scanf("%f", &temp->duree);

    if ( biblio == NULL) { biblio = temp; }
    else { tail->link = temp; }

    return temp;
}


void ajouterArtiste(chanson* ch){
    artiste* ptr = NULL;
    printf("\nCombien d'artiste pour ce morceau ? ---> ");
    int n; scanf("%d", &n);

    for ( int i = 0 ; i < n ; i++){
        artiste* temp = malloc ( sizeof ( artiste ) );
        if ( temp == NULL ){
            memory_message();
            exit(errno);
        }
        getArtisteData(temp);
        temp->next= NULL;
        if ( ch->ar == NULL ) { ch->ar = temp; ptr = temp;}
        else
        {
            ptr->next = temp;
            ptr = temp;
        }
//        ch->ar = temp;
    }
}

void getArtisteData(artiste* artiste){
    printf("\nNom d'artiste --> ");
    scanf(" %[^\n]", artiste->nom);
    printf("\nNationnalite d'artiste --> ");
    scanf(" %[^\n]", artiste->nationnalite);
}

void afficherBiblio(){
    chanson* ptr = biblio;
    while ( ptr != NULL){
        artiste* ptr2 = ptr->ar;
        printf("\n-Titre de morceau: %s",ptr->titre);
        int i = 1;
        while( ptr2 != NULL){
            printf("\n\t-nom d'artiste n*%d: %s",i , ptr2->nom);
            ptr2 = ptr2->next;
            i++;
        }
        printf("\n\t\t-Durée de morceau: %.2f",ptr->duree);
        ptr = ptr->link;
    }
}
void freeMemory() {
    chanson* current = biblio;
    while (current != NULL) {
        artiste* currentArtists = current->ar;
        while (currentArtists != NULL) {
            artiste* temp = currentArtists;
            currentArtists = currentArtists->next;
            free(temp);
        }
        chanson* temp = current;
        current = current->link;
        free(temp);
    }
}

chanson* ChercherArtiste(char *ar){
    chanson* ptr = biblio;
    while ( ptr != NULL ){
        artiste* ptr2 = ptr->ar;
        while( ptr2 != NULL ){
            if ( !strcmp(ptr2->nom, ar) )
            {
                return ptr; //return la chanson dont l'artiste figure
            }
            ptr2 = ptr2->next;
        }
        ptr = ptr->link;
    }
    return 0;
}

void ChercherLong(){
    chanson* ptr = biblio;
    while ( ptr != NULL ){
        if ( ptr->duree > 30 ){
            printf("\nLa chanson %s a une duree superieure a 30min!", ptr->titre);
        }
        ptr = ptr->link;
    }
}

void ChercherNat(){
    printf("\nQuel-est la nationnalitée de votre artiste? --> ");
    char nom[100]; scanf(" %[^\n]", nom);
//    for ( int i = 0 ; nom[i]!= '\0' ; i++){
//        nom[i] = tolower( nom[i] );
//    }
    chanson* ptr = biblio;
    while ( ptr != NULL){
        artiste* ptr2 = ptr->ar;
        while ( ptr2 != NULL){
            if ( !strcmp(ptr2->nom, nom) ){
                printf("\nVotre artiste avec nationnalitée donnée est: %s", ptr2->nom);
            }
            ptr2 = ptr2->next;
        }

        ptr = ptr->link;
    }

}

int supprimer(){
    printf("\nQuel-est le titre de chanson a suppimer ? --> ");
    char titre[100]; scanf(" %[^\n]", titre);

    chanson* ptr = biblio;
    // delete from start / delete from end / delete from middle.
    if ( !strcmp(biblio->titre, titre) )
    {
        biblio = biblio->link;
        free(ptr);
        return 1;
    }

    if ( !strcmp(tail->titre, titre) ) { tail = NULL; return 1;}

    while ( ptr->link != NULL){
        if ( !strcmp( ptr->link->titre, titre) ){
            ptr = ptr->link->link;
            free(ptr->link);
            return 1;
        }
        ptr = ptr->link;
    }
    return 0;
}


int menu(){
    printf("\n( 1 ). Ajouter une chanson."
           "\n( 2 ). Supprimer une chanson."
           "\n( 3 ). Chercher les artistes avec une nationnalitée specifique."
           "\n( 4 ). Afficher les chanson de duree > 30min ."
           "\n( 5 ). Visionner la bibliothèque complet"
           "\n( 6 ). Chercher un artiste dans la biblio."
           "\n( 0 ). Quitter."
           "\n\tVotre Choix --> ");
    int choix;
    scanf("%d", &choix);
    return choix;
}


void memory_message(){
    printf("\nError, Memory failure!");
}