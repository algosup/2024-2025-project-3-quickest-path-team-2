#include "api.hpp"
#include "../includes/graph.hpp" 
#include "crow_all.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <mutex>

#define STATIC_DIR "static/"

std::mutex cache_mutex;
std::unordered_map<std::string, std::string> file_cache;

// Function to read a file and return its content as a string, with caching
std::string readFile(const std::string& filePath) {
    std::lock_guard<std::mutex> lock(cache_mutex);
    auto it = file_cache.find(filePath);
    if (it != file_cache.end()) {
        return it->second;
    }
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file_cache[filePath] = content;
    return content;
}

// Function to start the API
void start_api(Graph& graph) {
    crow::SimpleApp app;

    // Route for the home page
    CROW_ROUTE(app, "/")([]() {
        try {
            return crow::response(readFile(STATIC_DIR "index.html"));
        } catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
    });

    // Route for serving static files
    CROW_ROUTE(app, "/static/<string>")([](const crow::request&, std::string fileName) {
        try {
            return crow::response(readFile(STATIC_DIR + fileName));
        } catch (const std::exception& e) {
            return crow::response(500, "Error reading file: " + std::string(e.what()));
        }
    });

    // Route for computing the shortest path
    CROW_ROUTE(app, "/api/shortest-path/").methods(crow::HTTPMethod::Get)([&graph](const crow::request& req) {
        const char* source = req.url_params.get("source");
        const char* target = req.url_params.get("target");
        const char* format = req.url_params.get("format");

        crow::json::wvalue response_json;

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

        uint32_t totalTime = 0;
        std::vector<int> path;
        try {
            path = graph.shortest_path(src, tgt, totalTime);
        } catch (const std::exception& e) {
            response_json["status"] = "error";
            response_json["message"] = std::string("Error computing shortest path: ") + e.what();
            return crow::response(500, response_json);
        }

        if (path.empty()) {
            response_json["status"] = "error";
            response_json["message"] = "No path found between the given nodes.";
            return crow::response(404, response_json);
        }

        if (!format) format = "json";

        if (std::string(format) == "simplify") {
            response_json["status"] = "success";
            response_json["path"] = path;
            response_json["time"] = totalTime;
            return crow::response(200, response_json);
        }

        if (std::string(format) == "json") {
            crow::json::wvalue path_array;
            for (size_t i = 0; i < path.size() - 1; ++i) {
                crow::json::wvalue segment;
                segment["landmark_1"] = path[i];
                segment["landmark_2"] = path[i + 1];
                segment["time"] = graph.get_travel_time(path[i], path[i + 1]);
                path_array[i] = std::move(segment);
            }

            response_json["status"] = "success";
            response_json["path"] = std::move(path_array);
            return crow::response(200, response_json);
        }

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

            crow::response res(200);
            res.set_header("Content-Type", "application/xml");
            res.body = xml_response.str();
            return res;
        }

        response_json["status"] = "error";
        response_json["message"] = "Invalid format specified";
        return crow::response(400, response_json);
    });

    std::cout << "Starting API on port 8080..." << std::endl;
    app.port(8080).multithreaded().run();
}
