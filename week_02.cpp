#include <iostream>
using namespace std;

void InputArray_1D(int*& a, int& n);
void FreeArray_1D(int*& a);
void OutputArray_1D(int* a, int n);
void CreateMatrix(int**& a, int& n, istream& input);
void PrintMatrix(int** a, int& n, ostream& output);
void FreeMatrix(int**& a, int& n);

void main()
{
    int n = 0;
    int* a = NULL;

    InputArray_1D(a, n);
    OutputArray_1D(a, n);
    FreeArray_1D(a);

    int** arr = NULL;
    int m;

    CreateMatrix(arr, m, cin);
    PrintMatrix(arr, m, cout);
    FreeMatrix(arr, m);

    return;
}

void InputArray_1D(int*& a, int& n)
{
    cout << "Nhap n = ";
    cin >> n;

    if (n < 1) return;

    a = new int[n];

    if (a == NULL) return;

    cout << "Nhap mang 1 chieu: ";
    for (int i = 0; i < n; i++)
        cin >> a[i];
}

void FreeArray_1D(int*& a)
{
    delete[] a;
}

void OutputArray_1D(int* a, int n)
{
    cout << "\nMang da nhap la:" << endl;
    for (int i = 0; i < n; i++)
        cout << a[i] << '\t';
    cout << "\n";
}

void CreateMatrix(int**& a, int& n, istream& input)
{
    cout << "Nhap n: ";
    input >> n;

    if (n < 1) return;

    a = new int* [n];

    if (a == NULL) return;

    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
        if (a[i] == NULL) return;
    }

    cout << "Nhap mang 2 chieu:\n";

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            input >> a[i][j];
}

void PrintMatrix(int** a, int& n, ostream& output)
{
    output << "\nMang da nhap la:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            output << a[i][j] << " ";
        output << "\n";
    }
}

void FreeMatrix(int**& a, int& n)
{
    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
}