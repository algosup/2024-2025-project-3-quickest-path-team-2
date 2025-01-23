#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

#include "graph.hpp"
#include <string>
#include <atomic>
#include <unordered_set>

/**
 * @brief Preprocess the data from a CSV file and store them in a graph.
 * 
 * @param filePath Path to the CSV file.
 * @param maxLines Maximum number of lines to process (0 = all lines).
 * @param graph Reference to the graph in which the data are stored.
 * @return true if the preprocessing is successful, false otherwise.
 */
bool preprocess_data(const std::string& filePath, int maxLines, Graph& graph);

#endif // PREPROCESSING_HPP
