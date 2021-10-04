#include <iostream>
#include "histogram.h..h"
#include <math.h>
#include <string>
#include <vector>
#include <curl/curl.h>

using namespace std;


int
main(int argc, char* argv[])
{
    if (argc > 1)
        for (size_t i = 0; i < argc; i++)
        {
            CURL *curl = curl_easy_init();
            if(curl)
            {
                CURLcode res;
                curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);

                if (curl_easy_strerror(res) != "CURLE_OK")
                {
                    cout << curl_easy_strerror(res);
                    exit(1);
                }
            }
            return 0;
        }



    curl_global_init(CURL_GLOBAL_ALL);
    const auto input = read_input(cin, true);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input);

    return 0;
}

