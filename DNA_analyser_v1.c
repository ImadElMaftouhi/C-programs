#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct node{
    char base;
    struct node* next;
    struct node* prev;
}node;
node* head = NULL;
node* tail = NULL;


void memory_message(){
    printf("Memory allocation failed");
    exit(0);
}

int find_total_length(char *str){

    int i=0;
    char checker = str[0];
    
    while ( checker != '\0'){
        i++; 
        checker = str[i];
    }
  
    return i;
}

node* add_at_end(node* ptr, char b){
    node* temp = malloc(sizeof(node));
    
    if ( temp == NULL){
        memory_message();
    }
    
    temp->base = b;
    temp->next = NULL;
    
    if ( head == NULL){
        temp->prev = NULL;
        head = temp;

    } else {
        temp->prev = ptr;
        ptr->next = temp;

    }
 
    return temp;    
}

node* add_at_start(node* head){
    node* temp = malloc (sizeof(node));

    temp->prev = NULL;
    temp->next = head;
    head->prev = temp;
    head = temp;

    return temp;
}

void add_sequence(){

    printf("\nAjouter votre séquence --> ");
    char *seq;
    scanf(" %[^\n]", seq);

    if ( seq == NULL )
    {
        printf("\nError de memoire! Ressayer.");
        return add_sequence();
    }
    
    char checker = seq[0]; int i=0;

    seq = strupr(seq);

    while (checker != '\0'){
        if  ( checker != 'A' && checker != 'a' && checker != 'T' && checker != 't' && checker != 'C' && checker != 'c' && checker != 'G' && checker != 'g' )
        {
            printf("\nError, verifiée les bases de votre séquence. "); 
            // free(seq);
            return add_sequence();
        }
        i++;
        checker = seq[i];
    }

    int n = find_total_length(seq);

    for ( i = 0 ; i < n ; i++){
        //printf("%c -> ", *(seq+i) );
        tail = add_at_end(tail, *(seq+i) );
    }

    // free(seq);
}

void find_seq(){
    char* seq;
    int i = 1;
    int ordre = 2;
    printf("\nEntrez la séquence que vous chercher --> ");
    scanf(" %[^\n]", seq);

    int n = find_total_length(seq);
    seq = strupr(seq);
    node* ptr1 = head;
    node* ptr2 = NULL;

    if ( ptr1 == NULL){
        printf("\nAucune séquence n'est encore inserer");
        return find_seq();
    }

    while ( ptr1 != NULL){
        if ( ptr1->base == *seq  )  // *seq ~ seq[0]
        {
            ordre++;
            ptr2 = ptr1->next;
            while ( ptr2 != NULL){
                while ( ptr2->base == *( seq + i ) ) {
                i++;
            }
            ptr2 = ptr2->next;
            }
        }
    ptr1 = ptr1->next;    
    }

    if ( i == n){
        printf("\nLa séquence existe dans l'ADN a l'ordre %d", ordre);
    } else {
        printf("\nLa séquence ne se trouve pas dans l'ADN");
    }

    // free(seq); // why doesn't this work ?????
}

void comparer(){
    char* seq = NULL;
    char* adn;
    int i = 0;
    printf("\nADN de nouveau patient --> ");
    scanf(" %[^\n]", adn);
    
    printf("\ntesting %s ", adn);

    adn = strupr(adn); //necesaire pour la comparison,
    node* ptr = head;

    while ( ptr != NULL ){
        if ( ptr->base == *(adn + i) ){
            i++; 
        }
    ptr = ptr->next;
    }

    if ( i == (find_total_length(adn) ) ){
        printf("\nLes deux brins sont egaux ");
    } else {
        printf("\nLes deux brins d'ADN sont differentes!");
    }

    // free(seq);

}

void print_debut(){
    node* ptr = head;

    printf("\nVotre séquence d'ADN dans l'ordre normale: ");
    while ( ptr != NULL){
        printf("%c->", ptr->base);
        ptr = ptr->next;
    }
    
    // free(ptr);
}

void print_fin(){
    node* ptr = tail;
    printf("\nVotre séquence d'ADN dans l'ordre inverse : ");
     while (ptr != NULL) {
        printf("%c->", ptr->base);
        ptr = ptr->prev;
    }

    // free(ptr);
}

int menu(){
    printf("\n---------------------------------------------------"
            "\nVoici le menu des operations possible."
            "\n1. Inserer une nouvelle séquence d'ADN"
            "\n2. Rechercher une séquence spécifique dans la structure de l'ADN."
            "\n3. Afficher l'ensemble de l'ADN stocké dans la structure."
            "\n4. Comparer deux ADN pour deux patients différents."
            "\n--------------------------------------------------"
            "\nVotre choix --> ");
    int c; 
    scanf("%d", &c);
    return c;
}


int main(){
    // tail = add_at_end(tail);

    int choix = menu();
    switch (choix){
        case 1:
            add_sequence();
            return main();
        case 2:
            find_seq();
            return main();
        case 3:
            print_debut();
            return main();
        case 4:
            comparer();
            return main();
        default:
        printf("Choix non valide!");
        return main();
    }



//free memory
node* p = head;
while (p != NULL) {
node* temp = p;
p = p->next;
free(temp);
}
return 0;
}