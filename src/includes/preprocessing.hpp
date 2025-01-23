#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

#include "graph.hpp"
#include <string>
#include <atomic>
#include <unordered_set>

/**
 * @brief Prétraite les données d'un fichier CSV et les stocke dans un graphe.
 * 
 * @param filePath Chemin du fichier CSV.
 * @param maxLines Nombre maximum de lignes à traiter (0 = toutes les lignes).
 * @param graph Référence au graphe dans lequel les données sont stockées.
 * @return true si le prétraitement est réussi, false sinon.
 */
bool preprocess_data(const std::string& filePath, int maxLines, Graph& graph);

#endif // PREPROCESSING_HPP
