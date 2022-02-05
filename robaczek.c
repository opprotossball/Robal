#include <stdio.h>
#include <stdlib.h>

#define ELEM 2 //liczba wspolrzednych okreslacjacych pozycje robaka
// lista liniowa przechowujaca dane z zestawu wejscia
typedef struct zestawy
{
    int nr;               // numer zestawu
    int wierzch;          // aktualny wiezcholek
    int n_wierzch;        // liczba wierzcholkow
    int n_krawedzi;       // liczba krawedzi
    int **drzewo;         // macierz sasiedztwa jako implementacja grafu (drogi w drzewie)
    int pocz[ELEM];       // poczatkowa pozycja naszego robaka(jego wspolrzedne) np. [2 3]
    int kon[ELEM];        // koncowa pozycja naszego robaka(jego wspolrzedne) np. [2 3]
    struct zestawy *nast; // wskaznik do nastepnego zestawu
} zestawy_t;

void init_zestaw(zestawy_t *zestaw)
{
    fprintf(stderr, "1\n");
    zestaw->drzewo = malloc(zestaw->n_wierzch * sizeof *(zestaw->drzewo));
    fprintf(stderr, "2\n");
    for (int i = 0; i < zestaw->n_wierzch; i++)
    {
        zestaw->drzewo[i] = malloc(zestaw->n_wierzch * sizeof(zestaw->drzewo[i]));
    }
    fprintf(stderr, "3\n");
    //*zestaw->drzewo = malloc(zestaw->n_wierzch * sizeof (zestawy_t));
    /*for (int i = 0; i < zestaw->n_wierzch; i++)
    {
        zestaw->drzewo[i] = malloc(zestaw->n_wierzch * sizeof(zestaw ->drzewo));
    }*/

    for (int i = 0; i < zestaw->n_wierzch; i++)
    {
        for (int j = 0; j < zestaw->n_wierzch; j++)
        {
            zestaw->drzewo[i][j] = 0;
        }
    }
    fprintf(stderr,"4\n");
}

void dodaj_polaczenie(zestawy_t *zestaw, int wpocz, int wkon)
{
    zestaw->drzewo[wpocz-1][wkon-1] = 1;
    zestaw->drzewo[wkon-1][wpocz-1] = 1; //graf nieskierowany

}

int Czytaj(char *fname, zestawy_t *zestaw)
{
    FILE *wejscie = fopen(fname, "r"); // czytam z pliku wejscia
    int n_zestaw;
    int liczba_zestawow;
    zestawy_t *tmp = zestaw;

    if (wejscie == NULL)
    {
        fprintf(stderr, "Duuuupa"); // profesjonalna obsluga bledow
        return 1;
    }

    if (fscanf(wejscie, "%d", &liczba_zestawow) != 1) //wczytywanie
    {
        fprintf(stderr, "Duuuupa"); // profesjonalna obsluga bledow
        return 1;
    }

    for (int i = 0; i < liczba_zestawow; i++)
    {
        if (fscanf(wejscie, "%d", &tmp->n_wierzch) != 1)
        {
            fprintf(stderr, "Duuuupa"); // profesjonalna obsluga bledow
            return 1;
        }
        init_zestaw(tmp); // zainicjuj tablice drzewo w zestawie
        for (int i = 0; i < tmp->n_wierzch - 1; i++)
        {
            int wpocz, wkon;
            if (fscanf(wejscie, "%d %d", &wpocz, &wkon) == 2)
            { //?? wsm nie jestem pewny
                dodaj_polaczenie(tmp, wpocz, wkon);
            }
        }
        if (fscanf(wejscie, "%d %d %d %d", &tmp->pocz[0], &tmp->pocz[1], &tmp->kon[0], &tmp->kon[1]) != 4)
        {
            fprintf(stderr, "Duuuupa"); // profesjonalna obsluga bledow
            return 1;
        }
        tmp->nast = malloc(sizeof *tmp->nast);
        if (tmp->nast == NULL)
        {
            fprintf(stderr, "Nieudalo sie przydzielic pamieci\n");
            return 1;
        }
        tmp = tmp->nast;
    }
    return 0;
}
// funkcja, ktora wykorzystuje algorytm dijikstry do wyszukania
// najkrotszej drogi z pozycji poczatkowej robala do pozycji koncowej
// zwraca kolejno odwiedzone wierzcholki
// jesli droga ktosza niz 10*n ruchow to zwroci 0
int *czy_jest_droga(zestawy_t *zestawy);

int main(int argc, char **argv)
{
    zestawy_t zestaw;

    if (argc != 2)
    {
        fprintf(stderr, "Duuuupa"); // profesjonalna obsluga bledow
        return 1;
    }
    printf("%d", Czytaj(argv[1], &zestaw));
    return 0;
}
