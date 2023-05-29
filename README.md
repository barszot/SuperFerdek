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
        Coin - reprezentuje monetę. Można je zbierać
        QuestionTile - reprezentuje kafelki ze znakiem zapytania, które reagują jeśli gracz uderzy je od dołu głową. Dziedziczą po niej
        następujące klasy:
            QuestionTileBeer - tworzy obiekt Beer po aktywacji.
            QuestionTileCoin - po aktywacji daje graczowi monetę.
    Mob - reprezentuje "moby". Dziedziczą po niej następujące klasy:
        Beer - reprezentuje piwo. Daje graczowi doładowanie po tym jak go dotknie.
        Spark - reprezentuje iskierkę która pojawia się przy aktywacji QuestionTileCoin. Jedyna rola Spark to pojawić się i szybko zniknąć, oraz dać
        graczowi +1 monetę.
        Enemy - reprezentuje wrogów. Dziedziczą po niej klasy:
            Pazdzioch - reprezentuje wroga-Paździocha
            Boczek - reprezentuje wroga-Boczka
    TileManager - klasa wczytujące rozmieszczenie kafelków i zarządzająca nim. Ma dwuwymiarowy wektor przechowujący unique-pointery wskazujące na poszczególne obiekty typu Tile.
    MobManager - klasa wczytujące rozmieszczenie mobów i zarządzająca nim. Ma jednowymiariow wektor przechowujący shared-pointery wskazujące na poszczególne obiekty typu Mob (generowane na samym początku rozpoczęcia poziomu).
    Ferdek - reprezentuje gracza - pana Ferdynanda.
