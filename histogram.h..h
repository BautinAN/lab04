#ifndef HISTOGRAM_H__H_INCLUDED
#define HISTOGRAM_H__H_INCLUDED
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

struct Input {
    size_t number_count;
    vector<double> numbers;
    size_t bin_count;
    size_t H;
};

vector<double>
input_numbers(istream& in, size_t count);

Input
read_input(istream& in, bool prompt);

void
find_minmax (const vector <double>& numbers, double& min, double& max);

vector<size_t>
make_histogram(Input input);

void
show_histogram_text(vector<size_t>& bins,Input input);

void
svg_begin(double width, double height);

void
svg_end();

void
svg_text(double left, double baseline, string text);

void svg_rect(double x, double y, double width, double height, string stroke ="indigo", string fill = "lawngreen");

void
show_histogram_svg(const vector<size_t>& bins,Input input);


#endif // HISTOGRAM_H__H_INCLUDED
