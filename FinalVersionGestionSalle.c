#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CELL_WIDTH 20


typedef struct resrv {
    char nom[50];
    bool reservee;
    struct resrv* next;
} resrv;

typedef struct Jeur {
    resrv* plg;
    struct Jeur* link;
} Jeur;

void memory_message() {
    printf("\nMemory can't be allocated\n");
    exit(0);
}

resrv* add_time(resrv* ptr) {
    resrv* temp = malloc(sizeof(resrv));

    if (temp == NULL) {
        memory_message();
    }

    temp->reservee = false;
    strcpy(temp->nom, "");
    temp->next = ptr;

    return temp;
}

Jeur* add_days(Jeur* ptr) {
    Jeur* temp = malloc(sizeof(Jeur));
    if (temp == NULL) {
        memory_message();
    }
    temp->link = ptr;
    temp->plg = NULL;

    return temp;
}

void reserver(Jeur* head, int d, int h){

    Jeur* ptr = head;
    for ( int i = 1 ; i < d ; i++ ) {
        ptr = ptr->link;
    }
    resrv* ptr2 = ptr->plg;
    for ( int j = 1 ; j < h ; j++) {
        ptr2 = ptr2->next;
    }

    if ( ptr2->reservee ) { puts("\nLa salle est non disponible!"); exit(0); }

    char nom[50];
    printf("\nNom complet de Client --> ");
    scanf(" %[^\n]", nom);

    strcpy(ptr2->nom, nom);
    ptr2->reservee = true;

}

void chercher(Jeur* head){
	char nom[50];
    char time[5][20]= { {"09:00am-10:45am" },{"11:00am-12:45am"},{"01:00pm-2:45pm"},{"03:00pm-04:45pm"},{"05:00pm-06:45pm"} };
	char day[6][10]= { {"Lundi"}, {"Mardi"}, {"Mercredi"}, {"Jeudi"}, {"Vendredi"}, {"Samedie"} };
    int count1=0; int count2=0;
    printf("\nNom de client --> ");
	scanf(" %[^\n]", nom);
	int exist = -1;
	
    Jeur* ptr = head;

    while (ptr != NULL) {
        resrv* ptr2 = ptr->plg;

        while (ptr2 != NULL) {
            if ( strcmp(ptr2->nom, nom) == 0 ) { 
            printf("\nLe client %s a reservée la salle pour le %s a %s ", nom, day[count1], time[count2] ); 
            exist++; }  
            ptr2 = ptr2->next; count2++;
        }
        ptr = ptr->link; count1++;
    }
	if (exist == -1)
		printf("\nAucune reservation sous le nom %s", nom);
}

void supprimer(Jeur* head){
    Jeur* ptr = head;
    char nom[50];
    printf("\nLe nom de client --> ");
    scanf(" %[^\n]", nom );
    int count= -1;
    while ( ptr != NULL){
        resrv* ptr2 = ptr->plg;
        while ( ptr2!= NULL ){
            if ( strcmp (ptr2->nom, nom) == 0 ){
                strcmp(ptr2->nom, "");
                ptr2->reservee = false;
                count++;
            }
            ptr2=ptr2->next;
        }ptr=ptr->link;
    }
    if ( count == -1) printf("Aucun reservations sous le nom %s", nom);
}

void affichier_reservations(Jeur* head){
    char time[5][20]= { {"09:00am-10:45am" },{"11:00am-12:45am"},{"01:00pm-2:45pm"},{"03:00pm-04:45pm"},{"05:00pm-06:45pm"} };
	char day[6][10]= { {"Lundi"}, {"Mardi"}, {"Mercredi"}, {"Jeudi"}, {"Vendredi"}, {"Samedie"} };
    Jeur* ptr = head;
    int count=0;
    int WIDTH = 20;

    printf("%-20s", "Days");
    for (int i = 0; i < 5; i++) {
        printf("%-*s", CELL_WIDTH, time[i]);
    }
    printf("\n");
    
    // Print separator line
    for (int i = 0; i < 10 + 5 * CELL_WIDTH; i++) {
        printf("-");
    }
    printf("\n");
    
    // Print schedule
    while (ptr != NULL) {
        printf("%-20s |", day[count]); // Assuming week starts with Monday
        resrv* booking = ptr->plg;
        for (int i = 0; i < 5; i++) {
            if (booking != NULL) {
                printf("| %-*s |", CELL_WIDTH, booking->nom);
                booking = booking->next;
            } else {
                printf("%-*s", CELL_WIDTH, "");
            }
        }
        printf("\n");
        count++;
        ptr = ptr->link;
    }





}

int main() {
    Jeur* head = NULL;
    Jeur* day_ptr = NULL;

    // l'allocation des memoire
    for (int day_count = 0; day_count < 6; day_count++) {
        Jeur* new_day = add_days(day_ptr);
        head = new_day;

        for (int time_count = 0; time_count < 5; time_count++) {
            resrv* new_time = add_time(new_day->plg);
            new_day->plg = new_time;
        }
        day_ptr = new_day;
    }
    Jeur* ptr = head;

    // Afficher les address des pointeurs
    // while (ptr != NULL) {
    //     resrv* ptr2 = ptr->plg;

    //     while (ptr2 != NULL) {
    //         printf("%p \t", ptr2);
    //         ptr2 = ptr2->next;
    //     }

    //     printf("\n");
    //     ptr = ptr->link;
    // }
    // printf("\n\n\n\n");


    int choix;

	do {
        printf("Voici un petit menu pour vous aidez a naviger."
            "\n--------------------------------------------------"
                "\n0. Quitter le programme."
                "\n1. Effectuer une reservation"
                "\n2. Chercher une reservation d'un client"
                "\n3. Supprimer une reservation d'un client"
                "\n4. Afficher tous les reservations "
            "\n--------------------------------------------------"
            "\n\n\tChoix --> "
        );
        scanf("%d", &choix);


        switch (choix){
            case 0: 
                printf("\nAu revoir !");
                exit(1);
            case 1:
                printf("A quel jour voulez-vous reservee? : "
                "\n--------------------------------------------------"
                    "\n1. Lundi"
                    "\n2. Mardi"
                    "\n3. Mercredi"
                    "\n4. Jeudi"
                    "\n5. Vendredi "
                    "\n6. Samedi\n"
                "\n---> ");
               
                int d; scanf("%d", &d);
                if ( d < 1 || d > 6 ){
                    printf("Choix non valide!\n");
                    scanf(" %d", &d);
                }
               
                printf("\nA quel heure voudrais-vous reserver ?"
                    "\n--------------------------------------------------"
                    "\n1. 09:00am-10:45am"
                    "\n2. 11:00am-12:45pm"
                    "\n3. 01:00pm-2:45pm"
                    "\n4. 03:00pm-4:45pm"
                    "\n5. 05:00pm-6:45pm"
                    "\n---> ");

                int h; scanf("%d", &h);

                if ( h < 1 || h > 5) {
                    printf("Choix non valide!\n");
                    scanf("%d", &h);
                }


                reserver(head, d, h); 
                break;


                case 2:
                    chercher(head);
                    break;

                case 3:
                    supprimer(head);
                    break;

                case 4:
                    affichier_reservations(head);
                    break;

            }
    }  while (choix != 5);

    // Free allocated memory
    ptr = head;
    while (ptr != NULL) {
        resrv* ptr2 = ptr->plg;
        while (ptr2 != NULL) {
            resrv* temp = ptr2;
            ptr2 = ptr2->next;
            free(temp);
        }

        Jeur* temp = ptr;
        ptr = ptr->link;
        free(temp);
    }
    return 0;
}
