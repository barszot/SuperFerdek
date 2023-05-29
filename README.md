Dokumentacja gry.

Przy tworzeniu gry wykorzystałem bibliotekę SFML do stworzenia klasy Window odpowiadającej za wyświetlanie gry. Gra składa się domyślnie z trzech poziomów, ale kod jest tak skonstruowany, że utworzenie nowych poziomów to żaden problem. Gra oferuje możliwość zapisania / wczytania stanu gry, oraz przechowuje rekordowy wynik. Jeśli rekord zostanie pobity, na ekranie wygranej pojawi się napis "NOWY REKORD" i rekord zostanie uaktualniony w pliku data.json przechowującym jednocześnie rekordowy wynik oraz zapisany stan gry.

By uruchomić grę, wystarczy pobrać repozytorium, wpisać w terminal komendę make (w celu skompilowania gry), po czym wystarczy wpisać
./build/main (w celu uruchomienia gry).

Sterowanie

W / górna strzałka - skok,
A / lewa strzałka - ruch w lewo,
D / prawa strzałka - ruch w prawo,
S / dolna strzałka - przykuc

Z - zapisanie / wczytanie gry
ENTER - (będąc w ekranie startowym) - włączanie gry
(po wygranej/przegranej) - powrót do ekranu startowego

Klasy:

Window - reprezentuje okno gry

Game - reprezentuje grę, ma metody odpowiadające za aktualizowanie gry w czasie, przełączanie na kolejne poziomy itp.

Tile - reprezentuje kafelek na mapie. Dziedziczą po niej następujące klasy:
    
Coin (Tile) - reprezentuje monetę. Można je zbierać

QuestionTile (Tile) - reprezentuje kafelki ze znakiem zapytania, które reagują jeśli gracz uderzy je od dołu głową. Dziedziczą po niej następujące klasy:

QuestionTileBeer (QuestionTile) - tworzy obiekt Beer po aktywacji.

QuestionTileCoin (QuestionTile) - po aktywacji daje graczowi monetę.

Mob - reprezentuje "moby". Dziedziczą po niej następujące klasy:

Beer (Mob) - reprezentuje piwo. Daje graczowi doładowanie po tym jak go dotknie.

Spark (Mob) - reprezentuje iskierkę która pojawia się przy aktywacji QuestionTileCoin. Jedyna rola Spark to pojawić się i szybko zniknąć, oraz dać graczowi +1 monetę.

Enemy (Mob) - reprezentuje wrogów. Dziedziczą po niej klasy:

Pazdzioch (Enemy) - reprezentuje wroga-Paździocha.

Boczek (Enemy) - reprezentuje wroga-Boczka.


TileManager - klasa wczytujące rozmieszczenie kafelków i zarządzająca nim. Ma dwuwymiarowy wektor przechowujący unique-pointery wskazujące na poszczególne obiekty typu Tile.

MobManager - klasa wczytujące rozmieszczenie mobów i zarządzająca nim. Ma jednowymiariow wektor przechowujący shared-pointery wskazujące na poszczególne obiekty typu Mob (generowane na samym początku rozpoczęcia poziomu).

Ferdek - reprezentuje gracza - pana Ferdynanda.


Klasy Tile i Mob mają dziedziczony (protected) atrybut int type. Należy dodać że niektóre typy są zarezerwowane dla poszczególnych klas:
(wrogowie (klasy dziedziczące po Enemy) muszą mieć ujemne wartości atrybutu type):


Coin -> 100,
QuestionTileBeer -> 10,
QuestioTileCoin -> 11,
Beer -> 1,
Spark -> 2,
Pazdzioch -> -1,
Boczek -> -2.
