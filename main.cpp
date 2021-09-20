#include <iostream>
#include "histogram.h.h"
#include <math.h>
#include <conio.h>
#include <string>
#include <windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
using namespace std;




int main()
{
    size_t number_count, bin_count;
    int n,H;
    float bin_razrydi[100];
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);
    cerr << "Enter bin count: ";
    cin >> bin_count;
    cerr << "Enter high: ";
    cin >> H;
    double min = numbers[0];
    double max = numbers[0];
    find_minmax(numbers, min, max);
    const auto bins = make_histogram(numbers, bin_count, number_count, min, max);
    show_histogram_svg(bins, H, bin_count);

    return 0;
}

