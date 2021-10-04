#include <iostream>
#include "histogram.h..h"
#include <math.h>
#include <string>
#include <vector>
#include <curl/curl.h>

using namespace std;



int main()
{   curl_global_init(CURL_GLOBAL_ALL);
    const auto input = read_input(cin, true);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input);

    return 0;
}

