#include "includes/utils.hpp"
#include <iostream>

void display_progress_bar(size_t current, size_t total) {
    const int barWidth = 50;
    float progress = static_cast<float>(current) / total;
    int position = static_cast<int>(progress * barWidth);

    std::cout << "\r[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < position) std::cout << "=";
        else if (i == position) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "% (" << current << "/" << total << ")";
    std::cout.flush();
}
