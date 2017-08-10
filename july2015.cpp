#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>

using namespace std;

void subsample(const int row, const int col, float* matrix)
{
    const int row1 = (row + 1) / 2;
    const int col1 = (col + 1) / 2;
    
    float m1[row1][col1];
    
    for(int i = 0; i < row1; ++i)
    {
        for(int j = 0; j < col1; ++j)
        {
            int rFrom = i * 2;
            int rTo = i * 2 + 1;
            
            int cFrom = j * 2;
            int cTo = j * 2 + 1;
            
            float sum = 0.0f;
            int count = 0;
            
            for(int r = rFrom; r <= rTo; ++r)
            {
                for(int c = cFrom; c <= cTo; ++c)
                {
                    sum += matrix[r * col + c];
                    ++count;
                }
            }
            
            m1[i][j] = sum / (float)count;
        }
    }
    
    for(int i = 0; i < row1; ++i)
    {
        for(int j = 0; j < col1; ++j)
        {
            cout << m1[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    const int row = 2, col = 3;
    
    float matrix[row][col] = 
    {
        {1.0f, 2.0f, 3.0f},
        {4.5f, 6.5f, 7.5f}
    };
    
    subsample(row, col, &matrix[0][0]);
    
    return 0;
}