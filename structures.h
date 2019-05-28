#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

// Deklaracja struktury katalogu
typedef struct Catalog{
    char nameCat[10];       // Nazwa katalogu

    struct HandlerRL *rList;
    struct Catalog *next;
}Catalog;

// Deklaracja struktury płyty
typedef struct Record{
    char nameRec[10];       // Nazwa plyty
    char type[6];           // Rodzaj nośnika
    char number[6];         // Numer identyfikacyjny

    struct HandlerCL *cList;   // Lista katalogow, do ktorych nalezy
    struct Record *next;
}Record;

// Deklaracja struktury katalogow
typedef struct catList{
    struct Catalog *cat;
    struct catList *next;
}catList;

// Deklaracja struktury plyt
typedef struct recList{
    struct Record *rec;
    struct recList *next;
}recList;

// Handler list katalogow
struct HandlerCL{
    catList *beg, *end;
};
// Handler list plyt
struct HandlerRL{
    recList *beg, *end;
};
// Handler płyt
struct HandlerR{
    Record *beg, *end;
};
// Handler katalogu
struct HandlerC{
    Catalog *beg, *end;
};

#endif // _STRUCTURES_H_
