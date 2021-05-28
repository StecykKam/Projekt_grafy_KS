# Projekt_grafy_KS
Repozytorium powstało na potrzeby projektu z  przedmiotu teorii grafów.


Zasada użycia algorytmu:
- Najwygodniej jest wykonać git clone  do folderu na swoim komputerze
- Program wczytuje dane z pliku txt o następującym formacie: ( dwa testowe pliki są dołączony w folderze i jeden z nich ustawiony jako domyślny)
1) Należy zacząć od stworzenia pliku txt w obrębie katalogu Algorytm Bellmana_Forda (tam gdzie main.cpp) i wpisania w pierwszej linijce liczbę node'ów naszego grafu
2) Następnie należy od nowych linii rozpocząć wpisywanie kolejnych krawędzi naszego grafu w następującym schemacie:
  - początek(nr node) koniec(nr node) wartość krawędzi(int)
  - przykład linijki z krawędzią:
  0 1 3              <----- krawędź od wierzchołka 0 do 1 o wartośći 3
  ważne jest to, że node'y muszą być numerowane od 0 ( 0 ,1 ,2 ,3 ... , n) !!!
  Algorytm zaczyna pracę od wiezchołka nr 0

3) W main.cpp należy we wskazanym miejscu zmienić nazwę pliku domyślnego na swój stworzony.
4) Po upewnieniu się, że wszystko zostało wykonane właściwie można skompilować kod w środowisku, a następnie uruchomić. Program wypisze dane grafu i przedstawi najkrótsze wartości ścieżek do wszystkich wierzchołków za pomocą algorytmu Bellmana-Forda oraz wyświetli najkrótszą ścieżkę od noda początkowego do ostatniego w naszym grafie.
