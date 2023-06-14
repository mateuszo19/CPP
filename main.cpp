/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream> //dla operacji wejścia/wyjścia
#include <cmath> //dla funkcji sqrt
#include <cstdlib> //dla funkcji qsort

using namespace std;

void printTab(int tab[], int n); //wyświetlanie elementów tablicy
void genTabSorted(int tab[], int n); //generowanie elementów tablicy - kolejne liczby naturalne
void genTabRevSorted(int tab[], int n); //generowanie elementów tablicy - liczby naturalne w kolejności malejącej
void genTabRand(int tab[], int n); //generowanie elementów tablicy - wartości pseudolosowe (mogą się powtarzać)
void genTabConst(int tab[], int n); //generowanie elementów tablicy - wartość stała
int findLinear(int tab[], int n, int x); //x - szukany element, jeśli jest - zwraca indeks elementu, jeśli nie - zwraca -1
int findJump(int tab[], int n, int x); //wyszukiwanie skokowe
int findBinaryRek(int tab[], int left, int right, int x); //wyszukiwanie binarne - rekurencja
int findBinaryIter(int tab[], int left, int right, int x); //wyszukiwanie binarne - iteracja
double timeFind(int tab[], int n, int x); //zwraca czas działania funkcji wyszukującej
double timeFindBinary(int tab[], int left, int right, int x); //zwraca czas działania funkcji wyszukującej - algorytm połówkowy
double timeSort(int tab[], int n); //zwraca czas działania funkcji sort w sekundach
double timeSortRek(int tab[], int left, int right); //zwraca czas działania funkcji sort w sekundach
void sortBubble(int tab[], int n); //sortowanie bąbelkowe
void sortBubble2(int tab[], int n); //sortowanie bąbelkowe z eliminacją pustych przebiegów
void sortInsert(int tab[], int n); //sortowanie przez wstawianie
void sortSelect(int tab[], int n); //sortowanie przez wybieranie
void sortShake(int tab[], int n); //sortowanie koktajlowe
void sortQuickRek(int tab[], int left, int right); //sortowanie szybkie
int getPivot(int tab[], int left, int right); //wybór elementu osiowego (pivot) dla algorytmu sortQuickRek
void sortQuick2Rek(int tab[], int left, int right); //sortowanie szybkie z wyborem elementu osiowego (pivot)
void sortShell(int tab[], int n); //sortowanie Shella
int compare (const void * a, const void * b); //dla funkcji qsort z biblioteki cstdlib

int main()
{
    cout<<"Algorytmy sortowania i wyszukiwania\n";
    int n = 100000, x = 10;
    int elements [n]; //= {13, 2, -5, 8, 10, -3, 21};
    // genTabSorted(elements, n);
    genTabRevSorted(elements, n);
    // genTabRand(elements, n);
    //genTabConst(elements, n);
    //printTab(elements, n);
    cout<<"\nSortowanie tablicy ...\n";
    // cout << "Rezultat sortBubble2(elements, n):\n";
    cout << "t = " << timeSort(elements, n) << " s\n";
    //cout << "t = " << timeSortRek(elements, 0, n - 1) << " s\n";
    // cout << "t = " << timeFind(elements, n, x) << " ms\n";
    // cout << "t = " << timeFindBinary(elements, 0, n - 1, x) << " s\n";
    //sortBubble(elements, n);
    //sortBubble2(elements, n);
    //sortInsert(elements, n);
    //sortSelect(elements, n);
    //sortShake(elements, n);
    //sortQuickRek(elements, 0, n - 1);
    //sortQuick2Rek(elements, 0, n - 1);
    //sortShell(elements, n);
    //qsort(elements, n, sizeof(int), compare);
    //cout << "indeks = " << findLinear(elements, n, x) << endl;
    //cout << "indeks = " << findJump(elements, n, x) << endl;
    //cout << "indeks = " << findBinaryRek(elements, 0, n - 1, x) << endl;
    //cout << "indeks = " << findBinaryIter(elements, 0, n - 1, x) << endl;
    //cout << endl;
    //printTab(elements, n);
    
    return 0;
}

void printTab(int tab[], int n)
{
    for(int i = 0; i < n; i++)
        cout << tab[i] << " ";
    
    cout << endl;
}

void genTabSorted(int tab[], int n)
{
    for(int i = 0; i < n; i++)
        tab[i] = i + 1;
}

void genTabRevSorted(int tab[], int n)
{
    for(int i = 0; i < n; i++)
        tab[i] = n - i;
}

void genTabRand(int tab[], int n)
{
    srand((int)time(0)); //generator liczb pseudolosowych
    for(int i = 0; i < n; i++)
        tab[i] = rand() % n;
}

void genTabConst(int tab[], int n)
{
    srand(time(NULL)); //generator liczb pseudolosowych
    int c = rand() % n;
    for(int i = 0; i < n; i++)
        tab[i] = c;
}

double timeFind(int tab[], int n, int x)
{
    clock_t start, stop;
    start = clock();
    // findLinear(tab, n, x);
    findJump(tab, n, x);
    stop = clock();
    
    return (stop - start) / (double)(CLOCKS_PER_SEC/1000);
}

double timeFindBinary(int tab[], int left, int right, int x)
{
    clock_t start, stop;
    start = clock();
    //findBinaryRek(tab, left, right, x);
    findBinaryIter(tab, left, right, x);
    stop = clock();
    
    return (stop - start) / (double)(CLOCKS_PER_SEC/1000);
}

int findLinear(int tab[], int n, int x)
{
    for(int i = 0; i < n; i++)
        if (tab[i] == x)
            return i; //jeśli został znaleziony element

    return -1; //jeśli brak szukanego elementu
}

int findJump(int tab[], int n, int x)
{
    int block = (int)(sqrt(n));
    int index = 0;
    while(tab[min(block, n) - 1] < x)
    {
        index = block;
        block += (int)(sqrt(n));
    if (index >= n)
      return -1;
    }
    while (tab[index] < x)
    {
        index++;
        if (index == min(block, n))
            return -1;
    }
    if (tab[index] == x)
        return index;
    
    return -1;
}

int findBinaryRek(int tab[], int left, int right, int x)
{
    if(left <= right)
    {
        int mid = (left + right) / 2; //indeks elementu środkowego
        if(tab[mid] == x)
            return mid; //element został znaleziony
        if(tab[mid] < x) //element szukany jest większy od środkowego
            return findBinaryRek(tab, mid + 1, right, x);
        
        return findBinaryRek(tab, left, mid - 1, x); //element szukany jest mniejszy od środkowego
    }
    
    return -1; //brak szukanego elementu
}

int findBinaryIter(int tab[], int left, int right, int x)
{
    while(left <= right)
    {
        int mid = (left + right) / 2;
        if(tab[mid] == x) //element został znaleziony
            return mid;
        else if(tab[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    
    return -1; //brak szukanego elementu
}

double timeSort(int tab[], int n)
{
    clock_t start, stop;
    start = clock();
    //sortBubble(tab, n);
    //sortBubble2(tab, n);
    // sortInsert(tab, n);
    //sortShake(tab, n);
    sortSelect(tab, n);
    //sortShell(tab, n);
    // qsort(tab, n, sizeof(int), compare);
    stop = clock();
    
    return (stop - start) / (double)(CLOCKS_PER_SEC/1000);
}

double timeSortRek(int tab[], int left, int right)
{
    clock_t start, stop;
    start = clock();
    //sortQuickRek(tab, left, right);
    sortQuick2Rek(tab, left, right);
    stop = clock();
    
    return (stop - start) / (double)CLOCKS_PER_SEC;
}

void sortBubble(int tab[], int n)
{
    for(int i = 0; i < n; i++)
        for(int j = n - 1; j > i; j--)
            if(tab[j - 1] > tab[j])
                swap(tab[j - 1], tab[j]); //zamiana sąsiednich elementów
}

void sortBubble2(int tab[], int n)
{
    for(int i = 0; i < n; i++)
    {
        bool swapped = false;
        for(int j = n - 1; j > i; j--)
            if(tab[j - 1] > tab[j])
            {
                swapped = true;
                swap(tab[j - 1], tab[j]); //zamiana sąsiednich elementów
            }
        if(!swapped)
            break; //Nie nastąpiła zamiana, więc koniec sortowania
    }    
}

void sortInsert(int tab[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int j = i;
        int element = tab[j];
        while((j > 0) && (tab[j - 1] > element))
        {
            swap(tab[j - 1], tab[j]); //zamiana elementów
            j--;
        }
        tab[j] = element; //wstawianie elementu
    }
}

void sortSelect(int tab[], int n)
{
   int idMin = 0;
   for(int i = 0; i < n; i++)
   {
        //znajdowanie najmniejszego elementu
        idMin = i;
        for(int j = i + 1; j < n; j++)
            if(tab[j] < tab[idMin])
                idMin = j;
                
        swap(tab[i], tab[idMin]); //zamiana aktualnie pierwszego elementu z aktualnie minimalnym
   }
}

void sortShake(int tab[], int n)
{
    int left = 0, right = n - 1;
    bool swapped = true;
    while(swapped)
    {
        swapped = false;
        for(int i = left; i < right; i++) //iteracja od lewej do prawej
            if(tab[i] > tab[i + 1])
            {
                swap(tab[i], tab[i + 1]); //zamiana sąsiednich elementów
                swapped = true;
            }
        right--;
        for(int i = right; i > left; i--) //iteracja od prawej do lewej
            if(tab[i] < tab[i - 1])
            {
                swap(tab[i], tab[i - 1]); //zamiana sąsiednich elementów
                swapped = true;
            }
        left++;
    }
}

void sortQuickRek(int tab[], int left, int right)
{
    if(left < right)
    {
        int pivot = getPivot(tab, left, right);
        sortQuickRek(tab, left, pivot - 1); //lewa część tablicy
        sortQuickRek(tab, pivot + 1, right); //prawa część tablicy
    }
}

int getPivot(int tab[], int left, int right)
{
    int pivot = right; //element osiowy (pivot) - ostatni element tablicy
    int index = left - 1;
    for(int i = left; i < right; i++)
        if(tab[i] < tab[pivot])
        {
            index++;
            swap(tab[i], tab[index]);
        }
    swap(tab[index + 1], tab[right]);
    
    return index + 1; //indeks elementu osiowego
}

void sortQuick2Rek(int tab[], int left, int right)
{
   int i = left, j = right;
   int pivot = tab[(left + right) / 2]; //wybór elementu osiowego (pivot)
   while(i <= j)
   {
        while(tab[i] < pivot)
            i++;
        
        while(tab[j] > pivot)
            j--;
        
        if(i <= j)
        {
            swap(tab[i], tab[j]);
            i++;
            j--;
        }
   }
   if(left < j)
        sortQuick2Rek(tab, left, j);
    if(i < right)
        sortQuick2Rek(tab, i, right);
}

void sortShell(int tab[], int n)
{
    for(int d = n / 2; d > 0; d /= 2)
    {
        for(int i = d; i < n; i++)
        {
            int element = tab[i];
            int j;
            for(j = i; j >= d && tab[j - d] > element; j -= d)
                tab[j] = tab[j - d];
                
            tab[j] = element;
        }
    }
}

int compare(const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}
