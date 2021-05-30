#include <iostream>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

int main()
{
    size_t number_count, bin_count;
    size_t k=0,C,z;
    int n,H,K;
    float bin_razrydi[100];
    cerr << "Enter number count: ";
    cin >> number_count;
    vector<double> numbers(number_count);
    cerr << "Enter numbers: ";
    for (size_t i=0; i < number_count; i++)
    {
        cin >> numbers[i];
    }
    cerr << "Enter bin count: ";
    cin >> bin_count;
    cout << "Enter high: ";
    cin >> H;
    K=bin_count;
    vector<size_t> bins(bin_count);
    double min = numbers[0];
    double max = numbers[0];
    for (double x : numbers)
    {
        if (x < min)
        {
            min = x;
        }
        else if (x > max)
        {
            max = x;
        }
    }
    double bin_size = (max-min)/bin_count;
    for (size_t i = 0; i < number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[bin_count-1]++;
        }
    }
    double max_count=bins[0];
    for (size_t j=1; j< bin_count; j++)
    {
        if (bins[j]>max_count) max_count=bins[j];
    }
    C=H/K;


    if (max_count > 76)
    {
        for (size_t j=0; j < bin_count; j++)
        {
            if (bins[j] < 10)
            {
                cout << " ";
            }
            if ((bins[j] < 100) && (bins[j]>10))
            {
                cout << "  ";
            }
            cout << bins[j] << "|";
            k=0;
            size_t height = 76 * (static_cast<double>(bins[j])/max_count);
            while ((k != height) && (k < height))
            {
                cout << "*";
                k=k+1.0;
            }
            cout << "\n";
            z=1;
            while (z < C)
            {
                if (max < 10)
                {
                    cout << "  ";
                }
                if ((max < 100) && (max>10))
                {
                    cout << " ";
                }
                if (max > 100)
                {
                    cout << "   ";
                }
                cout << "|";
                k=0;
                while ((k != height) && (k < height))
                {
                    cout << "*";
                    k=k+1.0;
                }
                z=z+1.0;
                cout << "\n";
            }
        }
    }
    else if (max > 10)
    {
        for (size_t j=0; j < bin_count; j++)
        {
            if (bins[j] < 10)
            {
                cout << " ";
            }
            cout << bins[j] << "|";
            k=0;
            while (k != bins[j])
            {
                cout << "*";
                k++;
            }
            cout << "\n";
            z=1;
            while (z < C)
            {
            cout << "  ";
            cout << "|";
            k=0;
            while (k != bins[j])
            {
                cout << "*";
                k++;
            }
            z=z+1.0;
            cout << "\n";
        }
    }
    }
    else
    {
        for (size_t j=0; j<bin_count; j++)
        {
            cout << bins[j] << "|";
            k=0;
            while (k != bins[j])
            {
                cout << "*";
                k++;
            }
            cout << "\n";
            z=1;
            while (z < C)
            {
                cout << " ";
                cout << "|";
                k=0;
                while (k != bins[j])
                {
                    cout << "*";
                    k++;
                }
                z=z+1.0;
                cout << "\n";
            }
        }
    }
    getch();
    return 0;
}
