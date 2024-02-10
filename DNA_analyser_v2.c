//
// Created by imadt on 12/02/2023.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//--------------------------------------------------------------------------S T R U C T U R E--------------------------------------------------------------------------------//

typedef struct sequence{
    char data;
    struct sequence* next;
    struct sequence* prev;
}sequence;

typedef struct node{
    sequence* element;
    struct node* next;
    struct node* prev;
}node;

node* head = NULL;
node* tail = NULL;

//---------------------------------------------------------------------------F O N C T I O N---------------------------------------------------------------------------------//

void memory_message(){
    printf("Error! Memory allocation failed\n");
}

int seq_checker(char c){
	if ( c != 'A' && c != 'a' && c != 'T' && c != 't' && c != 'C' && c != 'c' && c != 'G' && c != 'g' ) {
		return 1;
	}
	else {
		return 0;
	}
}

int trouver_taille(sequence* ptr){
    int i = 0;
    if ( head == NULL){
        printf("Aucun séquence n'est encore insérer!");
        return 0;
    }
    while (ptr != NULL){
        i++;
        ptr = ptr->next;
    }

    return i;
}

sequence* addbase(){
	sequence* head = NULL;
	sequence* ptr = NULL;
	sequence* temp = malloc(sizeof(sequence));

    if ( temp == NULL){
        memory_message();
    }

	printf("\nTaille de votre sequence --> ");
	int n; scanf("%d", &n);

	char seq[n];
	printf("\nLes bases de la sequence (base par base) :");

	for ( int i = 0 ; i < n ; i++)
    {
		printf("\n\tBase nmr`%d --> ", i+1);
		scanf(" %c", &seq[i]);

		while ( seq_checker ( seq[i] ) == 1 )
		{
			puts("Error, base non valide! Ressayer");
            scanf(" %c", &seq[i]);
			// return addbase();
		}

		seq[i] = toupper( seq[i] );
	}

	temp->data = seq[0];
	temp->prev = NULL;
	temp->next = NULL;
	head = temp;

	ptr = head;
	for ( int i = 1 ; i < n ; i++)
	{
		sequence* temp2 = malloc(sizeof(sequence));

		if ( temp2 == NULL) { memory_message(); /*return addbase()*/ }

		temp2->data = seq[i];
		temp2->prev = ptr;
		temp2->next = NULL;
		ptr->next = temp2;
		ptr = temp2;
	}

	return head;
}

node* addsequence(node* p){
    node* temp = malloc(sizeof(node));
    temp->element = NULL;

    if ( temp == NULL){
        memory_message();
    }

    temp->next = NULL; //parametres par default pour tous les nouveau sequence cree.

    //liee les sequence cree
    if ( head == NULL){
        temp->prev = NULL;
        head = temp;
    } else {
        temp->prev = p;
        p->next = temp;
    }

    // Partie des donnees
	temp->element = addbase();
    return temp;
}

void afficher_totale() {
    node* ptr = head;
    while (ptr != NULL) {
        sequence* temp = ptr->element;
        while (temp != NULL) {
            printf("%c->", temp->data);
            temp = temp->next;
        }
        ptr = ptr->next;
    }
}

void afficher_partielle() {
    node* ptr = head;
    int i = 1;
    while (ptr != NULL) {
        printf("\nSequence nmr^%d : ", i);
        i++;
        sequence* temp = ptr->element;
        while (temp != NULL) {
            printf("%c->", temp->data);
            temp = temp->next;
        }
        ptr = ptr->next;
    }
}

void print_at_pos() {
    int n;
    printf("\n\tL'ordre de votre sequence  --> ");
    scanf("%d", &n);

    node* ptr = head;

    for (int i = 1; i < n; i++) {
        if (ptr == NULL) {
            printf("\nSequence non existante, vérifiez l'ordre.\n");
            return;
        }
        ptr = ptr->next;
    }

    printf("\nLa sequence a l'ordre %d est: ", n);
    sequence* temp = ptr->element;
    while (temp != NULL) {
        printf("%c->", temp->data);
        temp = temp->next;
    }
}

void comparer(){
	node* ptr = head;
    int pos;
	printf("\nQuel sequence voulez-vous tester ? ordre--> ");
	scanf("%d", &pos);

    if ( pos <= 0){
        printf("\nOrdre invalide, veuillez entrer un nombre positif.\n");
        return comparer();
    }

	for ( int i = 1 ; i < pos ; i++){
		ptr = ptr->next;
	}

	if ( ptr == NULL){
		printf("\nSequence pas trouver, verifier l'ordre entrer");
		return comparer();
	}

	printf("\ntaile de votre sequence -- > ");
	int n; 
    scanf("%d", &n);

	char seq[n];

	for ( int i =0 ; i<n ; i++){
		printf("\nElement %d", i+1);
		scanf(" %c" , &seq[i]);
		
		if ( seq_checker ( seq[i] ) ){
			printf("\nError! Verifier la base saisir");
			return comparer();
		}
		seq[i] = toupper( seq[i] );
	}	
	
	int i = 0;
	sequence* temp = ptr->element;
	while ( temp != NULL && temp->data == seq[i] )
        {
            i++; 
            temp = temp->next;
        } 

    if ( i == n  ){
        printf("\nLes deux brins sont egaux ");
    } else {
		printf("\nLes deux brins d'ADN sont differentes");
	}
}

void comparer2(){
    int o1, o2;
    node* ptr1 = head;
    node* ptr2 = head;

    printf("\nOrdre de 1er sequence --> ");
    scanf("%d", &o1);
    if ( o1 <= 0)
        {
            printf("\nOrdre invalide, verifiez la saisie.\n");
            return comparer2();
        }


    printf("\nOrdre de 2eme sequence --> ");
    scanf("%d", &o2);
    if ( o2 <= 0 || o2 == o1 )
        {
            printf("\nOrdre invalide, verifiez la saisie.\n");
            return comparer2();
        }


    //parcours les listes par ptr1 et ptr2 a l'odre o1 et o2.
    for ( int i = 1 ; i < o1 ; i++){
        ptr1 = ptr1->next;
    }
    for ( int j = 1 ; j < o2 ; j++){
        ptr2 = ptr2->next;
    }

    if ( ptr1 == NULL || ptr2 == NULL ){
        printf("\nSequence pas trouver, verifier l'ordre entrer");
        return comparer2();
    }

    sequence* sous_ptr1 = ptr1->element;
    sequence* sous_ptr2 = ptr2->element;

    int checker = 0; 
    if ( trouver_taille(sous_ptr1) != trouver_taille(sous_ptr2) ) 
    {
        printf("\nLes deux sequence sont de differentes taille.");
        return comparer2();
    }
    else{
        // char mutation[ trouver_taille(sous_ptr1) ];
        // int i=0;
        while ( sous_ptr1 != NULL ){
            if ( sous_ptr1->data == sous_ptr2->data ){
                checker++;
            }else{
                // mutaion[i] = checker;
                printf("\n\t\tMutation au niveau de base nmr %d .", checker+1);
            }
            // i++;
            sous_ptr1 = sous_ptr1->next;
            sous_ptr2 = sous_ptr2->next;
        }
    }

    sous_ptr1 = ptr1->element;
    if ( checker == trouver_taille(sous_ptr1)) {
        printf("\nLes deux sequences sont egaux.");
    } else
    {
        // printf("%d \t %d", checker, trouver_taille(sous_ptr1) );
        printf("\n\t\tLes deux sequences sont differentes.");
        
    }

}

void supprimer(){
    printf("\nOdre de sequence a supprimer d'ADN. --> ");
    int ordre;
    scanf("%d", &ordre);
    node* ptr = head;
    for ( int i = 1 ; i < ordre ; i++){
        ptr = ptr->next;
    }

    if ( ptr == NULL){
        printf("\nElement non existant, verifier l'ordre saisie.");
        return supprimer();
    }

    if ( ptr == head){
        head = ptr->next;
        ptr->next->prev = NULL;
    }
    else if ( ptr == tail){
        tail = ptr->prev;
        ptr->prev->next = NULL;

    } 
    else {
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        free(ptr);
    }
    

}

int menu(){
	printf("\n-----------------------------------"
		"\nVoici un menu des operations valable."
		"\n0. Quitter le programme."
		"\n1. Inserer une nouvelle séquence d'ADN dans la structure définie."
		"\n2. Afficher l'ensemble de l'ADN stocké dans la structure."
		"\n3. Afficher les differentes séquences possible dans notre ADN."
		"\n4. Rechercher une séquence spécifique dans la structure de l'ADN."
		"\n5. Comparer deux ADN pour deux patients différents. "
        "\n6. Comparer deux sequence differentes dans la meme brin d'ADN."
        "\n7. Supprimer une sequence."
		"\n----------------------------------------\n"
		"\nVotre choix --> ");


	int choix; scanf("%d",&choix);

	switch (choix)
	{
		case 0:
			return 0;
		case 1:
			tail = addsequence(tail);
			break;
		case 2:
			afficher_totale();
			break;
		case 3:
			afficher_partielle();
			break;
		case 4:
			print_at_pos();
			break;
		case 5:
			comparer();
			break;

        case 6:
            comparer2();
            break;
        case 7:
            supprimer();
            break;
		default:
			printf("Error! Choix non valide");
			break;
	}

	while (getchar() != '\n');
	
	return 1;
}

//---------------------------------------------------------------------------------M A I N----------------------------------------------------------------------------------// 

int main (){

	while( menu () ) { }

	// //affichier les address des elements 
    // node* ptr = head;
    // while ( ptr != NULL){
    //     sequence* temp = ptr->element
    //     while ( temp != NULL) 
    //          {
    //          printf("header: %p \t base: %p\n", temp, temp->element);
    //          temp = temp->next;
    //          }
    //     ptr = ptr->next;
    // }


//liberer de mémoire
	node* ptr = head;
   	while (ptr != NULL) {
       node* temp = ptr;
        ptr = ptr->next;

        sequence* temp_seq = temp->element;
        while (temp_seq != NULL) {
            sequence* temp_seq2 = temp_seq;
            temp_seq = temp_seq->next;
            free(temp_seq2);
        }

        free(temp);
    }
    return 0;
}
