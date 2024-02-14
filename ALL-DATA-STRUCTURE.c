//
// created by Imad EL Maftouhi on 12/09/2023

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//////////////////////////////////////////////////////// L I S T E    C H A I N E E    S I M P L E ////////////////////////////////////////////////////////
typedef struct liste{
   	int data;
   	struct liste* next;
}liste;

//passage par reference
liste* ajouter_debut_ref(liste** head, int valeur){

	liste* temp = (liste*) malloc (sizeof(liste));
	if ( temp == NULL ) { return NULL; }

	temp->data = valeur;
	temp->next = NULL;
	if ( *head == NULL) { *head = temp; }
	else
	{
		temp->next = *head;
  		*head = temp;
	}
}

//passage par valeur
liste* ajouter_debut_val(liste* head, int valeur)
{
	liste* temp = (liste*)malloc(sizeof(liste));
	if ( temp == NULL ) { return NULL;}

	temp->data = valeur;
	temp->next= NULL;
	if ( head == NULL ) { return temp; }
	else
	{
		temp->next = head;
		return temp;
	}
}

//passage par valeur
liste* ajouter_fin_val(liste* head, int valeur){
	liste* temp = (liste*)malloc(sizeof(liste));

	if ( temp == NULL ){
		return NULL;
	}

	temp->next = NULL;
	temp->data = valeur;

	if ( head == NULL ){
		return temp;
	}
	else
	{
		liste* ptr = head;
		while( ptr->next != NULL )
		{
			ptr = ptr->next;
		}
		ptr->next = temp;
		ptr = temp;
	}

	return head;
}

//passage par referrence
liste* ajouter_fin_ref(liste** head, int valeur){
	liste* temp = (liste*)malloc(sizeof(liste));

	if (temp == NULL) { return NULL; }
	temp->data = valeur;
	temp->next = NULL;

	if ( head == NULL) { *head = temp; }
	else
	{
		liste* ptr = *head;
		while ( ptr->next != NULL )
		{
			ptr = ptr->next;
		}
		ptr->next = temp;
	}
}

liste* chercher(liste* head, int valeur){
	if ( head == NULL ){ printf("\n\n\tNULL LISTE!"); return NULL; }

	liste* ptr = head;

	while ( ptr != NULL && ptr->data != valeur)
	{ ptr = ptr->next; }

	return ptr;
}

void affichier(liste* head){
	if ( head == NULL)
	{
		printf("\nListe NULL!");
	}

	liste* ptr = head;
	while ( ptr != NULL )
	{
		printf("\nLa valeur a l'address %x <=> %p est:\t%d",ptr ,ptr ,ptr->data);
		ptr = ptr->next;
	}

}

void freeMemory(liste* head) {
    if (head == NULL) {
        return;
    }
    liste* ptr = head;
    liste* ptr2 = NULL;
    while (ptr != NULL) {
        ptr2 = ptr;
        ptr = ptr->next;
        free(ptr2);
    }
}

//////////////////////////////////////////////////////// D O U B L E M E N T    C H A I N E E ////////////////////////////////////////////////////////

typedef struct liste_dbl{
	int data;
	struct liste_dbl* next;
	struct liste_dbl* prev;
}liste_dbl;

//passage par referrence
liste_dbl* ajouter_debut_dbl_ref(liste_dbl** head_dbl,liste_dbl** tail, int valeur){
	liste_dbl* temp = (liste_dbl*)malloc(sizeof(liste_dbl));
	if ( temp == NULL) {	return NULL; }

	temp->data= valeur;
	temp->next = NULL;
	temp->prev = NULL;
	if ( *head_dbl == NULL) { *head_dbl = temp; *tail = temp;}
	else
	{
		(*head_dbl)->prev = temp;
		temp->next = *head_dbl;
		*head_dbl = temp;
	}

}

//passage par valeur
liste_dbl* ajouter_debut_dbl_val(liste_dbl* head_dbl,liste_dbl* tail, int valeur){
	liste_dbl* temp = (liste_dbl*)malloc(sizeof(liste_dbl));
	if ( temp == NULL ) { return NULL; }

	temp->data = valeur;
	temp->prev = NULL;
	temp->next = NULL;
	if ( head_dbl == NULL ) { tail = temp; return temp; }
	else
	{
		head_dbl->prev = temp;
		temp->next = head_dbl;
		head_dbl = temp;
	}
	return head_dbl;
}

//passage par referrence
liste_dbl* ajouter_fin_dbl_ref(liste_dbl** head_dbl,liste_dbl** tail, int valeur){
	liste_dbl* temp = (liste_dbl*)malloc(sizeof(liste_dbl));
	if ( temp == NULL){	return NULL;	}
	temp->data = valeur;
	temp->next = NULL;

	if ( *head_dbl == NULL)
	{
		temp->prev = NULL;
		*head_dbl = temp;
		*tail = temp;
	}
	else
	{
		(*tail)->next = temp;
		temp->prev = *tail;
		*tail = temp;
	}
//	return temp;
}

//passage par val
liste_dbl* ajouter_fin_dbl_val(liste_dbl* head_dbl, liste_dbl* tail, int valeur){
	liste_dbl* temp = (liste_dbl*)malloc(sizeof(liste_dbl));
	if ( temp == NULL ){ return NULL;}
	temp->data = valeur;
	temp->next = NULL;

	if ( head_dbl == NULL )
	{
		temp->prev = NULL;
		head_dbl = temp;
		tail = temp;
	}
	else
	{
		tail->next = temp;
		temp->prev = tail;
	}

	return temp; // pour l'associer a 'tail' pour qu'il pointe toujours sur le dernier elemenet.
}

//affichier dans le sens direct ( head -> tail )
void affichier_dbl_direct(liste_dbl* head){
	if ( head == NULL ){printf("\n\tNULL LISTE!");return;}

	liste_dbl* ptr = head;
	while ( ptr != NULL )
	{
		printf("\nLa valeur a l'address %x <=> %p est:\t%d",ptr ,ptr ,ptr->data);
		ptr = ptr->next;
	}
}

//affichier dans le sens inverse ( tail -> head )
void affichier_dbl_inverse(liste_dbl* tail){
	if ( tail == NULL ) {	printf("\n\tNULL LISTE!"); return;	}

	liste_dbl* ptr = tail;
	while ( ptr != NULL)
	{
		printf("\nLa valeur a l'address %x <=> %p est:\t%d",ptr ,ptr ,ptr->data);
		ptr = ptr->prev;
	}
}

liste_dbl* chercher_list_dbl(liste_dbl** head_dbl, liste_dbl** tail, int valeur){
	if ( *head_dbl == NULL ){ printf("\n\n\t\tNULL LISTE!"); return NULL;}

	liste_dbl* ptr = *head_dbl;
	liste_dbl* ptr2 = *tail;

	while ( ptr != NULL && ptr2 != NULL)
	{
		if ( ptr->data == valeur) { return ptr; }
		if ( ptr2->data == valeur) { return ptr2; }
		ptr = ptr->next;
		ptr2 = ptr2->prev;
	}

	return NULL;
}

void freeMemory_dbl(liste_dbl** head){
	liste_dbl* ptr = *head;
    liste_dbl* ptr2 = NULL;
	while ( ptr != NULL ){
        ptr2 = ptr;
		ptr = ptr->next;
		free(ptr2);
	}
}


//////////////////////////////////////////////////////// L I S T E    C I R C U L A I R ////////////////////////////////////////////////////////

typedef struct liste_crl{
	int data;
	struct liste_crl* next;
	struct liste_crl* prev;
}liste_crl;

//passage par valeur
liste_crl* ajouter_debut_liste_crl_val(liste_crl* head, liste_crl** tail_crl, int valeur){
	liste_crl* temp = (liste_crl*)malloc(sizeof(liste_crl));
	if ( temp == NULL ){ return NULL; }

	temp->data= valeur;
	if ( head == NULL )
	{
			temp->next = temp;
			temp->prev = temp;
			*tail_crl = temp;
		return temp;
	}
	else
	{
		head->prev= temp;
		temp->next = head;
		head = temp;
	}

	return head;
}

//passage par referrence
liste_crl* ajouter_debut_liste_crl_ref(liste_crl** head, liste_crl** tail_crl, int valeur){

	liste_crl* temp = (liste_crl*)malloc(sizeof(liste_crl));
	if ( temp == NULL ) { return NULL;	}

	temp->data = valeur;

	if ( *head == NULL ){
		temp->next = temp;
		temp->prev = temp;
		*head = temp;
		*tail_crl = temp;
	}
	else
	{
		(*head)->prev = temp;
		temp->next = *head;
		*head = temp;
	}
}

//passage par referrence
liste_crl* ajouter_fin_liste_crl_ref(liste_crl** head, liste_crl** tail, int valeur){
	liste_crl* temp = (liste_crl*)malloc(sizeof(liste_crl));
	if ( temp == NULL ){ return NULL;	}

	temp->data= valeur;
	if ( *head == NULL )
	{
		temp->next = temp;
		temp->prev = temp;
		*tail = temp;
		*head = temp;
	}
	else
	{
		temp->next = NULL;
		temp->prev = *tail;
		(*tail)->next = temp;
		*tail = temp;
	}

}

//passage par valeur
liste_crl* ajouter_fin_liste_crl_val(liste_crl* head, liste_crl* tail, int valeur){
	liste_crl* temp = (liste_crl*)malloc(sizeof(liste_crl));
	if ( temp == NULL ){ return NULL; }

	temp->data = valeur;
	if ( head == NULL )
	{
		temp->next = temp;
		temp->prev = temp;
		tail = head = temp;
		return temp;
	}

	temp->prev = tail;
	tail->next = temp;
	tail = temp;
	return tail;
}

liste_crl* chercher_crl(liste_crl* head, liste_crl* tail, int valeur){
	if ( head == NULL) {  printf("\n\n\tNULL LISTE!."); return NULL; }
	liste_crl* p1 = head;
	liste_crl* p2 = tail;
	while ( p1 != tail && p2 != head)
	{
		if ( p1->data == valeur) { return p1; }
		if ( p2->data == valeur) { return p2; }
		p1 = p1->next;
		p2 = p2->prev;
	}
	return NULL;
}

void affichier_liste_crl_direct(liste_crl* head){
	if ( head == NULL ){ printf("\n\n\t\tNULL LISTE!"); return; }

	liste_crl* ptr = head;
	do
	{
		printf("\nLa valeur a l'address %x <=> %p est:\t%d",ptr ,ptr ,ptr->data);
		ptr = ptr->next;
	}	while ( ptr != head);
}

void affichier_liste_crl_inverse(liste_crl* tail){
	if ( tail == NULL) { printf("\n\n\t\tNULL LISTE!"); return; }
	liste_crl* ptr = tail;
	do{
		printf("\nLa valeur a l'address %x <=> %p est:\t%d",ptr ,ptr ,ptr->data);
		ptr = ptr->prev;
	} while ( ptr != tail );
}

void freeMemory_crl(liste_crl** head){
	while ( *head != NULL)
	{
        liste_crl* ptr = *head;
        *head = (*head)->next;
		free(ptr);
	}
}

/////////////////////////////////////////////////////////    P I L E     ////////////////////////////////////////////////////////

typedef struct pile{
	int data;
	struct pile* next;
	struct pile* prev;
}pile;

//passage par valeur
pile* empiler_val(pile* head, pile** tail, int valeur){
	pile* temp = (pile*)malloc(sizeof(pile));
	if ( temp == NULL ) { return NULL;	}

	temp->data = valeur;
	temp->next = NULL;
	temp->prev = NULL;
	if ( head == NULL )
	{
		*tail = temp;
		head = temp;
		return temp;
	}
	temp->next = head;
	head->prev = temp;
	head = temp;
	return head;
}

pile* depiler_val(pile* head){
	if ( head == NULL) { printf("\n\n\tNULL LISTE."); return NULL;}
	pile* temp = head;
	head = head->next;
	free(temp);
	return head;
}

//passage par referrence
pile* empiler_ref(pile** head,pile** tail, int valeur){
	pile* temp = (pile*)malloc( sizeof(pile) );
	if ( temp == NULL ){ return NULL; }

	temp->data = valeur;
	temp->next = NULL;
	temp->prev = NULL;

	if ( *head == NULL ) { *tail = temp; *head = temp; }
	(*head)->prev = temp;
	temp->next = *head;
	*head = temp;
}

pile* depiler_ref(pile** head){
	if ( *head == NULL ) { printf("\n\n\tNULL LISTE."); return NULL; }
    pile* temp = *head;
    *head = (*head)->next;
	free(temp);
}

//chercher par referrence
pile* chercher_pile(pile* head, pile* tail, int valeur){
	if ( head == NULL ) { printf("\n\n\tNULL LISTE!"); return NULL; }
	pile* p1 = head;
	pile* p2 = tail;
	while ( p1 != tail && p2 != head)
	{
		if ( p1->data == valeur ) { return p1; }
		if ( p2->data == valeur ) { return p2; }

		p1 = p1->next;
		p2 = p2->prev;
	}
	return NULL;
}

//affichage.
void affichier_pile(pile* head){
	if ( head == NULL ){ printf("\n\n\tNULL LISTE!"); }

	pile* ptr = head;

	while ( ptr != NULL )
	{
		printf("\nLa valeur a l'address %x <=> %p est:\t%d",ptr ,ptr ,ptr->data);
		ptr = ptr->next;
	}
}

void freeMemory_pile(pile** head){
	if ( *head == NULL ){ printf("\nNULL LISTE");return;}
	while ( *head != NULL )
	{
//        printf("\nHead is: \t%p", *head);
        pile* temp = *head;
//        printf("\nTemp is: \t%p", temp);
        *head = (*head)->next;
//        printf("\nNew head is: \t%p", *head);
        free(temp);
//        printf("\ntemp is freed;");
	}
    printf("\nstage 3");
}



////////////////////////////////////////////////////////    F I L E     ////////////////////////////////////////////////////////

typedef struct file{
	int data;
	struct file* next;
	struct file* prev;
}file;

//passage par referrence
file* enfiler_ref(file** head, file** tail, int valeur){
	file* temp = (file*)malloc(sizeof(file));
	if ( temp == NULL ){  return NULL;}

	temp->data = valeur;
	temp->next = NULL;
	temp->prev = NULL;

	if ( *head == NULL)
	{
		*tail = *head = temp;
	}

	temp->next = *head;
	(*head)->prev = temp;
	*head = temp;
}

file* defiler_ref(file** tail){
	if ( *tail == NULL ){ printf("\n\n\tNULL LISTE!"); return NULL;}
	*tail = (*tail)->prev;
	free((*tail)->next);
}

//passage par valeur
file* enfiler_val(file* head, file** tail, int valeur){
	file* temp = (file*)malloc(sizeof(file));
	if ( temp == NULL ){ return NULL;	}

	temp->data = valeur;
	temp->next = NULL;
	temp->prev = NULL;
	if ( head == NULL )
	{
		*tail = head = temp;
		return temp;
	}
	temp->next = head;
	head->prev = temp;
	head = temp;
	return temp;
}

file* defiler_val(file* tail){
	if ( tail == NULL )  { printf("\n\n\tNULL LISTE!"); return NULL; }
	tail = tail->prev;
	free(tail->next);
	return tail;
}

file* chercher_file(file* head, file* tail, int valeur){
	if ( head == NULL ) {printf("\n\t\t\tNULL LISTE!"); return NULL;}

	file* p1 = head;
	file* p2 = tail;
	while ( p1 != tail && p2 != head)
	{
		if ( p1->data == valeur ) {return p1;}
		if ( p2->data == valeur ) {return p2;}
		p1 = p1->next;
		p2 = p2->prev;
	}
	return NULL;
}

void affichier_file(file* tail){
	if ( tail == NULL ){ printf("\n\n\tNULL LISTE!"); return; }

	file* ptr = tail;

	while ( ptr != NULL )
	{
		printf("\nLa valeur a l'address %x <=> %p est:\t%d",ptr ,ptr ,ptr->data);
		ptr = ptr->prev;
	}
}

void freeMemory_file(file** head){
	if ( *head == NULL ) {return;}
	while ( *head != NULL)
	{
        file* temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}



// GRAPHE IMPLEMANTATION /////////



float** ImportMatrice(char *path){
	if ( path == NULL ){
		printf("Le chemin n'est pas specifiée a l'appelle de la fonction ImportMatrice()!");
		return NULL;
	}

	// add logic to import data here.	

}



////////////////////////////////////////////////////////  M A I N  ////////////////////////////////////////////////////////
int main(){
	int n; // la variable oú on va stocker la valeur a chercher dans n'importe quelle liste.

////////////////////////////////////////////////////////////////////////////////////////////////////
	struct liste* head = NULL;


	ajouter_debut_ref(&head, 1);
	ajouter_debut_ref(&head, 2);
	ajouter_debut_ref(&head, 3);
	head = ajouter_debut_val(head, 4);
	head = ajouter_debut_val(head, 5);
	head = ajouter_debut_val(head, 6);

////////////////////////////////////////

	ajouter_fin_ref(&head, 10);
	ajouter_fin_ref(&head, 20);
	ajouter_fin_ref(&head, 30);

	ajouter_fin_val(head, 10);
	ajouter_fin_val(head, 20);
	ajouter_fin_val(head, 30);

////////////////////////////////////////

	printf("\nVoici une liste chainee simple: \n");
	affichier(head);

	printf("\n\nQuel nombre vous cherchez? => ");
	scanf("%d", &n);
	if ( chercher(head,n) != NULL )
	{
		printf("\nla valeur %d est enregistrée a l'address %x <=> %p dans notre liste simple.\n", n, chercher(head,n), chercher(head,n) );
	}
	else { printf("\nValeur n'existe pas dans notre liste.\n");	}




////////////////////////////////////////////////////////////////////////////////////////////////////

	struct liste_dbl* head_dbl = NULL;
	struct liste_dbl* tail = NULL;

	printf("\n\nVoici une liste doublement chaine: \n");

	ajouter_debut_dbl_ref(&head_dbl, &tail, 11);
	ajouter_debut_dbl_ref(&head_dbl, &tail, 22);
	ajouter_debut_dbl_ref(&head_dbl, &tail, 33);

	head_dbl = ajouter_debut_dbl_val(head_dbl, tail, 11);
	head_dbl = ajouter_debut_dbl_val(head_dbl, tail, 22);
	head_dbl = ajouter_debut_dbl_val(head_dbl, tail, 33);

/////////////////////////////////////////

	ajouter_fin_dbl_ref(&head_dbl, &tail, 77);
	ajouter_fin_dbl_ref(&head_dbl, &tail, 88);
	ajouter_fin_dbl_ref(&head_dbl, &tail, 99);

	tail = ajouter_fin_dbl_val(head_dbl,tail, 77);
	tail = ajouter_fin_dbl_val(head_dbl,tail, 88);
	tail = ajouter_fin_dbl_val(head_dbl,tail, 99);

	printf("\n\t\tDoublement chainee dans le sens direct ( head -> tail )");
	affichier_dbl_direct(head_dbl);
	printf("\n\t\tDoublement chainee dans le sens inverse ( tail -> head )");
	affichier_dbl_inverse(tail);

	printf("\n\nQuel nombre vous cherchez? => ");
	scanf("%d", &n);

	liste_dbl* chr = chercher_list_dbl(&head_dbl, &tail , n);
	if ( chr != NULL )
	{
		printf("\nla valeur %d est enregistrée a l'address %x <=> %p dans notre liste doublement chainee.\n", n,chr,chr);
	}
	else { printf("\nValeur n'existe pas dans notre liste.\n");	}


////////////////////////////////////////////////////////////////////////////////////////////////////

	struct liste_crl* head_crl = NULL;
	struct liste_crl* tail_crl = NULL;

	printf("\n\nVoici une liste circulaire doublement chainee.\n");

/////////////////////////////////////////////////////

	head_crl = ajouter_debut_liste_crl_val(head_crl, &tail_crl, 111);
	head_crl = ajouter_debut_liste_crl_val(head_crl, &tail_crl, 222);;
	head_crl = ajouter_debut_liste_crl_val(head_crl, &tail_crl, 333);

	ajouter_debut_liste_crl_ref(&head_crl,&tail_crl, 111);
	ajouter_debut_liste_crl_ref(&head_crl,&tail_crl, 222);
	ajouter_debut_liste_crl_ref(&head_crl,&tail_crl, 333);

/////////////////////////////////////////////////////

	tail_crl = ajouter_fin_liste_crl_val(head_crl, tail_crl, 100);
	tail_crl = ajouter_fin_liste_crl_val(head_crl, tail_crl, 200);
	tail_crl = ajouter_fin_liste_crl_val(head_crl, tail_crl, 300);

	ajouter_fin_liste_crl_ref(&head_crl,&tail_crl, 100);
	ajouter_fin_liste_crl_ref(&head_crl,&tail_crl, 200);
	ajouter_fin_liste_crl_ref(&head_crl,&tail_crl, 300);

/////////////////////////////////////////////////////

	printf("\nLe dernier element est: %x <=> %p : val = %d\n", tail_crl, tail_crl, tail_crl->data);
	printf("\nLe premier element est: %x <=> %p : val = %d\n", head_crl, head_crl, head_crl->data);

	tail_crl->next = head_crl;
	head_crl->prev = tail_crl;

	printf("\n\n\tListe Circulaire dans le sens direct ( head -> tail ): \n");
	affichier_liste_crl_direct(head_crl);
	printf("\n\t\tListe Circulaire dans le sens inverse ( tail -> head ) \n");
	affichier_liste_crl_inverse(tail_crl);


	printf("\nQuel nombre cherhcez-vous ? => ");
	scanf("%d", &n);
	liste_crl* ptr = chercher_crl(head_crl, tail_crl,n);
	if ( ptr != NULL ){
		printf("\nla valeur %d est enregistrée a l'address %x <=> %p dans notre liste circulaire doublement chainee.\n", n,ptr,ptr);
	}
	else { printf("\nValeur n'existe pas dans notre liste.\n");	}
	free(ptr);




////////////////////////////////////////////////////////////////////////////////////////////////////

	printf("\n\nVoici un exemple de la structure de donnee 'PILE'.\n");

	struct pile* head_pile = NULL;
	struct pile* tail_pile = NULL;

	head_pile = empiler_val(head_pile,&tail_pile, 404);
	head_pile = empiler_val(head_pile,&tail_pile, 505);
	head_pile = empiler_val(head_pile,&tail_pile, 606);


	empiler_ref(&head_pile,&tail_pile,404);
	empiler_ref(&head_pile,&tail_pile,505);
	empiler_ref(&head_pile,&tail_pile,606);

	printf("\n\t\t\t I N F O .\n");
	printf("\n\t\t\t\t head = %d\tAddress: %x <=> %p", head_pile->data, head_pile, head_pile);
	printf("\n\t\t\t\t tail = %d\tAddress: %x <=> %p", tail_pile->data, tail_pile, tail_pile);

	affichier_pile(head_pile);

	printf("\n\tDepiler: ");

	printf("\n\t\tPar valeur: \n");
	head_pile = depiler_val(head_pile);
	affichier_pile(head_pile);

	printf("\n\t\tPar referrence: \n");
	depiler_ref(&head_pile);
	affichier_pile(head_pile);

	printf("\n\nQuel valeur vous-cherchez ? => ");
	scanf("%d", &n);
	pile* ptr2 = chercher_pile(head_pile, tail_pile, n);
	if ( ptr2 != NULL )
	{
		printf("\nla valeur %d est enregistrée a l'address %x <=> %p dans notre PILE.\n", n,ptr2,ptr2);
	}
	else { printf("\nValeur %d n'existe pas dans notre liste.\n", n);	}
	free(ptr2);


////////////////////////////////////////////////////////////////////////////////////////////////////

	printf("\n\nVoici un exemple de la structure de donnee 'FILE'.\n");

	struct file* head_file = NULL;
	struct file* tail_file = NULL;

	head_file = enfiler_val(head_file,&tail_file, 90);
	head_file = enfiler_val(head_file,&tail_file, 80);
	head_file = enfiler_val(head_file,&tail_file, 70);

	enfiler_ref(&head_file,&tail_file, 60);
	enfiler_ref(&head_file,&tail_file, 50);
	enfiler_ref(&head_file,&tail_file, 40);

	printf("\t\t I N F O\n");
		printf("\n\t\t\tPremier element dans la structure: valeur: %d\tAddress: %x <=> %p", tail_file->data, tail_file, tail_file);
		printf("\n\t\t\tDerniere element dans la structure: valeur: %d\tAddress: %x <=> %p\n", head_file->data, head_file, head_file);
	affichier_file(tail_file);

	printf("\n\n\t D E F I L E R\n");

	printf("\n\t\tPassage par valeur: ");
		tail_file = defiler_val(tail_file);
		affichier_file(tail_file);

	printf("\n\t\tPassage par referrence: ");
		defiler_ref(&tail_file);
		affichier_file(tail_file);

	printf("\nQuel valeur cherchez-vous? => ");
	scanf("%d", &n);
	file* ptr3 = chercher_file(head_file,tail_file,n);
	if ( ptr3 != NULL )
	{
		printf("\nla valeur %d est enregistrée a l'address %x <=> %p dans notre FILE.\n", n,ptr3,ptr3);
	}
	else { printf("\nValeur %d n'existe pas dans notre liste.\n", n);	}
	free(ptr3);

////////////////////////////////////////////////////////////////////////////////////////////////////

	printf("\n\n\n\t\t\tMEMORY PANIC!");
	printf("\n\n\n\t\t\tMEMORY PANIC!");

	freeMemory_file(&head_file);
	affichier_file(&head_file);
	puts("\n\t\tStage 1\n");

	freeMemory_pile(&head_pile);
	affichier_pile(&head_pile);
	puts("\n\t\tStage 2\n");

	freeMemory_crl(&head_crl);
	affichier_liste_crl_direct(&head_crl);
	puts("\n\t\tStage 3\n");
	
	freeMemory_dbl(&head_dbl);
	affichier_dbl_direct(&head_dbl);
	puts("\n\t\tStage 4\n");
	
	freeMemory(head);
	affichier(&head);
	puts("\n\t\tStage 5\n");



	return 0;
}