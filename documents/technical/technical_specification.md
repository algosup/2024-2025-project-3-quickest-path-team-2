# Technical Specification Document

## Project Overview
**Project Name:** Quickest Path  
**Team:** Team 2  
**Date:** 2025-2025 

## Table of Contents
1. [Introduction](#introduction)
2. [Objectives](#objectives)
3. [Requirements](#requirements)
4. [System Architecture](#system-architecture)
5. [Data Handling](#data-handling)
6. [Algorithm](#algorithm)
7. [User Interface](#user-interface)
8. [Testing](#testing)
9. [Deployment](#deployment)
10. [Maintenance](#maintenance)

## Introduction
The Quickest Path project aims to develop a software solution that calculates the fastest path between two nodes based on data provided in a CSV file.

## Objectives
- Develop an efficient algorithm to find the quickest path.
- Ensure the software can handle large datasets.
- Provide a user-friendly interface for input and output.

## Project Folder Structure

```bash
2024-2025-project-3-quickest-path-team-2
├── .gitignore
├── bin
├── documents
│  ├── functional
│  ├── images
│  │  ├── functional
│  │  ├── management
│  │  ├── quality_Assurance
│  │  └── technical
│  ├── management
│  ├── quality_Assurance
│  ├── technical
│  │  └── technical_specification.md
│  └── user_Manual
├── README.md
├── src
│  ├── data
│  │  └── example.csv
│  ├── software.cpp
│  └── software.hpp
└── test
  └── test.cpp
``` 

## Conventions
There are the conventions to follow during the project.

### Naming Conventions
|   Type    |   Example     |   Convention name |
|:-         |:-             |:-                 |
|Folder     |folder_Name    |camel_Snake_Case   |
|File       |file_name      |snake_case         |
|DEFINE     |DEFINE_WELL    |CONSTANT_CASE      |
|typedef    |TPDF_STRING    |CONSTANT_CASE      |
|const      |BestConstEver  |PascalCase         |
|variable   |bestVarEver    |camelCase          |
|function   |good_function()|snake_case         |
|struct     |s_Struct       |camel_Snake_Case   |


> [!WARNING]  
> The types **DEFINE** and **typedef** uses the same convention, however typedef have for the first word an abbreviation then indicate the type used.

>[!CAUTION]
> Each structure have to have in their name the pre-fix "s_".

### Files Conventions
>[!NOTE]
> Each .cpp file have to be joined with it's equivalent named .hpp, for instance if the file software.cpp is created the file software.hpp **HAVE** to be created.

There is an example to use the different files.


```cpp
software.cpp
    #include "software.hpp"
    #define NICE_TEXT = "Hello,"


    int declare_the_function(int bestIntEver) {
        int newBestIntEver = bestIntEver;
        newBestIntEver += bestIntEver;
        return newBestIntEver;
    }

    void print_some_text(string NICE_TEXT) {
        if (NICE_TEXT != "\0") {
            std::cout << NICE_TEXT << " world!" << std::endl;
        }
        sdt::cout << "NICE_TEXT is empty." << std::endl;
    }
```
>[!IMPORTANT]
>The .cpp file is only used to implement the logical interaction in.
> 
```cpp
software.hpp
    #pragma once
    #include <iostream>
    
    typedef struct Student{
        string name;
        unsigned short age;
    } s_Student;

    /*
        This function double the value of itself.
        params:
            int bestIntEver
        return: 
            int newBestIntEver
    */
    int declare_the_function(int bestIntEver);
    
    /*
        Permit the print the text given as parameter.
        params:
            string niceText;
    */
    void print_some_text(string niceText);
```
>[!CAUTION]
>The .hpp file permit only to declare functions and comment the utility of each ones, giving also the parameters and what it return.

> [!TIP]
> ``` cpp
> #pragma once
> ```
> Is a preprocessor directive used to prevent header files from being included multiple times.


## Requirements
### Functional Requirements
- Import data from a CSV file.
- Calculate the quickest path between two nodes.
- Display the results to the user.

### Non-Functional Requirements
- Performance: The software should process data efficiently.
- Usability: The interface should be intuitive and easy to use.
- Scalability: The system should handle increasing amounts of data.

## System Architecture
### Overview
- **Input:** CSV file containing node connections and times.
- **Processing:** Algorithm to calculate the quickest path.
- **Output:** Display of the quickest path and time.

### Components
1. **Data Importer:** Reads and parses the CSV file.
2. **Path Calculator:** Implements the algorithm to find the quickest path.
3. **User Interface:** Allows users to input nodes and view results.

## Data Handling
### CSV File Format
- **Columns:** ID_1, ID_2, Time
- **Example:**
    ```
    ID_1,ID_2,Time
    1,2,1000
    2,3,1500
    ```

### Data Validation
- Ensure all rows have valid numeric values.
- Check for missing or duplicate entries.

## Algorithm
### Description
Describe the algorithm used to find the quickest path, such as Dijkstra's or A* algorithm.

### Pseudocode
Provide pseudocode for the algorithm.

## User Interface
### Input
- Text fields for entering the start and end nodes.
- Button to trigger the calculation.

### Output
- Display the quickest path and total time.
- Option to view the path details.

## Testing
### Unit Tests
- Test data import functionality.
- Test path calculation with various datasets.

### Integration Tests
- Ensure all components work together seamlessly.

### Performance Tests
- Measure the time taken to process large datasets.

## Deployment
### Environment
- Specify the required software and hardware.

### Installation
- Provide steps to install and configure the software.

## Maintenance
### Updates
- Outline the process for updating the software.

### Support
- Provide contact information for technical support.
