#include <iomanip>
#include <iostream>
#include <time.h>

using namespace std;

void PrintRow(int** a, const int rowNo, const int colCount, int colNo)
{
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void InputRow(int** a, const int rowNo, const int colCount, int colNo)
{
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1)
        InputRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    InputRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        InputRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void Part1_ZeroCol(int** a, const int colCount, bool& hasZero, int rowNo, int colNo)
{
    if (a[rowNo][colNo] == 0)
    {
        hasZero = true;
    }
    else if (colNo < colCount - 1)
    {
        Part1_ZeroCol(a, colCount, hasZero, rowNo, colNo + 1);
    }
}

void Part1_CountCol(int** a, const int colCount, int& count, int rowNo, int colNo)
{
    if (a[rowNo][colNo] < 0)
        count++;
    if (colNo < colCount - 1)
        Part1_CountCol(a, colCount, count, rowNo, colNo + 1);
}

int Part1_CountCols(int** a, const int rowCount, const int colCount, int rowNo)
{
    if (rowNo >= rowCount)
        return 0;

    bool hasZero = false;
    Part1_ZeroCol(a, colCount, hasZero, rowNo, 0);

    int count = 0;
    if (hasZero)
    {
        Part1_CountCol(a, colCount, count, rowNo, 0);
    }

    return count + Part1_CountCols(a, rowCount, colCount, rowNo + 1);
}

bool IsMaxInRowN(int** a, const int rowNo, const int value, const int colCount, int colNo)
{
    if (colNo >= colCount)
        return true;
    if (a[rowNo][colNo] < value)
        return false;
    else
        return IsMaxInRowN(a, rowNo, value, colCount, colNo + 1);
}

bool IsMinInColK(int** a, const int colNo, const int value, const int rowCount, int rowNo)
{
    if (rowNo >= rowCount)
        return true;
    if (a[rowNo][colNo] > value)
        return false;
    else
        return IsMinInColK(a, colNo, value, rowCount, rowNo + 1);
}

void Part2_SaddlePointRow(int** a, const int rowCount, const int colCount,
    int& No, const int rowNo, int colNo)
{
    if (IsMaxInRowN(a, rowNo, a[rowNo][colNo], colCount, 0) &&
        IsMinInColK(a, colNo, a[rowNo][colNo], rowCount, 0))
    {
        cout << setw(4) << ++No << setw(6) << rowNo << setw(6) << colNo << endl;
    }
    if (colNo < colCount - 1)
        Part2_SaddlePointRow(a, rowCount, colCount, No, rowNo, colNo + 1);
}

void Part2_SaddlePointRows(int** a, const int rowCount, const int colCount,
    int& No, int rowNo)
{
    Part2_SaddlePointRow(a, rowCount, colCount, No, rowNo, 0);
    if (rowNo < rowCount - 1)
        Part2_SaddlePointRows(a, rowCount, colCount, No, rowNo + 1);
}

int main()
{
    /* srand((unsigned)time(NULL));*/
    int rowCount, colCount;
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;
    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    InputRows(a, rowCount, colCount, 0);
    PrintRows(a, rowCount, colCount, 0);

    int totalNegatives = Part1_CountCols(a, rowCount, colCount, 0);
    cout << "Total negative elements in rows containing at least one zero: " << totalNegatives << endl;

    cout << endl;
    cout << "Saddle points: min in row & max in col" << endl;
    cout << setw(4) << "No" << setw(6) << "Row" << setw(6) << "Col" << endl;
    int No = 0;
    Part2_SaddlePointRows(a, rowCount, colCount, No, 0);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}