#ifndef _LIST_H_
#define _LIST_H_
// Funkcja czyszczaca buffer
void clearInputBuffer();
// Funkcja zwracajaca wskaznik na katalog
Catalog **findCatalog(struct HandlerC *headC, char *name);
// Funkcja zwracajaca wskaznik na plyte
Record **findRecord(struct HandlerR *headR, char *number);
// Funkcja zwracajca wskaznik na katalog w liscie katalogow plyty
catList **findCatInRec(struct HandlerR *headR, char *number, char *nameCat);
// Funkcja dodajaca plyte do listy plyt katalogu
void addRecToCat(char *catalog, struct HandlerC *headC, struct HandlerR *headR, char *number);
// Funkcja dodajaca katalog do liste katalogow do plyty
void addCatToRec(char *catalog, struct HandlerC *headC, struct HandlerR *headR, char *number);
// Funkcja dodajaca katalog
void addCatalog(struct HandlerC *headC, char *name);
// Sortowanie bez uwzglednienia wielkosci znakow
int sortWOCase(char const *a, char const *b);
// Funkcja sortujaca
void sortRecord(struct HandlerC *headC, char *name);
// Funkcja dodajaca plyte
void addRecord(struct Record *temp, struct HandlerR *headR);
// Funkcja usuwajaca katalog z listy katalogow plyty
void remCatFromRec(struct HandlerR *headR, char *number, char *nameCat);
// Funkcja usuwajaca plyte z listy plyt katalogu
void remRecFromCat(struct HandlerC *headC, char *number, char *nameCat);
// Funkcja usuwajaca katalog
void remCatalog(struct HandlerC *headC, char *name);
// Funkcja usuwajaca plyte
void remRecord(struct HandlerR *headR, char *number);
// Funkcja sprawdzajaca poprawnosc typu nosnika
int isCorrectType( char *type, char **tab );
// Funkcja sprawdzajaca poprawnosc numeru
int isCorrectNumber(struct HandlerR *headR, char *number);
// Funkcja usuwajaca wszytskie katalogi
void delAllCatalogs(struct HandlerC *headC, struct HandlerR *headR);
// Funkcja usuwajaca wszystkie plyty
void delAllRecords(struct HandlerC *headC, struct HandlerR *headR);
// Funkcja zapis katalog.txt
void saveKatalog(struct HandlerC *headC, FILE *file);
// Funkcja zapis pozycje.txt
void savePozycje(struct HandlerR *headR, FILE *file);
// Funkcja zapis baza.txt
void saveBaza(struct HandlerR *headR, FILE *file);
// Funkcja load katalog.txt
void loadKatalog(struct HandlerC *headC, FILE *file);
// Funkcja load pozycje.txt
void loadPozycje(struct HandlerR *headR, struct Record *temp, char **typeCorrect, FILE *file);
// Funkcja load baza.txt
void loadBaza(struct HandlerR *headR, struct HandlerC *headC, char **typeCorrect, FILE *file, struct Record *temp);

 #endif // _LIST_H_

