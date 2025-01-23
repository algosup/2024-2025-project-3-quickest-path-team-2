#include "crow_all.h"
#include <fstream>
#include <sstream>

#define STATIC_DIR "../static/"

// Fonction pour lire un fichier
std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    crow::SimpleApp app;

    // Route pour la page d'accueil
    CROW_ROUTE(app, "/")([]() {
        // Charger le fichier index.html
        std::string filePath = STATIC_DIR "index.html";
        try {
            return crow::response(readFile(filePath));
        } catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
    });

    CROW_ROUTE(app, "/api/shortest-path/").methods(crow::HTTPMethod::GET)
        ([](const crow::request& req, crow::response& res) {
            auto landmark_1 = req.url_params.get("landmark_1");
            auto landmark_2 = req.url_params.get("landmark_2");
            crow::json::wvalue response;
            if (landmark_1 && landmark_2) {

                std::vector<int> path = {1, 250, 200, 1000};
                int total_time = 65429;

                response["path"] = path;
                response["time"] = total_time;
                res.code = crow::status::OK;
            } else {
                response["status"] = "error";
                response["message"] = "Missing parameters";
                res.code = crow::status::BAD_REQUEST;
            }
            res.set_header("Content-Type", "application/json");
            res.write(response.dump());
            res.end();
        });

    CROW_ROUTE(app, "/api/shortest-path/json").methods(crow::HTTPMethod::GET)
        ([](const crow::request& req, crow::response& res) {
            auto landmark_1 = req.url_params.get("landmark_1");
            auto landmark_2 = req.url_params.get("landmark_2");
            crow::json::wvalue response;
            if (landmark_1 && landmark_2) {
                crow::json::wvalue::list paths;
                for (int i = 0; i < 100; i++) {
                    crow::json::wvalue path;
                    path["landmark_1"] = std::to_string(i + 1);
                    path["landmark_2"] = std::to_string(i + 1000);
                    path["time"] = 65429;
                    paths.push_back(path);
                }
                response["paths"] = std::move(paths);
                res.code = crow::status::OK;
                response["status"] = std::to_string(res.code);
            } else {
                response["status"] = "error";
                response["message"] = "Missing parameters";
                res.code = crow::status::BAD_REQUEST;
            }
            res.set_header("Content-Type", "application/json");
            res.write(response.dump());
            res.end();
        });

    CROW_ROUTE(app, "/api/shortest-path/xml").methods(crow::HTTPMethod::GET)
    ([](const crow::request& req, crow::response& res) {
        auto landmark_1 = req.url_params.get("landmark_1");
        auto landmark_2 = req.url_params.get("landmark_2");
        std::ostringstream oss;
        if (landmark_1 && landmark_2) {
            oss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                << "<paths>\n";
            for (int i = 0; i < 100; i++) {
                oss << "\t<path>\n"
                    << "\t\t<landmark_1>" << (i + 1) << "</landmark_1>\n"
                    << "\t\t<landmark_2>" << (i + 1000) << "</landmark_2>\n"
                    << "\t\t<time>65429</time>\n"
                    << "\t</path>\n";
            }
            oss << "</paths>";
            res.code = crow::status::OK;
        } else {
            oss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                << "<response>\n"
                << "\t<status>error</status>\n"
                << "\t<message>Missing parameters</message>\n"
                << "</response>";
            res.code = crow::status::BAD_REQUEST;
        }
        res.set_header("Content-Type", "application/xml");
        res.write(oss.str());
        res.end();
    });


    // Démarrer le serveur
    app.port(8080).multithreaded().run();
    return 0;
}



