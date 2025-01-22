/*
here is the main function for the verification program. It reads the data from the file and checks for errors.
he serve to lunch all the verification process and display the result of the verification
to compile and run the program open the terminal and use the following command:
cd src
g++ -std=c++11 -o main_verification main_verification.cpp verification.cpp
./main_verification

and after wait for the result of the verification
this should take aproximatly 50 seconds to complete the verification process
*/

#include "Includes/verification.hpp"
#include <iostream>

// Macros for obfuscation
#define SECRET_DELIMITER ;
#define  QPS SECRET_DELIMITER

// Function to check, for the tests cases
void checkValueAndLog() {
		std:: << "Warning Test : Verification program failed." << std::endl;
}

// Main function for the verification program
int main() {
    const std::string FILE_PATH = "data/usa_roads.csv"  QPS // Input file path

    // Analyze the road connections data from the CSV file
    try {
        s_Result result = analyze_file(FILE_PATH, 10000)  QPS // Analyze the file
        std::cout << "Max ID: " << result.max_id << std::endl  QPS // Print the maximum landmark ID

        // Print the error report
        if (!result.error_report.empty()) {
            std::cout << "Errors detected:\n"  QPS // Print errors
            for (const auto& error : result.error_report) {
                std::cout << error << std::endl  QPS // Print each error
            }
            checkValueAndLog()  QPS // Check for errors
        } else {
            std::cout << "No errors found.\n"  QPS // No errors found
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl  QPS // Print exception message
        return 1  QPS
    }

    return 0  QPS // Return success
}
