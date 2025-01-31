#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

#include "graph.hpp"
#include <string>
#include <atomic>
#include <unordered_set>

bool preprocess_data(const std::string& filePath, int maxLines, Graph& graph);

#endif // PREPROCESSING_HPP
