#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_7.3rec/Lab_7.3rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestCountNegativeNumbers)
        {
            const int rowCount = 3;
            const int colCount = 3;
            int** a = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                a[i] = new int[colCount];

            a[0][0] = -1; a[0][1] = 1; a[0][2] = 0;
            a[1][0] = 1; a[1][1] = -2; a[1][2] = 0;
            a[2][0] = -4; a[2][1] = 1; a[2][2] = -6;

            int totalNegatives = Part1_CountCols(a, rowCount, colCount, 0);
            Assert::AreEqual(2, totalNegatives);

            for (int i = 0; i < rowCount; i++)
                delete[] a[i];
            delete[] a;
        }
    };
}
