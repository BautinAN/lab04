#include <iostream>
#include "histogram.h..h"
#include <math.h>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <sstream>

using namespace std;


int
main(int argc, char* argv[])
{
    Input input;

    if (argc > 1)
    {
        input = download(argv[1]);
    }
    else
    {
        input = read_input(cin, true);
    }

    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input);

    return 0;
}

