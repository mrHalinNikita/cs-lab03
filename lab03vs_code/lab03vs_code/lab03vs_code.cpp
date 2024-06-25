#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"

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

void svg_text(double left, double baseline, string text, double font_size) {
    cout << "<text x='" << left << "' y='" << baseline << "' font-size='" << font_size << "'>'" << text << "'</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'></rect>\n";
}

void test_height(size_t& height_bin, size_t bins_count, const size_t IMAGE_HEIGHT) {
    if (height_bin * bins_count > IMAGE_HEIGHT) {
        height_bin = (IMAGE_HEIGHT / bins_count);
    }
}

void show_histogram_svg(const vector<size_t> bins, size_t height_bin) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 700;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BLOCK_WIDTH = 10;
    const auto HISTOGRAM_MAX_WIDTH = IMAGE_WIDTH - TEXT_LEFT - TEXT_WIDTH;
    size_t max_bin = bins[0];
    test_height(height_bin, bins.size(), IMAGE_HEIGHT);
    for (size_t bin : bins) {
        if (max_bin < bin) max_bin = bin;
    }
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        size_t height = bin;
        if (max_bin * BLOCK_WIDTH > HISTOGRAM_MAX_WIDTH) {
            height = HISTOGRAM_MAX_WIDTH * (static_cast<double> (bin) / (max_bin * BLOCK_WIDTH));
        }
        const double bin_width = BLOCK_WIDTH * height;
        double font_size = height_bin / 2;
        svg_text(TEXT_LEFT, top + height_bin / 2, to_string(bin), font_size);
        svg_rect(TEXT_WIDTH + height_bin, top, bin_width, height_bin, "#474A51", "#DC143C");
        top += height_bin;
    }
    svg_end();
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
