//
// Created by imadt on 12/3/2023.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//----------------------------------------------------------S T R U C T U R E-------------------------------------------------------------------//

typedef struct jour{
    char emp[3][3][100];
    struct jour* next;
    struct jour* prev;
}jour;

jour* head = NULL;
jour* tail = NULL;

//-----------------------------------------------------------F O N C T I O N--------------------------------------------------------------------//
void init_list();
int afficher();
int ajouter();
int modifier();
int chercher();
int plus_de_3();
int supprimer();
int menu();
 

//---------------------------------------------------------------M A I N------------------------------------------------------------------------//
int main (){
    jour* ptr = head;
    init_list();
    menu();




    //afficher les address.
    // printf("\nStarting from monday:\n");
    // ptr = head;
    // do{
    //     printf("\n%p\t", ptr);
    //     ptr = ptr->next;
    // } while ( ptr != head);


    // printf("\nStarting from Sunday:\n");
    // ptr = tail;
    // do{
    //     printf("\n%p\t", ptr);
    //     ptr = ptr->prev;
    // } while ( ptr != tail) ;


    //liberer la memoire.
    ptr = head;
    do {    
        jour* temp = ptr;
        ptr = ptr->next;
        free(temp);
    }while ( ptr != head);


    return 0;
}
//-----------------------------------------------------------F O N C T I O N--------------------------------------------------------------------//

void memory_message(){
    printf("\nError! Memory fault.");
}


void init_list(){
    for ( int i = 0 ; i < 7 ; i++){
        jour* temp = malloc( sizeof ( jour ) );
        
        if ( !temp ){
            memory_message();
            exit(0);
        }
        for ( int i = 0 ; i < 3 ; i++){
            strcpy(temp->emp[i][0], "");
            strcpy(temp->emp[i][1], "");
            strcpy(temp->emp[i][2], "");
            }

        temp->next = NULL;


        if (head == NULL){
            temp->prev = NULL;
            head = temp;
            tail = temp;
        }
        else{
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }
    
    tail->next = head;
    head->prev = tail;
}


int menu(){
    printf("\n\n-------------------Menu----------------------- "
        "\n( 1 ). Affichier la garde de la semaine."
        "\n( 2 ). Ajouter les médecin de la garde pour un jour."
        "\n( 3 ). Modifier les infos. des médecin de la garde."
        "\n( 4 ). Affichier les médecin qui interviennent plus de 3 fois."
        "\n( 5 ). Quitter."
        "\n\t\tVotre choix => " );

    int choix; scanf("%d", &choix);
    while( choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6) 
    {
        printf("\nChoix d'operation non valide, nouvelle choix => ");
        scanf("%d", &choix);
    }
    
    switch(choix){
        case 1:
            afficher();
            return menu();
        case 2: 
            ajouter();
            return menu();
        case 3:
            modifier();
           return menu();
        case 4:
            plus_de_3();
           return menu();
        case 5: 
            printf("\n\t\t\t\tAu revoir!");
            exit(0);
        default:
            printf("\nChoix Non valide! ressayer s'il-vous-plait.");
            return menu();

    }




}

int ajouter(){
    printf("\nQuel jour ? ( 1 - 7 ) => ");
    int j; scanf("%d", &j);
    if ( j != 1 && j!= 2 && j != 3 && j != 4 && j != 5 && j != 6 && j != 7 )
    {
        puts("\nChoix non valide, verifier votre saisie!");
        return ajouter();
    }

    jour* ptr = head;
    for ( int i = 1 ; i < j ; i++ ) 
    {
        ptr = ptr->next;
    }

    if ( !ptr )
    {
        printf("Error! Element non trouvée.");
        return ajouter();
    }

    if ( strcmp(ptr->emp[0][0], "") ){
        printf("\nLes médecin de la garde pour ce jour sont deja definit!, essayer l'option 3 ou 5.");
        return menu();
    }

    for ( int i = 0 ; i < 3 ; i++)
    {
        printf("\nNom d'employée nmr %d => ", i+1);
            scanf(" %[^\n]" ,ptr->emp[i][0]);
        printf("\nPrenom d'employée nmr %d => ", i+1);
            scanf(" %[^\n]" ,ptr->emp[i][1]);
        printf("\nSpécialité d'employée nmr %d => ", i+1);
            scanf(" %[^\n]" ,ptr->emp[i][2]);
    }

    return 1;
}

int afficher(){
    jour* ptr = head;
    
    puts("\nVoici tous les informations concernant la garde de cette semaine: ");
    int d = 0;
    
    do{
        d++;
        printf("\n Jour %d: ", d);
        for ( int a = 0 ; a < 3 ; a++){
            if ( !strcmp(ptr->emp[a][0], "") ){
                printf("\tVide.\t");
                continue;
            }
            printf("\n\tMédecin nmr %d: ", a+1);
            printf("\n\t\tNom: %s \t Prenom: %s \t\t Spécialité: %s", ptr->emp[a][0], ptr->emp[a][1], ptr->emp[a][2]);

        }
        ptr = ptr->next;
    } while ( ptr != head);
    return 1;
}

int modifier(){
    jour* ptr = tail;
    printf("\nVoulez-vous modifier la garde de quel jour? ( 1 - 7 ) => ");
    int choix; scanf("%d", &choix);
    while ( choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 && choix != 7 ){
        printf("\nChoix non valide, nouvelle choix => ");
        scanf("%d", &choix);
    }

    for ( int i = 0 ; i < choix ; i++){
        ptr = ptr->next;
    }

    if ( ptr == NULL){
        printf("\nError, pointeur est vide. Retourne!");
        return menu();
    }

    printf("\nLes médecin existant: ");
    for ( int i = 0 ; i < 3 ; i++){
        printf("\n\tMédecin nmr %d: ", i+1);
        printf("\n\t\tNom: %s ; Prenom : %s ; spécialité: %s", ptr->emp[i][0], ptr->emp[i][1], ptr->emp[i][2]);
    }
    printf("\nQuel médecin voulez-vous modifier/changer ? ( 1 - 3 )=> ");
    int m; scanf("%d", &m);
    while ( m != 1 && m != 2 && m != 3){
        puts("\nChoix non valide, nouvelle choix => ");
        scanf("%d", &m);
    }

    printf("\nNom => ");
    char temp[100]; 
    scanf(" %[^\n]", temp);
    strcpy(ptr->emp[m-1][0], temp);

    printf("\nPrenom => ");
    scanf(" %[^\n]", temp);
    strcpy(ptr->emp[m-1][1], temp);
    
    printf("\nSpécialité => ");
    scanf(" %[^\n]", temp);
    strcpy(ptr->emp[m-1][2], temp);

    printf("\n\t\t\tOpération réussie!");
}


int plus_de_3(){
    jour* ptr = head;
    do{

        for ( int i = 0 ; i < 3 ; i++)
        {
            jour* ptr2 = ptr;
        int check = 0;
            do{
                for ( int j = 0 ; j < 3 ; j++)
                {
                    if ( !strcmp( ptr->emp[i][0], ptr2->emp[j][0] ) )
                    {
                        check++;
                    }
                }
                ptr2 = ptr2->next;
            } while ( ptr2 != head );

            // doit soustracter 1 de notre var check car on compare notre elemenet avec lui meme au debut.
            if (  check > 3 ) 
            {
                printf("\nLe médecin %s %s figure plus 3 fois: ", ptr->emp[i][0], ptr->emp[i][1]);
            }
            check = 0 ;
        }
        ptr = ptr->next;
    }  while ( ptr != head );
    
    return 1;
}