# recordsDatabase
Project 3 from PRI classes.

Zad 3.5

Napisać komputerowy katalog płyt (lub odpowiednio rozbudować poprzedni program (zad. 2)), 
zorganizowanych w działach tematycznych (odpowiednik rodzaju danych w zad. 2). 
Zarówno liczba działów jak i płyt nie jest ograniczona. Nazwy działów nie mogą się powtarzać. 
W ramach każdego działu pozycje płyt opisywane są jak w zad 2, tzn.: tytuł, rodzaj nośnika, nr katalogowy. 
Dana płyta może przynależeć do kilku działów jednocześnie lub do żadnego.

Program powinien umożliwiać:
->dodawanie nowych i modyfikację już istniejących pozycji,
->utworzenie nowego lub usunięcie istniejącego działu,
->zmianę nazwy dowolnego działu,
->przenoszenie określonej płyty z jednego działu do drugiego,
->dodawanie i usuwanie określonej płyty z danego działu,
->usuwanie określonej płyty z całego katalogu,
->wyszukiwanie i wyświetlanie płyt wg zadanych parametrów – tytuł, rodzaj nośnika, nr katalogowy 
(np.: wyświetl wszystkie płyty CD, albo: znajdź płyty zatytułowane Armagedon), wyświetlone pozycje 
powinny zawierać pełną informację, tzn. tytuł, rodzaj nośnika, nr i działy, w których się znajdują.
->wyświetlanie zawartości dowolnie wybranego działu
->wyświetlanie istniejących działów
->wyświetlanie istniejących rekordów

Program powinien umożliwiać zapis danych w trzech plikach tekstowych (rozszerzenie *.txt) 
umożliwiających odczytywanie i zapisywanie oraz modyfikację danych przy użyciu dowolnego edytora tekstowego:

1. plik zawierający same katalogi – katalog.txt
2. plik zawierający rekordy – pozycje.txt
3. plik zawierający kompletne dane (rekordy+katalogi+łącza) - baza.txt

Każdy plik może być zapisywany i odczytywany niezależnie poprzez wydawanie odpowiednich 
komend np.: save katalog.txt lub load baza.txt. Wczytanie pliku pozycje.txt skutkuje dopisaniem nowych rekordów 
jako nienależących do żadnego katalogu (identyfikacja po numerze katalogowym). 
Wczytanie pliku katalog.txt skutkuje dopisaniem nowych działów (identyfikacja po nazwie). 
Po wczytaniu pliku baza.txt dotychczas istniejąca struktura zostaje usunięta.
