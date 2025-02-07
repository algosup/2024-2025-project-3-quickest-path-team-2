#include "api.hpp"
#include "../includes/graph.hpp" 
#include "crow_all.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>

#define STATIC_DIR "static/"

std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + filePath);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void start_api(Graph& graph) {
    crow::SimpleApp app;

    // Route pour la page d'accueil
    CROW_ROUTE(app, "/")([]() {
        try {
            return crow::response(readFile(STATIC_DIR "index.html"));
        } catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
    });

    // Route pour les fichiers statiques
    CROW_ROUTE(app, "/static/<string>")([](const crow::request&, std::string fileName) {
        try {
            return crow::response(readFile(STATIC_DIR + fileName));
        } catch (const std::exception& e) {
            return crow::response(500, "Erreur lecture fichier: " + std::string(e.what()));
        }
    });

    // Route pour calculer le plus court chemin
    CROW_ROUTE(app, "/api/shortest-path/").methods(crow::HTTPMethod::GET)([&graph](const crow::request& req) {
        const char* source = req.url_params.get("source");
        const char* target = req.url_params.get("target");
        const char* format = req.url_params.get("format");

        crow::json::wvalue response_json;

        // Vérification des paramètres
        if (!source || !target) {
            response_json["status"] = "error";
            response_json["message"] = "Missing parameters: source and target are required.";
            return crow::response(400, response_json);
        }

        int src, tgt;
        try {
            src = std::stoi(source);
            tgt = std::stoi(target);
        } catch (const std::exception&) {
            response_json["status"] = "error";
            response_json["message"] = "Invalid source or target parameters.";
            return crow::response(400, response_json);
        }

        // Calcul du plus court chemin
        uint32_t totalTime = 0;
        std::vector<int> path;
        try {
            path = graph.shortest_path(src, tgt, totalTime);
        } catch (const std::exception& e) {
            response_json["status"] = "error";
            response_json["message"] = std::string("Error computing shortest path: ") + e.what();
            return crow::response(500, response_json);
        }

        // Vérification si un chemin a été trouvé
        if (path.empty()) {
            response_json["status"] = "error";
            response_json["message"] = "No path found between the given nodes.";
            return crow::response(404, response_json);
        }

        if (!format) format = "json";

        crow::response res;

        // Format simplifié
        if (std::string(format) == "simplify") {
            response_json["status"] = "success";
            response_json["path"] = std::move(path);
            response_json["time"] = totalTime;
            res = crow::response(200, response_json);
            return res;
        }

        // Format JSON détaillé
        if (std::string(format) == "json") {
            crow::json::wvalue detailed_path;
            crow::json::wvalue path_array;

            for (size_t i = 0; i < path.size() - 1; ++i) {
                crow::json::wvalue step;
                step["landmark_1"] = path[i];
                step["landmark_2"] = path[i + 1];
                step["time"] = graph.get_travel_time(path[i], path[i + 1]);
                path_array[static_cast<int>(path_array.size())] = std::move(step);
            }

            detailed_path["status"] = "success";
            detailed_path["path"] = std::move(path_array);
            res = crow::response(200, detailed_path);
            return res;
        }

        // Format XML
        if (std::string(format) == "xml") {
            std::ostringstream xml_response;
            xml_response << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<paths>\n";
            for (size_t i = 0; i < path.size() - 1; ++i) {
                xml_response << "    <path>\n"
                            << "        <landmark_1>" << path[i] << "</landmark_1>\n"
                            << "        <landmark_2>" << path[i + 1] << "</landmark_2>\n"
                            << "        <time>" << graph.get_travel_time(path[i], path[i + 1]) << "</time>\n"
                            << "    </path>\n";
            }
            xml_response << "</paths>\n";

            res = crow::response(200);
            res.set_header("Content-Type", "application/xml");
            res.body = xml_response.str();
            return res;
        }

        // Format non supporté
        response_json["status"] = "error";
        response_json["message"] = "Invalid format specified";
        return crow::response(400, response_json);
    });

    std::cout << "Démarrage de l'API sur le port 8080..." << std::endl;
    app.port(8080).multithreaded().run();
}
