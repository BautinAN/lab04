#ifndef HISTOGRAM_H__H_INCLUDED
#define HISTOGRAM_H__H_INCLUDED
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
input_numbers(size_t count);

void
find_minmax(const vector<double>& numbers, double& min, double& max);

vector<size_t>
make_histogram(const vector<double>& numbers,size_t bin_count, size_t number_count, double& min, double& max);

void
show_histogram_text(vector<size_t>& bins, size_t bin_count, int H);

void
svg_begin(double width, double height);

void
svg_end();

void
svg_text(double left, double baseline, string text);

void svg_rect(double x, double y, double width, double height, string stroke ="indigo", string fill = "lawngreen");

void
show_histogram_svg(const vector<size_t>& bins, int H, size_t bin_count);


#endif // HISTOGRAM_H__H_INCLUDED
