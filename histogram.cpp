#include "histogram.h..h"
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <sstream>
#include <windows.h>

using namespace std;


vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in, bool prompt)
{
    Input data;

    if (prompt)
    {
        cerr << "Enter number count: ";
    }
    size_t number_count;
    in >> number_count;

    if (prompt)
    {
        cerr << "Enter numbers: ";
    }
    data.numbers = input_numbers(in, number_count);

    if (prompt)
    {
        cerr << "Enter bin count: ";
    }
    size_t bin_count;
    in >> bin_count;
    data.bin_count=bin_count;

    if (prompt)
    {
        cerr << "Enter high: ";
    }
    size_t H;
    in >> H;

    return data;
}

void find_minmax (const vector <double>& numbers, double& min, double& max)
{

    if(numbers.size() != 0 )
    {

        min = numbers[0];
        max = numbers[0];
        for (double x : numbers)
        {
            if (x < min) min=x;
            if (x> max) max=x;
        }
    }
    return;
}

vector <size_t> make_histogram(Input input)
{

    double max = 0;
    double min = 0;
    find_minmax(input.numbers, min, max);
    vector<size_t> bins(input.bin_count);
    double bin_size = (max-min)/input.bin_count;
    for (double x : input.numbers)
    {
        bool found = false;
        for (size_t j = 0; (j < input.bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= x) && (x < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[input.bin_count-1]++;
        }
    }
    return bins;
}


void
show_histogram_text(vector<size_t>& bins,Input input)
{
    size_t C, k=0, z=0;
    size_t K=input.bin_count;
    double max_count=bins[0];
    for (size_t j=1; j< input.bin_count; j++)
    {
        if (bins[j]>max_count) max_count=bins[j];
    }
    C=input.H/K;
    size_t  height;
    for (size_t j=0; j < input.bin_count; j++)
    {
        while (z < C)
        {
            if (bins[j] < 100)
            {
                cout << " ";
            }
            if (bins[j] <10)
            {
                cout << " ";
            }
            if (z == 0)
            {
                cout << bins[j];
            }
            if (z > 0)
            {
                if (bins[j] >= 100)
                {
                    cout << "  " << " ";
                }
                if ((bins[j] < 100) && (bins[j] > 9))
                {
                    cout << "  ";
                }
                if (bins[j] < 10)
                {
                    cout << " ";
                }
            }
            cout << "|";

            height = bins[j];
            if (max_count > 76)
            {
                height = 76 * (static_cast<double>(bins[j])/max_count);
            }
            k=0;
            while (k != height)
            {
                cout << "*";
                k=k+1.0;
            }
            cout  << "\n";
            z=z+1.0;
        }
        z=0;
    }
    return;
}



void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end()
{
    cout << "</svg>\n";
}


void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'> " << text << "</text>";
}

string make_info_text()
{
    stringstream buffer;
    long unsigned int info;
    DWORD mask = 0x0000ffff;
    info = GetVersion();
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    DWORD maskk = 0x00ff;
    DWORD version_major = maskk & version;
    DWORD version_minor = version >> 8;

    buffer << "Windows: " << version_major << "." << version_minor << " (build " << platform << ")" << "\n";
    DWORD numer = 256;
    LPDWORD pointer = &numer;
    char lpBuffer[numer];
    GetComputerNameA(lpBuffer,pointer);
    buffer << "Computer name: " << lpBuffer;
    return buffer.str();
}

void svg_rect(double x, double y, double width, double height, ostream& out, string stroke, string fill)
{
    cout << "<rect x='" << x <<"' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill <<"'/>";
}

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    size_t data_size = sizeof(items, item_size, item_count, ctx);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast <const char*> (items), data_size);
    return 0;
}

void
show_histogram_svg(const vector<size_t>& bins,Input input)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 700;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    double BLOCK_WIDTH = 10;
    double max_count=bins[0];
    for (size_t j=1; j< input.bin_count; j++)
    {
        if (bins[j] > max_count) max_count=bins[j];
    }
    if (max_count > 76) BLOCK_WIDTH=((IMAGE_WIDTH-TEXT_WIDTH) / max_count);
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    double top = 0;
    if( input.H < TEXT_BASELINE) input.H=TEXT_BASELINE;
    if( (input.H*input.bin_count) > IMAGE_HEIGHT) input.H = ((IMAGE_HEIGHT-TEXT_BASELINE) / input.bin_count);
    for (size_t bin : bins)
    {

        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, input.H, cout);
        top += input.H;
    }
    svg_text(0,top + TEXT_BASELINE,make_info_text());
    svg_end();
}



Input
download(const string& address)
{
    stringstream buffer;

    CURL *curl = curl_easy_init();
    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_URL, write_data);
        res = curl_easy_perform(curl);
        curl_off_t speed;


        if (curl_easy_strerror(res) != "CURLE_OK")
        {
            cout << curl_easy_strerror(res) << "\n";
            exit(1);

        }

        res = curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD_T, &speed);
        cout << "Download speed "<< speed << " bytes/sec\n";
    }
    curl_easy_cleanup(curl);
    curl_global_init(CURL_GLOBAL_ALL);
    return read_input(buffer, false);
}
