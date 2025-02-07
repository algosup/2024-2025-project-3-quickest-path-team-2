#include "includes/preprocessing.hpp"

/**
 * Processes a chunk of the file to extract and store graph edges.
 * 
 * @param fileData Pointer to the start of the file data in memory.
 * @param fileSize Size of the file data.
 * @param graph Reference to the Graph object where edges will be added.
 * @param seenConnections Map to track already processed connections.
 * @param maxId Atomic integer to keep track of the maximum node ID.
 * @param maxLines Maximum number of lines to process (if <= 0, process all lines).
 */
void process_chunk(
    const char* fileData,
    size_t fileSize,
    Graph& graph,
    TPDF_CONNECTIONS& seenConnections,
    std::atomic<int>& maxId,
    int maxLines
) {
    const char* fileEnd = fileData + fileSize;
    const char* lineStart = fileData;
    int lineCount = 0;

    // Process each line in the chunk
    while (lineStart < fileEnd && (maxLines <= 0 || lineCount < maxLines)) {
        const char* lineEnd = std::find(lineStart, fileEnd, '\n');
        if (lineEnd == fileEnd) {
            break; // End of file
        }

        // Extract the line as a string
        std::string line(lineStart, lineEnd - lineStart);
        lineStart = lineEnd + 1; // Move to the next line
        lineCount++;

        // Parse the line into landmarkA, landmarkB, and time
        std::istringstream ss(line);
        int landmarkA, landmarkB, time;
        char delimiter;

        // Check if the line is well-formed
        if (!(ss >> landmarkA >> delimiter >> landmarkB >> delimiter >> time) || delimiter != ',') {
            std::cerr << "Skipping malformed line: " << line << std::endl;
            continue;
        }

        // Validate the data
        if (landmarkA <= 0 || landmarkB <= 0 || time <= 0 || landmarkA == landmarkB) {
            std::cerr << "Skipping invalid data: " << line << std::endl;
            continue;
        }

        // Skip if the connection has already been processed
        if (seenConnections[landmarkA].count(landmarkB) > 0 || seenConnections[landmarkB].count(landmarkA) > 0) {
            continue;
        }

        // Add the edge to the graph and mark the connection as seen
        graph.add_edge(landmarkA, landmarkB, time);
        seenConnections[landmarkA].insert(landmarkB);
        seenConnections[landmarkB].insert(landmarkA);

        // Update the maximum node ID
        maxId.store(std::max(maxId.load(), (int)std::max(landmarkA, landmarkB)));
    }

    std::cout << "Processed " << lineCount << " lines." << std::endl;
}

/**
 * Preprocesses the data from the input file and builds the graph.
 * 
 * @param filePath Path to the input CSV file.
 * @param maxLines Maximum number of lines to process (if <= 0, process all lines).
 * @param graph Reference to the Graph object to be populated.
 * @return True if preprocessing is successful, otherwise throws an exception.
 */
bool preprocess_data(const std::string& filePath, int max_lines, Graph& graph) {
    TPDF_CONNECTIONS seenConnections;
    std::atomic<int> maxId(0);

#ifdef _WIN32
    HANDLE fileHandle = CreateFileA(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Error: Impossible to open the CSV file: " + filePath);
    }

    DWORD fileSize = GetFileSize(fileHandle, NULL);
    HANDLE fileMapping = CreateFileMapping(fileHandle, NULL, PAGE_READONLY, 0, fileSize, NULL);
    if (!fileMapping) {
        CloseHandle(fileHandle);
        throw std::runtime_error("Error: Failed to create file mapping for " + filePath);
    }

    char* fileData = static_cast<char*>(MapViewOfFile(fileMapping, FILE_MAP_READ, 0, 0, fileSize));
    if (!fileData) {
        CloseHandle(fileMapping);
        CloseHandle(fileHandle);
        throw std::runtime_error("Error: Failed to map the CSV file: " + filePath);
    }
#else
    int fd = open(filePath.c_str(), O_RDONLY);
    if (fd == -1) {
        throw std::runtime_error("Error: Impossible to open the CSV file: " + filePath);
    }

    size_t fileSize = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    char* fileData = static_cast<char*>(mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, fd, 0));
    if (fileData == MAP_FAILED) {
        close(fd);
        throw std::runtime_error("Error: Failed to mmap the CSV file: " + filePath);
    }
#endif

    std::cout << "File mapped successfully. Size: " << fileSize << " bytes." << std::endl;

    // Process the file
    process_chunk(fileData, fileSize, graph, seenConnections, maxId, max_lines);

    // Clean up
#ifdef _WIN32
    UnmapViewOfFile(fileData);
    CloseHandle(fileMapping);
    CloseHandle(fileHandle);
#else
    munmap(fileData, fileSize);
    close(fd);
#endif

    return true;
}

int get_max_lines(const fs::path& dataFolderPath) {
    int maxLines = 0;
    for (const auto& entry : fs::directory_iterator(dataFolderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".csv") {
            std::ifstream file(entry.path());
            if (file.is_open()) {
                maxLines += std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
                file.close();
            }
        }
    }
    return maxLines;
}