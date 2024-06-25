#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"

using namespace std;

vector<double>
input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

vector<size_t> make_histogram(const vector<double> numbers, size_t bin_count) {
    double min, max;
    find_minmax(numbers, min, max);
    vector<size_t>bins(bin_count, 0);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; j < (bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
            }
        }
        if (!found) {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}

void show_histogram_text(vector<size_t>bins) {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
    size_t max_bin = bins[0];
    for (size_t bin : bins) {
        if (max_bin < bin) {
            max_bin = bin;
        }
    }
    for (size_t bin : bins) {
        size_t height = bin;
        if (max_bin > MAX_ASTERISK) {
            height = MAX_ASTERISK * (static_cast<double> (bin) / max_bin);
        }

        if (bin < 100) cout << " ";
        if (bin < 10) cout << " ";
        cout << bin;
        cout << "|";
        for (size_t i = 0; i < height; i++) {
            cout << "*";
        }
        cout << '\n';
    }
}

int main() {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    double min, max;
    find_minmax(numbers, min, max);

    size_t height_historgam;
    cerr << "Enter height historgram:";
    cin >> height_historgam;

    const auto bins = make_histogram(numbers, bin_count);

    show_histogram_svg(bins, height_historgam);

    return 0;
}
