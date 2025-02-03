#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

typedef struct file_data {
    string filename;
    string path;
} s_File_Data;


/**
* Function to check if the data folder is empty
* @param args fs::path
* @return bool
*/
bool check_data_folder(fs::path dataFolderPath);

/**
* Function to get the amount of .csv files in the data folder
* @param args fs::path
* @return int
*/
int get_amount_of_csv(fs::path dataFolderPath);

/** 
* Function to save the .csv files in the data folder
* @param args fs::path, s_File_Data[]
* @return s_File_Data
*/
s_File_Data save_csv_files(fs::path dataFolderPath, s_File_Data files_data_storage[]);
#endif