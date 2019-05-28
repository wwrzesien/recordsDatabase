#ifndef _FUNCTION_H_
#define _FUNCTION_H_

// Funkcja zwracaja liczbe argumentow
int numArgs(char **args);
// Dodawanie katalogu
void addCatFunc(char **args, struct HandlerC *headC);
// Usuniecie katalogu
void remCatFunc(char **args, struct HandlerC *headC, struct HandlerR *headR);
// Zmiana nazwy katalogu
void modCatFunc(char **args, struct HandlerC *headC);
// Wyświetlenie zawartosci/listy katalogów
void showCatFunc(char **args, struct HandlerC *headC);
// Wyswietlenie płyt
void showRecFunc(char **args, struct HandlerR *headR);
// Dodanie płyty
void addRecFunc(char **args, char **typeCorrect, struct HandlerR *headR, struct HandlerC *headC);
// Dodanie plyty do katalogu
void addRecToCatFunc(char **args, struct HandlerR *headR, struct HandlerC *headC);
// Modyfikacja płyty
void modRecFunc(char **args, struct HandlerR *headR, char **typeCorrect);
// Wyszukiwanie płyty
void srchRecFunc(char **args, struct HandlerR *headR);
// Przeniesienie płyty
void movRecFunc(char **args, struct HandlerC *headC, struct HandlerR *headR);
// Usuniecie płyty katalogu
void remRecFunc(char **args, struct HandlerR *headR, struct HandlerC *headC);
// Zapis do pliku
void saveFunc(char **args, struct HandlerR *headR, struct HandlerC *headC);
// Odczyt z pliku
void loadFunc(char **args, struct HandlerR *headR, struct HandlerC *headC, char **typeCorrect);
// Pomoc
void helpFunc();

#endif // _FUNCTION_H_

