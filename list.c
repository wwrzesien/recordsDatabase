#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "structures.h"
#include "function.h"
#include "list.h"
#include "shell.h"

// Funkcja czyszczaca buffer
void clearInputBuffer(){
    char c;
    do{
        c = getchar();
    } while (c != '\n' && c != EOF);
}
// Funkcja zwracajaca wskaznik na katalog
Catalog **findCatalog(struct HandlerC *headC, char *name){
    Catalog **temp = &(headC->beg);
    while((*temp) != NULL){
        if(strcmp((*temp)->nameCat, name) == 0){
            return temp;
        }
        temp = &((*temp)->next);
    }
    return NULL;
}
// Funkcja zwracajaca wskaznik na plyte
Record **findRecord(struct HandlerR *headR, char *number){
    Record **temp = &(headR->beg);
    while((*temp) != NULL){
        if(strcmp((*temp)->number, number) == 0){
            return temp;
        }
        temp = &((*temp)->next);
    }
    return NULL;
}
// Funkcja zwracajca wskaznik na katalog w liscie katalogow plyty
catList **findCatInRec(struct HandlerR *headR, char *number, char *nameCat){
    Record *el = *(findRecord(headR, number));
    catList **temp = &(el->cList->beg);
    while((*temp) != NULL){
        if(strcmp( ((*temp)->cat)->nameCat, nameCat ) == 0){
            return temp;
        }
        temp = &((*temp)->next);
    }
    return NULL;
}
// Sortowanie bez uwzglednienia wielkosci znakow
int sortWOCase(char const *a, char const *b){
    for(;; a++, b++){
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if(d != 0 || !*a)
            return d;
    }
}
// Funkcja sortujaca
void sortRecord(struct HandlerC *headC, char *name){
     recList *list = (*findCatalog(headC, name))->rList->beg;
     recList *temp = NULL;
     recList *help = NULL;
     struct Record *s = malloc(sizeof(Record));
    // Sortowanie wedlug nazwy plyty
    for( temp = list; temp != NULL; temp = temp->next){
        for( help = temp; help != NULL; help = help->next){
            if(sortWOCase(help->rec->nameRec, temp->rec->nameRec) < 0){
                return;
                /*strcpy(s->nameRec, help->rec->nameRec);
                strcpy(s->type, help->rec->type);
                strcpy(s->number, help->rec->number);

                strcpy(help->rec->nameRec, temp->rec->nameRec);
                strcpy(help->rec->type, temp->rec->type);
                strcpy(help->rec->number, temp->rec->number);

                strcpy(temp->rec->nameRec, s->nameRec);
                strcpy(temp->rec->type, s->type);
                strcpy(temp->rec->number, s->number);*/


                /*strcpy( help->rec->nameRec, temp->rec->nameRec );
                strcpy( temp->rec->nameRec, s);*/
            }
        }
    }
    free(s);
}
// Funkcja dodajaca plyte
void addRecord(struct Record *temp, struct HandlerR *headR){
    struct Record *el = malloc(sizeof(struct Record));
    struct HandlerCL *headCL = malloc(sizeof(struct HandlerCL));

    // Jezeli lista pusta
    if(headR->beg == NULL){
        headR->beg = el;
        headR->end = el;
        el->next = NULL;
        el->cList = headCL;
        (el->cList)->beg = NULL;
        (el->cList)->end = NULL;
        strcpy(el->nameRec, temp->nameRec);
        strcpy(el->type, temp->type);
        strcpy(el->number, temp->number);
    }
    else{
        el->next = NULL;
        strcpy(el->nameRec, temp->nameRec);
        strcpy(el->type, temp->type);
        strcpy(el->number, temp->number);
        headR->end->next = el;
        headR->end = el;
        el->cList = headCL;
        (el->cList)->beg = NULL;
        (el->cList)->end = NULL;
    }
}
// Funkcja dodajaca plyte do listy plyt katalogu
void addRecToCat(char *catalog, struct HandlerC *headC, struct HandlerR *headR, char *number){
    Record *el = (*findRecord(headR, number));
    recList *list = malloc(sizeof(struct recList));
    struct HandlerRL *headRL = (*findCatalog(headC, catalog))->rList;
    struct recList *temp = headRL->beg;

    // Sprawdzenie czy istnieje katalog
    if( findCatalog(headC, catalog) == NULL ){
        puts("addRecToCat: Nie ma takiego katalogu.");
    }

    if(strcmp(catalog, "brak") == 0){
        return;
    }

    // Przypisanie 1 plyty
    if( headRL->beg == NULL ){
        headRL->beg = list;
        headRL->end = list;
        list->rec = el;
        list->next = NULL;
    }
    else{

        headRL->end->next = list;
        headRL->end = list;
        list->next = NULL;
        list->rec = el;
    }
}
// Funkcja dodajaca katalog do listy katalogow plyty
void addCatToRec(char *catalog, struct HandlerC *headC, struct HandlerR *headR, char *number){
    Catalog *el = (*findCatalog(headC, catalog));
    catList *list = malloc(sizeof(struct catList));
    struct HandlerCL *headCL = (*findRecord(headR, number))->cList;
    // Czy istnieje element
    if(headR->end == NULL){
        puts("addCatRec: Brak plyty do przypisania.");
        return;
    }

    if(strcmp(catalog, "brak") == 0){
        return;
    }

    // Przypisanie 1 katalogu
    if( headCL->beg == NULL ){
        headCL->beg = list;
        headCL->end = list;
        list->cat = el;
        list->next = NULL;
    }
    else{
        headCL->end->next = list;
        headCL->end = list;
        list->next = NULL;
        list->cat = el;
    }
}
// Funkcja dodajaca katalog
void addCatalog(struct HandlerC *headC, char *name){
    struct Catalog *el = malloc(sizeof(struct Catalog));
    struct HandlerRL *headRL = malloc(sizeof(struct HandlerRL));

    if( strcmp(name, "brak") == 0){
        return;
    }
    // Jesli lista pusta
    if(headC->beg == NULL){
        headC->beg = el;
        headC->end = el;
        el->next = NULL;
        strcpy(el->nameCat, name);
        el->rList = headRL;
        (el->rList)->beg = NULL;
        (el->rList)->end = NULL;
    }
    else{
        el->next = NULL;
        strcpy(el->nameCat, name);
        headC->end->next = el;
        headC->end = el;
        el->rList = headRL;
        (el->rList)->beg = NULL;
        (el->rList)->end = NULL;
    }
}
// Funkcja usuwajaca katalog z listy katalogow plyty
void remCatFromRec(struct HandlerR *headR, char *number, char *nameCat){
    struct HandlerCL *headCL = (*findRecord(headR, number))->cList;
    catList *temp = headCL->beg;
    catList *el;

    if( headR->beg == NULL ){
        puts("remCatFromRec: Lista plyt jest pusta.");
        return;
    }
    // Jesli element jest na 1 miejscu
    if( strcmp(temp->cat->nameCat, nameCat) == 0){
        el = headCL->beg;
        headCL->beg = temp->next;
        temp->next = NULL;
        free(temp);
    }
    else{
        while( strcmp( (temp->next)->cat->nameCat, nameCat) !=0 ){
            temp = temp->next;
        }
        el = temp->next;
        if(el->next != NULL){
            temp->next = temp->next->next;
            el->next = NULL;
            free(el);
        }
        // Usuwamy ostatni element
        else{
            temp->next = temp->next->next;
            headCL->end = temp;
            free(el);
        }
    }
}
// Funkcja usuwajaca plyte z listy plyt katalogu
void remRecFromCat(struct HandlerC *headC, char *number, char *nameCat){
    struct HandlerRL *headRL = (*findCatalog(headC, nameCat))->rList;
    recList *temp = headRL->beg;
    recList *el;

    if( headC->beg == NULL ){
        puts("remCatFromRec: Lista katalogow jest pusta.");
        return;
    }
    // Jesli element jest na 1 miejscu
    if( strcmp(temp->rec->number, number) == 0){
        el = headRL->beg;
        headRL->beg = temp->next;
        temp->next = NULL;
        free(temp);
    }
    else{
        while( strcmp( (temp->next)->rec->number, number) !=0 ){
            temp = temp->next;
        }
        el = temp->next;
        if(el->next != NULL){
            temp->next = temp->next->next;
            el->next = NULL;
            free(el);
        }
        // Usuwamy ostatni element
        else{
            temp->next = temp->next->next;
            headRL->end = temp;
            free(el);
        }
    }
}
// Funkcja usuwajaca katalog
void remCatalog(struct HandlerC *headC, char *name){
    Catalog *temp = headC->beg;
    Catalog *elem; // Wskaznik na element do usuniecia
    struct HandlerRL *headRL = (*findCatalog(headC, name))->rList;
    struct HandlerRL *temp2 = headRL;

    // Usuniecie listy plyt danego katalogu
    while( headRL->beg != NULL ){
        temp2->beg = headRL->beg;
        headRL->beg = headRL->beg->next;
        free(temp2->beg);
    }
    headRL->end = NULL;

    // Jesli element jest 1 na liscie
    if( strcmp(temp->nameCat, name) == 0 ){
        elem = temp;
        headC->beg = temp->next;
        temp->next = NULL;
        free(elem);
    }
    else{
        while( strcmp( (temp->next)->nameCat, name) != 0){
            temp = temp->next;
        }
        elem = temp->next;
        if( elem->next != NULL ){
            temp->next = (temp->next)->next;
            elem->next = NULL;
            free(elem);
        }
        // Usuwamy ostatni element
        else{
            temp->next = (temp->next)->next;
            headC->end = temp;
            free(elem);
        }
    }
}
// Funkcja usuwajaca plyte
void remRecord(struct HandlerR *headR, char *number){
    Record *temp = headR->beg;
    Record *elem; // Wskaznik na element do usuniecia
    struct HandlerCL *headCL = (*findRecord(headR, number))->cList;
    struct HandlerCL *temp2 = headCL;

    // Usuniecie listy plyt danego katalogu
    while( headCL->beg != NULL ){
        temp2->beg = headCL->beg;
        headCL->beg = headCL->beg->next;
        free(temp2->beg);
    }
    headCL->end = NULL;

    // Jesli element jest 1 na liscie
    if( strcmp(temp->number, number) == 0 ){
        elem = temp;
        headR->beg = temp->next;
        temp->next = NULL;
        free(elem);
    }
    else{
        while( strcmp( (temp->next)->number, number) != 0){
            temp = temp->next;
        }
        elem = temp->next;
        if( elem->next != NULL ){
            temp->next = (temp->next)->next;
            elem->next = NULL;
            free(elem);
        }
        // Usuwamy ostatni element
        else{
            temp->next = (temp->next)->next;
            headR->end = temp;
            free(elem);
        }
    }
}
// Funkcja sprawdzajaca poprawnosc typu nosnika
int isCorrectType( char *type, char **tab ){
    for(int i=0;i<4;i++){
        if(strcmp(type, tab[i]) == 0)
            return 0;
    }
    return 1;
}
// Funkcja sprawdzajaca poprawnosc numeru
int isCorrectNumber(struct HandlerR *headR, char *number){
    int i=0;
    while( number[i] != '\0'){
        i++;
    }
    if(i != 5){
        return 1;
    }
    // 3 pierwsze znaki - cyfry
    if(isdigit(number[0]) == 0 || isdigit(number[1]) == 0 || isdigit(number[2]) == 0){
        return 1;
    }

    // 2 ost znaki - duze, rozne litery
    if(isupper(number[3]) == 0 || isupper(number[4]) == 0 || number[3] == number[4] ){
        return 1;
    }
    // spr czy nie istnieje juz taki sam numer
    Record *temp = headR->beg;
    while( temp ){
        if(strcmp(number, temp->number) == 0){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
// Funkcja usuwajaca wszytskie katalogi
void delAllCatalogs(struct HandlerC *headC, struct HandlerR *headR){
    struct HandlerC *temp;
    while(headC->beg != NULL){
        //temp->beg = headC->beg;
        //headC->beg = headC->beg->next;
        if( headC->beg->rList->beg != NULL ){
            // Usuniecie katalogu z listy katalogow plyt
            struct recList *temp2 = headC->beg->rList->beg;
            while(temp2){
                remCatFromRec(headR, temp2->rec->number, headC->beg->nameCat);
                temp2 = temp2->next;
            }
        }
        remCatalog(headC, headC->beg->nameCat);
        //free(temp->beg);
    }
    headC->end = NULL;
}
// Funkcja usuwajaca wszystkie plyty
void delAllRecords(struct HandlerC *headC, struct HandlerR *headR){
    while(headR->beg != NULL){
        if( headR->beg->cList->beg != NULL ){
            // Usuniecie plyty z listy plyt katalogow
            struct catList *temp2 = headR->beg->cList->beg;
            while(temp2){
                remRecFromCat(headC, headR->beg->number, temp2->cat->nameCat);
                temp2 = temp2->next;
            }
        }
        remRecord(headR, headR->beg->number);
    }
    headR->end = NULL;
}
// Funkcja zapis katalog.txt
void saveKatalog(struct HandlerC *headC, FILE *file){
    if(headC->beg != NULL){
        int i = 1;
        struct Catalog* temp = headC->beg;
        while(temp){
            fprintf(file, "\n");
            fprintf(file,"%s\r\n", temp->nameCat);
            temp = temp->next;
            i++;
        }
    }
}
// Funkcja zapis pozycje.txt
void savePozycje(struct HandlerR *headR, FILE *file){
    Record *temp = headR->beg;
    while(temp){
        fprintf(file,"%s\r\n", temp->nameRec);
        fprintf(file,"%s\r\n", temp->type);
        fprintf(file,"%s\r\n", temp->number);
        fprintf(file,"\r\n");
        temp = temp->next;
    }
}
// Funkcja zapis baza.txt
void saveBaza(struct HandlerR *headR, FILE *file){
    Record *temp = headR->beg;
    catList *listC;
    while(temp){
        listC = temp->cList->beg;
        fprintf(file,"%s\r\n", temp->nameRec);
        fprintf(file,"%s\r\n", temp->type);
        fprintf(file,"%s\r\n", temp->number);
        if(listC != NULL){
            while(listC){
                fprintf(file,"%s", listC->cat->nameCat);
                if(listC->next != NULL){
                    fprintf(file,",");
                }
                listC = listC->next;
            }
        }
        else{
            fprintf(file, "brak");
        }
        fprintf(file,"\r\n");
        fprintf(file,"\r\n");
        temp = temp->next;
    }
}
// Funkcja load katalog.txt
void loadKatalog(struct HandlerC *headC, FILE *file){
    char line[10];
    fscanf(file, "%s", line);
    if(findCatalog(headC, line) == NULL){
        addCatalog(headC, line);
    }
}
// Funkcja load pozycje.txt
void loadPozycje(struct HandlerR *headR, struct Record *temp, char **typeCorrect, FILE *file){
    int k = 0;
    char line[10];
    // Nazwa
    fscanf(file,"%s", line);
    strcpy( temp->nameRec, line );
    k++;
    // Rodzaj nosnika
    fscanf(file,"%s", line);
    if( isCorrectType(line, typeCorrect ) == 0 ){
        strcpy( temp->type, line );
        k++;
    }
    // Numer
    fscanf(file,"%s", line);
    if( isCorrectNumber(headR, line ) == 0 ){
        strcpy( temp->number, line );
        k++;
    }
    if( findRecord(headR, temp->number) == NULL && k == 3){
        addRecord(temp, headR);
    }
}
// Funkcja load baza.txt
void loadBaza(struct HandlerR *headR, struct HandlerC *headC, char **typeCorrect, FILE *file, struct Record *temp){
    // Tablica pomocnicza na katalogi
        char **catalogs;
        char line[100];
        int i = 0;

        // Odczyt
        while( !feof(file) ){
            //  Wczytanie plyty bez katalogow
            loadPozycje(headR, temp, typeCorrect, file);

            i = 0;
            // Wczytanie katalogow
            fscanf(file, "%s", line);
            catalogs = splitLine(line); // Rozdzielenie katalogow

            while(catalogs[i] != NULL){
                if(strcmp(catalogs[i], "brak") != 0){
                    // Sprawdzenie czy istnieje taki katalog
                    if( findCatalog(headC, catalogs[i]) != NULL ){
                        // Sprawdzenie czy plyta juz nalezy do tego katalogu
                        if( findCatInRec(headR, temp->number, catalogs[i]) == NULL ){
                            // Dodanie katalogu listy (plyty)
                            addCatToRec(catalogs[i], headC, headR, temp->number);
                            // Dodanie plyty do listy (katalogu)
                            addRecToCat(catalogs[i], headC, headR, temp->number);
                        }
                    }
                    else{
                        addCatalog(headC, catalogs[i]);
                        // Dodanie katalogu listy (plyty)
                        addCatToRec(catalogs[i], headC, headR, temp->number);
                        // Dodanie plyty do listy (katalogu)
                        addRecToCat(catalogs[i], headC, headR, temp->number);
                    }
                }
                 i++;
            }
        }
}

























