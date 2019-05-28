#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "structures.h"
#include "function.h"
#include "shell.h"
#include "list.h"

// Funkcja zwracaja liczbe argumentow
int numArgs(char **args){
    int n = 0; // Liczba argumentów
    while(args[n] != NULL){
        n++;
    }
    return n;
}
// Dodawanie katalogu
void addCatFunc(char **args, struct HandlerC *headC){
    char name[10];
    printf("Nazwa: %s\n", args[1]);
    // Sprawdzenie czy juz istnieje
    if(findCatalog(headC, args[1]) != NULL){
        puts("addCatFunc: Podany katalog już istnieje.");
    }
    else{
        addCatalog(headC, args[1]);
        puts("Dodano katalog.");
    }
}
// Usuniecie katalogu
void remCatFunc(char **args, struct HandlerC *headC, struct HandlerR *headR){
    if( findCatalog(headC, args[1]) != NULL){ // Sprawdzenie czy istnieje katalog
        // Usuniecie katalogu
        if( (*findCatalog(headC, args[1]))->rList->beg != NULL ){
            // Usuniecie katalogu z listy katalogow plyt
            struct recList *temp = (*findCatalog(headC, args[1]))->rList->beg;
            while(temp){
                remCatFromRec(headR, temp->rec->number, args[1]);
                temp = temp->next;
            }
        }
        remCatalog(headC, args[1]);
        puts("Usunieto katalog.");
    }
    else{
        puts("remCatFunc: Nie ma takiego katalogu.");
    }
}
// Zmiana nazwy katalogu
void modCatFunc(char **args, struct HandlerC *headC){
    char name[10];
    if(findCatalog(headC, args[1]) != NULL){
        printf("Stara nazwa: %s\n", (*findCatalog(headC, args[1]))->nameCat );
        strcpy( (*findCatalog(headC, args[1]))->nameCat, "\0\0" );
        printf("Nowa nazwa: "); scanf("%s", name);
        clearInputBuffer();

        // Sprawdzenie czy nowa nazwa juz istnieje
        if(findCatalog(headC, name) == NULL){
         strcpy( (*findCatalog(headC, "\0\0"))->nameCat, name );
         puts("Zmodyfikowano katalog.");
        }
        else{
            puts("modCatFunc: Podany katalog już istnieje.");
        }
    }
    else{
        puts("modCatFunc: Nie ma takiego katalogu.");
    }
}
// Wyświetlenie zawartosci/listy katalogów
void showCatFunc(char **args, struct HandlerC *headC){
    // Wyswietlenie listy katalogó
    if(strcmp(args[0], "show-c-all") == 0){
        if(headC->beg != NULL){
            int i = 1;
            struct Catalog* temp = headC->beg;
            while(temp){
                printf("%d. %s\n", i, temp->nameCat);
                temp = temp->next;
                i++;
            }
        }
        else{
            puts("showCatFunc: Lista katalogów jest pusta.");
        }
    }
    // Wyswietlenie zawartości katalogu
    else{
        if(findCatalog(headC, args[1]) != NULL){
            if((*findCatalog(headC, args[1]))->rList->beg != NULL){
                //sortRecord(headC, args[1]);
                struct recList *listR = (*findCatalog(headC, args[1]))->rList->beg;
                int i = 1;
                while(listR){
                    printf("Nr.%d\n", i);
                    printf("Nazwa: %s\n", listR->rec->nameRec);
                    printf("Rodzaj nośnika: %s\n", listR->rec->type);
                    printf("Numer: %s\n", listR->rec->number);
                    listR = listR->next;
                    i++;
                }
            }
            else{
                puts("showCatFunc: Katalog jest pusty.");
            }
        }
        else{
            puts("showCatFunc: Nie ma takiego katalogu.");
        }
    }
}
// Wyswietlenie wszytskich płyt
void showRecFunc(char **args, struct HandlerR *headR){
    if(headR->beg == NULL){
        puts("showRecFunc: Lista plyt jest pusta.");
        return;
    }
    Record *temp = headR->beg;
    catList *listC;
    int i = 1;
    while(temp){
        listC = temp->cList->beg;
        printf("Nr.%d\n", i);
        printf("Nazwa: %s\n", temp->nameRec);
        printf("Rodzaj nosnika: %s\n", temp->type);
        printf("Numer: %s\n", temp->number);
        printf("Katalog: ");
        while(listC){
            printf("%s ", listC->cat->nameCat);
            listC = listC->next;
        }
        printf("\n");
        temp = temp->next;
        i++;
    }
}
// Dodanie płyty
void addRecFunc(char **args, char **typeCorrect, struct HandlerR *headR, struct HandlerC *headC){
    char catalog[10];
    char s[1];
    char s2[1];
    Record *temp = malloc(sizeof(Record));
    // Nazwa
    printf("Nazwa: %s\n", args[1]);
    strcpy(temp->nameRec, args[1]);
    // Rodzaj nosnika
    printf("Rodzaj nośnika: "); scanf("%s", temp->type);
    while( isCorrectType(temp->type, typeCorrect) != 0 ){
        puts("addRecFunc: Niepoprawny rodzaj nosnika.");
        printf("Rodzaj nośnika: "); scanf("%s", temp->type);
        clearInputBuffer();
    }
    // Numer
    printf("Numer: "); scanf("%s" ,temp->number);
    while( isCorrectNumber(headR, temp->number) != 0 ){
        puts("addRecFunc: Nieprawidlowy numer katalogowy.");
        printf("Numer: "); scanf("%s" ,temp->number);
        clearInputBuffer();
    }
    // Dodawanie plyty
    addRecord(temp, headR);
    // Katalog
    do{
        printf("Przypisac plyte do katalogu? (y/n): ");
        scanf("%s", s);
        clearInputBuffer();
    }while( strcmp(s, "y") != 0 && strcmp(s, "n") != 0 );

    if( strcmp(s, "y") == 0 ){
        if( headC->beg != NULL ){
            do{
                printf("Katalog: "); scanf("%s", catalog);
                clearInputBuffer();
                // Sprawdzenie czy istnieje taki katalog
                if( findCatalog(headC, catalog) != NULL ){
                    // Sprawdzenie czy plyta juz nalezy do tego katalogu
                    if( findCatInRec(headR, temp->number, catalog) == NULL ){
                        // Dodanie katalogu listy (plyty)
                        addCatToRec(catalog, headC, headR, temp->number);
                        // Dodanie plyty do listy (katalogu)
                        addRecToCat(catalog, headC, headR, temp->number);
                    }
                    else{
                        puts("findCatInRec: Plyta juz nalezy do tego katalogu.");
                    }
                }
                else{
                    puts("addRecFunc: Nie ma takiego katalogu.");
                }
                if( 0 == 0 ){
                    printf("Czy chcesz wprowadzic katalog? (y/n)"); scanf("%s", s2);
                    clearInputBuffer();
                }
                else{
                    break;
                }
            }while( strcmp(s2, "y") == 0 );
        }
        else{
            puts("addRecFunc: Lista katalogow jest pusta.");
            strcpy(catalog, "brak");
        }
    }
    else if( strcmp(s, "n") == 0 ){
        strcpy(catalog, "brak");
    }
    free(temp);
    puts("Dodano plyte.");
}
// Dodanie plyty do katalogu
void addRecToCatFunc(char **args, struct HandlerR *headR, struct HandlerC *headC){
    if( headR->beg == NULL ){
        puts("addRecToCatFunc: Lista plyt jest pusta.");
        return;
    }
    if( headC->beg == NULL ){
        puts("addRecToCatFunc: Lista katalogow jest pusta.");
        return;
    }
    if( findRecord(headR, args[1]) != NULL ){
        char cat[10];
        char s[2];

        // Informacje o plycie
        Record *temp = (*findRecord(headR, args[1]));
        catList *listC = temp->cList->beg;
        // Wyswietlenie starej plyty
        printf("Plyta: \n");
        printf("Nazwa: %s\n", temp->nameRec);
        printf("Rodzaj nosnika: %s\n", temp->type);
        printf("Numer: %s\n", temp->number);
        printf("Katalog: ");
        while(listC){
            printf("%s ", listC->cat->nameCat);
            listC = listC->next;
        }
        printf("\n");

        do{
            printf("Podaj katalog: "); scanf("%s", cat);
            clearInputBuffer();
            if( findCatalog(headC, cat) == NULL ){
                puts("addRecToFunc: Nie ma takiego katalogu.");
                do{
                    printf("Kontynuowac dodawanie? (y/n) "); scanf("%s", s);
                    clearInputBuffer();
                }while( strcmp(s, "y") != 0 && strcmp(s, "n") != 0 );
                if( strcmp(s, "n") == 0)
                    return;
            }
            else{
                strcpy(s, "n");
            }
        }while( strcmp( s, "y") == 0);
        if( findCatInRec(headR, args[1], cat) == NULL ){
            // DOdanie plyty do listy plyt katalogu
            addRecToCat(cat, headC, headR, args[1]);
            // Dodanie katalog do listy katalogow plyty
            addCatToRec(cat, headC, headR, args[1]);
            puts("Dodano plyte do katalogu.");
        }
        else{
            puts("addRecToCatFunc: Plyta juz nalezy do katalogu.");
        }
    }
    else{
        puts("addRecToCatFunc: Nie ma takiej plyty.");
        return;
    }
}
// Modyfikacja płyty ( zmiana nazwy, typu, numeru )
void modRecFunc(char **args, struct HandlerR *headR, char **typeCorrect){
    if( headR->beg == NULL ){
        puts("modRecFunc: Lista plyt jest pusta.");
        return;
    }
    if( findRecord(headR, args[1]) == NULL){
        puts("modRecFunc: Nie ma takiej plyty.");
        return;
    }

    Record *temp = (*findRecord(headR, args[1]));
    // Wyswietlenie starej plyty
    printf("Plyta: \n");
    printf("Nazwa: %s\n", temp->nameRec);
    printf("Rodzaj nosnika: %s\n", temp->type);
    printf("Numer: %s\n", temp->number);

    int status = 1;
    char choice[10];
    char s[1];
    char number[6];

    puts("Modyfikacja: tytul -> title, rodzaj nosnika -> type, nr kat. -> number");

    do{
        printf("Modyfikakcja: "); scanf("%s", choice);
        clearInputBuffer();
        // Nazwa
        if( strcmp( choice, "title") == 0 ){
            printf("Nazwa: "); scanf("%s", temp->nameRec);
            clearInputBuffer();
        }
        // Rodzaj nosnika
        else if( strcmp( choice, "type") == 0 ){
            printf("Rodzaj nośnika: "); scanf("%s", temp->type);
            clearInputBuffer();
            while( isCorrectType(temp->type, typeCorrect) != 0 ){
                puts("modRecFunc: Niepoprawny rodzaj nosnika.");
                printf("Rodzaj nośnika: "); scanf("%s", temp->type);
                clearInputBuffer();
            }
        }
        // Numer
        else if( strcmp( choice, "number") == 0 ){
            printf("Numer: "); scanf("%s" , number);
            clearInputBuffer();
            strcpy( temp->number, "\0\0" );
            while( isCorrectNumber(headR, number) != 0 ){
                puts("addRecFunc: Nieprawidlowy numer katalogowy.");
                printf("Numer: "); scanf("%s" ,number);
                clearInputBuffer();
            }
            strcpy( temp->number, number);
        }
        else {
            puts("modRecFunc: Nie ma takiej opcji.");
        }

        do{
            printf("Zakonczyc modyfikacje? (y/n): ");
            scanf("%s", s);
            clearInputBuffer();
        }while( strcmp(s, "y") != 0 && strcmp(s, "n") != 0 );
        if( strcmp(s, "y") == 0)
            status = 0;
        else
            status = 1;
    }while(status);
    puts("Modyfikacja zakonczona.");
}
// Wyszukiwanie płyty
void srchRecFunc(char **args, struct HandlerR *headR){
    if(headR->beg == NULL ){
        puts("printRecord: Lista plyt jest pusta.");
        return;
    }
    Record *temp = headR->beg;
    catList *listC;
    int i = 1;
    int n = 0;

    char var[10];
    printf("Kryterium wyszukiwania: %s\n", args[1]);

    if( strcmp(args[1], "title" ) == 0 ){
        printf("Podaj tytul: "); scanf("%s", var);
        clearInputBuffer();
        n = 0;
        while(temp){
            listC = temp->cList->beg;
            if(strcmp( temp->nameRec, var) == 0){
                printf("Nr.%d\n", i);
                printf("Nazwa: %s\n", temp->nameRec);
                printf("Rodzaj nosnika: %s\n", temp->type);
                printf("Numer: %s\n", temp->number);
                printf("Katalog: ");
                while(listC){
                    printf("%s ", listC->cat->nameCat);
                    listC = listC->next;
                }
                printf("\n");
                n++;
                i++;
            }
            temp = temp->next;
        }
        if( n == 0)
            puts("srchRecFunc: Nie ma takiej nazwy.");
    }
    else if( strcmp( args[1], "type" ) == 0 ){
        printf("Podaj rodzaj nosnika: "); scanf("%s", var);
        clearInputBuffer();
        n = 0;
        while(temp){
            listC = temp->cList->beg;
            if(strcmp( temp->type, var) == 0){
                printf("Nr.%d\n", i);
                printf("Nazwa: %s\n", temp->nameRec);
                printf("Rodzaj nosnika: %s\n", temp->type);
                printf("Numer: %s\n", temp->number);
                printf("Katalog: ");
                while(listC){
                    printf("%s ", listC->cat->nameCat);
                    listC = listC->next;
                }
                printf("\n");
                n++;
            }
            temp = temp->next;
            i++;
        }
        if( n == 0)
            puts("srchRecFunc: Nie ma takiego rodzaju.");
    }
    else if( strcmp( args[1], "number" ) == 0 ){
        printf("Podaj numer katalogowy: "); scanf("%s", var);
        clearInputBuffer();
        n = 0;
        while(temp){
            listC = temp->cList->beg;
            if(strcmp( temp->number, var) == 0){
                printf("Nr.%d\n", i);
                printf("Nazwa: %s\n", temp->nameRec);
                printf("Rodzaj nosnika: %s\n", temp->type);
                printf("Numer: %s\n", temp->number);
                printf("Katalog: ");
                while(listC){
                    printf("%s ", listC->cat->nameCat);
                    listC = listC->next;
                }
                printf("\n");
                n++;
            }
            temp = temp->next;
            i++;
        }
        if( n == 0)
            puts("srchRecFunc: Nie ma takiego numeru.");
    }
    else{
        puts("srchRecFunc: Nie ma takiego kryterium.");
    }
}
// Przeniesienie płyty
void movRecFunc(char **args, struct HandlerC *headC, struct HandlerR *headR){
    if ( (*findRecord(headR, args[1]))->cList->beg == NULL ){
        puts("movRecFunc: Plyta nie nalezy do zadnego katalogu.");
        return;
    }
    if( findRecord( headR, args[1]) != NULL ){
        Record *temp = (*findRecord(headR, args[1]));
        catList *listC = temp->cList->beg;
        // Wyswietlenie starej plyty
        printf("Plyta: \n");
        printf("Nazwa: %s\n", temp->nameRec);
        printf("Rodzaj nosnika: %s\n", temp->type);
        printf("Numer: %s\n", temp->number);
        printf("Katalog: ");
        while(listC){
            printf("%s ", listC->cat->nameCat);
            listC = listC->next;
        }
        printf("\n");
        char fName[10];
        char tName[10];
        char s[2];
        do{
            printf("Z katalogu: "); scanf("%s", fName);
            clearInputBuffer();
            if( findCatInRec(headR, args[1], fName) == NULL){
                puts("movRecFunc: Plyta nie nalezy do takiego katalogu.");
                printf("Kontynuowac przeniesienie? (y/n) "); scanf("%s", s);
                clearInputBuffer();
                if( strcmp( s, "n") == 0)
                    return;
            }
            else{
                break;
            }
        }while( strcmp( s, "y") == 0);

        do{
            printf("Do katalogu: "); scanf("%s", tName);
            clearInputBuffer();
            if( findCatalog(headC, tName) == NULL ){
                puts("movRecFunc: Nie ma takiego katalogu.");
                printf("Kontynuowac przeniesienie? (y/n) "); scanf("%s", s);
                clearInputBuffer();
                if( strcmp(s, "n") == 0)
                    return;
            }
            else{
                if( findCatInRec(headR, args[1], tName) == NULL ){
                    // Usuniecie katalogu z listy katalogow plyty
                    remCatFromRec(headR, args[1], fName);
                    // Usuniecie plyty z listy plyt katalogu
                    remRecFromCat(headC, args[1], fName);
                    // Dodanie katalogu do listy katalogow plyty
                    addCatToRec(tName, headC, headR, args[1]);
                    // Dodanie plyty do listy plyt katalogu
                    addRecToCat(tName, headC, headR, args[1]);
                }
                else{
                    puts("mocRecFunc: Plyta juz znajduje sie w tym katalogu.");
                    return;
                }
            }
        }while( strcmp(s, "y") == 0);
        puts("Plyta zostala przeniesiona.");
    }
    else{
        puts("movRecFunc: Nie ma takiej plyty.");
        return;
    }
}
// Usuniecie płyty z katalogu/bazy
void remRecFunc(char **args, struct HandlerR *headR, struct HandlerC *headC){
    if( headR == NULL ){
        puts("remRecFunc: Lista plyt jest pusta.");
        return;
    }
    // Sprawdzenie czy plyta istnieje
    if( findRecord(headR, args[1]) != NULL ){
        // Informacje o plycie
        Record *temp = (*findRecord(headR, args[1]));
        catList *listC = temp->cList->beg;
        // Wyswietlenie starej plyty
        printf("Plyta: \n");
        printf("Nazwa: %s\n", temp->nameRec);
        printf("Rodzaj nosnika: %s\n", temp->type);
        printf("Numer: %s\n", temp->number);
        printf("Katalog: ");
        while(listC){
            printf("%s ", listC->cat->nameCat);
            listC = listC->next;
        }
        printf("\n");
        char s[2];

        do{
            printf("Usunac plyte z: (a)bazy, (b)katalogu? "); scanf("%s", s);
            clearInputBuffer();
        }while( strcmp(s, "a") != 0 && strcmp(s, "b") != 0);

        if( strcmp(s, "a") == 0){
            // Usuniecie plyty z list plyt katalogow
            struct catList *tempR = (*findRecord(headR, args[1]))->cList->beg;
            while(tempR){
                remRecFromCat(headC, args[1], tempR->cat->nameCat);
                tempR = tempR->next;
            }
            // Usuniecie plyty
            remRecord(headR, args[1]);
            puts("Usunieto plyte z bazy.");
        }
        else if( strcmp(s, "b") == 0){
            if( (*findRecord(headR, args[1]))->cList->beg == NULL ){
                puts("remRecFunc: Plyta nie nalezy do zadnego katalogu.");
                return;
            }
            char cat[10];
            do{
                printf("Podaj nazwe katalogu: "); scanf("%s", cat);
                clearInputBuffer();
                if( findCatInRec(headR, args[1], cat) == NULL){
                    puts("remRecFunc: Plyta nie nalezy do takiego katalogu.");
                }
                else{
                    break;
                }
            }while(1);
            // Usuniecie plyty z listy plyt katalogu
            remRecFromCat(headC, args[1], cat);
            // Usuniecie katalogu z listy katalogow plyty
            remCatFromRec(headR, args[1], cat);
            puts("Usunieto plyte z katalogu.");
        }
    }
    else{
        puts("remRecFunc: Nie ma takiej plyty.");
        return;
    }
}
// Zapis do pliku
void saveFunc(char **args, struct HandlerR *headR, struct HandlerC *headC){
    if(headR == NULL){
        puts("saveFunc: Lista plyt jest pusta.");
        return;
    }
    if(headC == NULL){
        puts("saveFunc: Lista katalogow jest pusta.");
        return;
    }
    FILE *file;
    // katalog.txt
    if( strcmp( args[1], "katalog.txt" ) == 0 ){
        file = fopen(args[1], "w");
        if( file == NULL ){
            puts("saveFunc: Blad odczytu pliku.");
            return;
        }
        // Zapis
        saveKatalog(headC, file);
    }
    // pozycje.txt
    else if( strcmp( args[1], "pozycje.txt" ) == 0 ){
        file = fopen(args[1], "w");
        if( file == NULL ){
            puts("saveFunc: Blad odczytu pliku.");
            return;
        }
        // Zapis
        savePozycje(headR, file);
    }
    // baza.txt
    else if( strcmp( args[1], "baza.txt" ) == 0 ){
        file = fopen(args[1], "w");
        if( file == NULL ){
            puts("saveFunc: Blad odczytu pliku.");
            return;
        }
        // Zapis
        saveBaza(headR, file);
    }
    else{
        puts("saveFunc: Niepoprana nazwa pliku.");
        return;
    }
    fclose(file);
    puts("Zapisano do pliku.");
}
// Odczyt z pliku
void loadFunc(char **args, struct HandlerR *headR, struct HandlerC *headC, char **typeCorrect){
    Record *temp = malloc(sizeof(Record));

    FILE *file;
    // katalog.txt
    if( strcmp( args[1], "katalog.txt" ) == 0 ){
        file = fopen(args[1], "r");
        if( file == NULL ){
            puts("saveFunc: Blad odczytu pliku.");
            return;
        }
        // Odczyt
        while( !feof(file) ){
            loadKatalog(headC, file);
        }
    }
    // pozycje.txt
    else if( strcmp( args[1], "pozycje.txt" ) == 0 ){
        file = fopen(args[1], "r");
        if( file == NULL ){
            puts("saveFunc: Blad odczytu pliku.");
            return;
        }
        // Odczyt
        while( !feof(file) ){
            loadPozycje(headR, temp, typeCorrect, file);
        }
    }
    // baza.txt
   else if( strcmp( args[1], "baza.txt" ) == 0 ){
        file = fopen(args[1], "r");
        if( file == NULL ){
            puts("saveFunc: Blad odczytu pliku.");
            return;
        }
        if(headC->beg != NULL){
            // Usuniecie dotychczasowej listy katalogow
            delAllCatalogs(headC, headR);
        }
        if(headR->beg != NULL){
            // Usuniecie dotychczasowej listy plyt
            delAllRecords(headC, headR);
        }

        // Funkcja load baza.txt
        loadBaza(headR, headC, typeCorrect, file, temp);
    }
    else{
        puts("loadFunc: Niepoprana nazwa pliku.");
        return;
    }
    fclose(file);
    free(temp);
    puts("Zaladawano plik.");
}
// Pomoc
void helpFunc(){
    puts("Dostępne funkcje:");
    puts("add-c nazwa       -> dodanie nowego katalogu");
    puts("rem-c nazwa       -> usuniecie katalogu");
    puts("mod-c nazwa       -> zmiana nazwy katalogu");
    puts("show-c nazwa      -> wyświetlenie zawartości katalogu");
    puts("show-c-all        -> wyświetlenie listy katalogów");
    puts("show-r-all        -> wyświetlenie wszytskich płyt");
    puts("add-r nazwa       -> dodanie nowej płyty");
    puts("add-r-c nr_kat    -> dodanie plyty do katalogu");
    puts("mod-r nr_kat      -> modyfikacja płyty");
    puts("srch-r kryterium  -> wyszukiwanie płyty zgodnie z kryt. (title, type, number)");
    puts("mov-r nr_kat      -> przeniesienie płyty do katalogu");
    puts("rem-r nr_kat      -> usunięcie płyty (a- z bazy, b- z katalogu)");
    puts("save plik.txt     -> zapis bazy do pliku (katalog.txt, pozycje.txt, baza.txt)");
    puts("load plik.txt     -> odczyt bazy z pliku (katalog.txt, pozycje.txt, baza.txt)");
    puts("help              -> lista funkcji");
    puts("");
}

