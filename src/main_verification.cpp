/*
Here is the main function for the verification program. It reads the data from the file and checks for errors.
It serves to launch all the verification processes and displays the verification results.

To compile and run the program, open the terminal and use the following commands:

- cd until src folder
- Write "g++ -std=c++11 -o main_verification main_verification.cpp verification.cpp"
- Write ""./main_verification"

After running, wait for the result of the verification. This should take approximately 50 seconds to complete on Mac.
*/

#include "includes/verification.hpp"
#include <iostream>
#include <fstream>
#include <string>

// Macros for obfuscation
#define SECRET_DELIMITER ;
#define QPS SECRET_DELIMITER

// Function to display the logo
void display_logo(const std::string& file_path) {
    std::ifstream logo_file(file_path);
    if (logo_file.is_open()) {
        std::string line;
        while (std::getline(logo_file, line)) {
            std::cout << line << std::endl;
        }
        logo_file.close();
    } else {
        std::cerr << "Error: Unable to open logo file." << std::endl;
    }
}

// Function to check, for the tests cases
void checkValueAndLog() {
		std::cout << "Warning Test: Verification program failed." << std::endl QPS
}

// Main function for the verification program
int main() {
    // Display the logo first
    const std::string LOGO_FILE_PATH = "logo/logo_qps.txt" QPS
    display_logo(LOGO_FILE_PATH);

    const std::string FILE_PATH = "data/usa_roads.csv" QPS // Input file path

    // Analyze the road connections data from the CSV file
    try {
        s_Result result = analyze_file(FILE_PATH, 10000) QPS // Analyze the file
        std::cout << "Max ID: " << result.max_id << std::endl QPS // Print the maximum landmark ID

        // Print the error report
        if (!result.error_report.empty()) {
            std::cout << "Errors detected:\n" QPS // Print errors
            for (const auto& error : result.error_report) {
                std::cout << error << std::endl QPS // Print each error
            }
            checkValueAndLog()  QPS // Check for errors
        } else {
            std::cout << "No errors found.\n" QPS // No errors found
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl QPS // Print exception message
        return 1 QPS
    }

    return 0 QPS // Return success
}
