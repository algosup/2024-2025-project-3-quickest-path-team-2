#include "includes/utils.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + filePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
