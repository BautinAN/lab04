#include <iostream>
#include "histogram.h..h"
#include <math.h>
#include <string>
#include <vector>

using namespace std;



int main()
{
    const auto input = read_input(cin, true);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input);

    return 0;
}

