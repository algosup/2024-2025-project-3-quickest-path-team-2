#include "includes/graph.hpp"
#include "includes/preprocessing.hpp"
#include "includes/main.hpp"
#include <iostream>
#include <chrono>
#include <iomanip> // For std::setprecision

int choice;
long long totalTime;
bool preprocess_done = false;
bool graph_loaded = false;
bool data_loaded = false;
bool data_file_is_empty = false;
fs::path dataFolderPath = fs::current_path().parent_path() / "data";
s_File_Data files_data_storage[100]; 


bool check_data_folder(fs::path dataFolderPath) {
    if (!fs::exists(dataFolderPath) || fs::is_empty(dataFolderPath)) {
        if (!fs::exists(dataFolderPath)) {
            cout << "Data folder does not exist\n";
        }
        if (fs::is_empty(dataFolderPath)) {
            cout << "Data folder is empty\n";
        }
        return true;
    }
    return false;
}

int get_amount_of_csv(fs::path dataFolderPath) {
    int csv_count = 0;
    for (const auto& entry : fs::directory_iterator(dataFolderPath)) {
        s_File_Data file_data;
        if (fs::is_regular_file(entry) && entry.path().extension() == ".csv") {
            file_data.filename = entry.path().filename().string();
            file_data.path = entry.path().string();
            csv_count++;
        }
    }
    return csv_count;
}

s_File_Data save_csv_files(fs::path dataFolderPath, s_File_Data files_data_storage[]) {
    int i = 0;
    for (const auto& entry : fs::directory_iterator(dataFolderPath)) {
        if (entry.path().extension() == ".csv") {
            files_data_storage[i].filename = entry.path().filename().string();
            files_data_storage[i].path = entry.path().string();
            i++;
        }
    }
    return files_data_storage[i];
}

Graph graph;

int main(void) {
    data_file_is_empty = check_data_folder(dataFolderPath);
    if (data_file_is_empty) {
        cout << "Data folder is empty. Please insert .csv file into the data folder\n";
        return 1;
    }
    if (get_amount_of_csv(dataFolderPath) == 0) {
        cout << "No .csv file found in the data folder\n";
        return 1;
    }
    else {
        save_csv_files(dataFolderPath, files_data_storage);
    }
    
    int file_number = 0;
    int source = 0;
    int target = 0;
    do {
        cout << "----"
                << " |Menu| "
                << "----\n";
        cout << "0. Exit\n";
        cout << "1. See the list of .csv files\n";
        cout << "2. Load .csv file\n";
        cout << "3. Find the shortest path\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 0:
                cout << "Exiting the program\n";
                break;
            case 1:
                for (int i = 0; i < get_amount_of_csv(dataFolderPath); i++) {
                    cout << i+1 << ". " << files_data_storage[i].filename << "\n";
                }
                break;
            case 2:
                cout << "Enter the number of the .csv file you want to load: ";
                cin >> file_number;
                cout << "Loading " << files_data_storage[file_number-1].filename << "...\n";
                // delete &graph; TODO
                try {
                    std::cout << "Starting preprocessing..." << std::endl;

                    auto startPreprocess = std::chrono::steady_clock::now();
                    preprocess_data(files_data_storage[file_number-1].path, get_max_lines(dataFolderPath), graph);
                    auto endPreprocess = std::chrono::steady_clock::now();
                    auto preprocessDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endPreprocess - startPreprocess);
                    std::cout << "Preprocessing completed in " << preprocessDuration.count() << " ms" << std::endl;
                    preprocess_done = true;

                    // LOAD API TODO
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            case 3: {
                if (!preprocess_done) {
                    cout << "Please load the .csv file first\n";
                    break;
                }
                cout << "Enter the source node: ";
                cin >> source;
                cout << "Enter the target node: ";
                cin >> target;
                cout << "Finding the shortest path from " << source << " to " << target << "...\n";
                if (source < 0 || source > graph.get_max_node_id() || target < 0 || target > graph.get_max_node_id()) {
                    std::cerr << "Error: Source or target node is out of bounds." << std::endl;
                    return 1;
                }
                auto startPath = std::chrono::steady_clock::now();
                std::vector<int> path = graph.shortest_path(source, target, totalTime);
                auto endPath = std::chrono::steady_clock::now();
                auto pathDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endPath - startPath);
                if (path.empty()) {
                    std::cout << "No path found between " << source << " and " << target << "." << std::endl;
                } else {
                    std::cout << "Shortest path found:\n";
                    for (size_t i = 0; i < path.size(); ++i) {
                        std::cout << path[i];
                        if (i != path.size() - 1) std::cout << " -> ";
                    }
                    std::cout << std::endl;
                }
                std::cout << "Path calculation took " << pathDuration.count() << " ms." << std::endl;
                break;
            }
            default:
                cout << "Invalid choice\n";
                break;
        }
    } while (choice != 0);
    
    
    //     auto preprocessDuration = std::chrono::duration_cast<std::chrono::seconds>(endPreprocess - startPreprocess);
    //     std::cout << "\nPreprocessing completed in " << preprocessDuration.count() << " seconds." << std::endl;

    //     // Verify the graph
    //     int maxNode = graph.get_max_node_id();
    //     std::cout << "Graph loaded with max node ID: " << maxNode << std::endl;

    //     // Prompt user for source and target nodes
    //     int source, target;
    //     std::cout << "Enter the source node: ";
    //     std::cin >> source;
    //     std::cout << "Enter the target node: ";
    //     std::cin >> target;

    //     // Validate the nodes
    //     if (source < 0 || source > maxNode || target < 0 || target > maxNode) {
    //         std::cerr << "Error: Source or target node is out of bounds." << std::endl;
    //         return 1;
    //     }

    //     std::cout << "Finding shortest path from " << source << " to " << target << "..." << std::endl;

    //     // Calculate the shortest path
    //     long long totalTime = 0;  // Use long long for total time
    //     auto startPath = std::chrono::steady_clock::now();
    //     std::vector<int> path = graph.shortest_path(source, target, totalTime);
    //     auto endPath = std::chrono::steady_clock::now();

    //     auto pathDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endPath - startPath);

    //     // Display the results
    //     if (path.empty()) {
    //         std::cout << "No path found between " << source << " and " << target << "." << std::endl;
    //     } else {
    //         std::cout << "Shortest path found with total time " << totalTime << ":\n";
    //         for (size_t i = 0; i < path.size(); ++i) {
    //             std::cout << path[i];
    //             if (i != path.size() - 1) std::cout << " -> ";
    //         }
    //         std::cout << std::endl;
    //     }

    //     std::cout << "Path calculation took " << pathDuration.count() << " ms." << std::endl;

    // } catch (const std::exception& e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    // }

    return 0;
}