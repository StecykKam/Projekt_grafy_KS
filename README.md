# Projekt_grafy_KS
Repozytorium powstało na potrzeby projektu z  przedmiotu teorii grafów.


Zasada użycia algorytmu:
- Najwygodniej jest wykonać git clone  do folderu na swoim komputerze
- Program wczytuje dane z pliku txt o następującym formacie: ( próbny plik jest dołączony w folderze i jest ustawiony jako domyślny)
1) Należy zacząć od stworzenia pliku txt w obrębie katalogu Algorytm Bellmana_Forda (tam gdzie main.cpp) i wpisania w pierwszej linijce liczbę node'ów naszego grafu
2) Następnie należy od nowych linii rozpocząć wpisywanie kolejnych krawędzi naszego grafu w następującym schemacie:
  - (początek(nr node),koniec(nr node),wartość krawędzi(int)),
  ważne jest to, że node'y muszą być numerowane od 0 ( 0 ,1 ,2 ,3 ... , n) !!!

3) W main.cpp należy we wskazanym miejscu zmienić nazwę pliku domyślnego na swój stworzony.
4) Po upewnieniu się, że wszystko zostało wykonane właściwie można skompilować kod w środowisku, a następnie uruchomić. Program wypisze dane grafu oraz przedstawi najkrótsze ścieżki do wszystkich wierzchołków za pomocą algorytmu Bellmana-Forda.
