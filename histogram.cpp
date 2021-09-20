#include "histogram.h.h"
#include <iostream>
#include <conio.h>
#include <math.h>
#include <string>
#include <windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

vector<double>
input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

void
find_minmax(const vector<double>& numbers, double& min, double& max)
{
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
}

vector<size_t>
make_histogram(const vector<double>& numbers,size_t bin_count, size_t number_count, double& min, double& max)
{   vector<size_t> result(bin_count);
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
                result[j]++;
                found = true;
            }
        }
        if (!found)
        {
            result[bin_count-1]++;
        }

    }
    return result;
}


void
show_histogram_text(vector<size_t>& bins, size_t bin_count, int H)
{
    size_t C, k=0, z=0;
    int K=bin_count;
    double max_count=bins[0];
    for (size_t j=1; j< bin_count; j++)
    {
        if (bins[j]>max_count) max_count=bins[j];
    }
    C=H/K;
    size_t  height;
    for (size_t j=0; j < bin_count; j++)
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

}



void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}


void
svg_text(double left, double baseline, string text) {
     cout << "<text x='" << left << "' y='" << baseline << "'> " << text << "</text>";
}



void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout << "<rect x='" << x <<"' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill <<"'/>";
}

void
show_histogram_svg(const vector<size_t>& bins, int H, size_t bin_count) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 700;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    double BLOCK_WIDTH = 10;
    double max_count=bins[0];
    for (size_t j=1; j< bin_count; j++)
    {
        if (bins[j] > max_count) max_count=bins[j];
    }
    if (max_count > 76) BLOCK_WIDTH=((IMAGE_WIDTH-TEXT_WIDTH) / max_count);
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    double top = 0;
    if( H < TEXT_BASELINE) H=TEXT_BASELINE;
    if( (H*bin_count) > IMAGE_HEIGHT) H = (IMAGE_HEIGHT / bin_count);
for (size_t bin : bins) {

    const double bin_width = BLOCK_WIDTH * bin;
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
    svg_rect(TEXT_WIDTH, top, bin_width, H);
    top += H;
}
    svg_end();
}
