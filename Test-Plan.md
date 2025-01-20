<!-- PROJECT LOGO -->
<br />
<div alig="center">
    <h1 align="center"> Test Plan </h1>
    <p align="center">
        <strong> Quickest Path in C++ - Team 2's project</strong>
        <br />

</div>
</br>

<!-- TABLE OF CONTENTS -->

<details>
<summary>
      <h4 style="display: inline-block">Table of Contents</h4>
</summary>


 
</details>

## 1. Introduction

### 1.1 Purpose

The primary goal of this Test Plan is to define clear objectives and strategies for verifying the correctness, performance, and reliability of our C++-based path calculator software. 
By outlining our testing methodology, this document establishes the criteria by which we will determine if the project meets its functional and non-functional requirements. 
It further clarifies how testing outcomes will be measured and reported, ensuring transparency and accountability throughout the development lifecycle.

### 1.2 Project Overview

This project focuses on computing the quickest path between two landmarks within the United States. 
Implemented in C++, the application processes a large CSV file (*USA-roads.csv*) that contains landmark IDs and associated travel times. The system exposes a single REST API endpoint accepting a source and destination landmark, then returning the total travel time and the series of landmarks constituting the path. Given the data size of approximately 24 million nodes, performance optimization is paramount, and approximation heuristics are allowed as long as the travel time does not exceed 10% of the shortest possible route. 

Additionally, the project provides a data validation tool to confirm that the CSV file forms a Directed Acyclic Graph (DAG) and that the graph is fully connected. Verification of extremely large CSV files (e.g., up to 30 million lines) should ideally complete in about one minute. A progress bar in the command prompt will show the verification status, and if it remains stuck for more than 10 seconds, a warning is logged for potential issues.

```mermaid
flowchart LR
    A[USA-roads.csv] --> B[Data Validation Tool]
    B[Data Validation Tool] --> C[GraphBuilder]
    C[GraphBuilder] --> D[Pathfinding Logic]
    D[Pathfinding Logic] --> E[REST API Server]
    E[REST API Server] --> F[Client]
```

- **Test Hooks**  
  - *Unit Tests* on the Data Validation Tool, Graph Builder, and Pathfinding modules.  
  - *Integration Tests* once these modules are linked.  
  - *System Tests* when calling the REST API end-to-end to verify performance and correctness.

### 1.3 Testing Scope

All major functional components will be tested, including data ingestion, graph building, path calculation with approximation heuristics, and response delivery via the REST API. 
Automated tests will be run through GitHub Actions on every push to the `main` branch, ensuring continuous validation of new code. Specific performance tests at scale may require further configuration, especially for testing the system’s handling of 24+ million nodes and verifying CSV files of up to 30 million lines in ~1 minute. Any testing activities not covered by the existing CI environment or requiring specialized load-testing tools may be deferred until additional resources are available.

---

## 2. Test Strategy

### 2.1 Testing Levels

#### 2.1.1 Unit Testing 
   - Validates isolated functions (e.g., CSV parsing, adjacency matrix creation, Dijkstra’s pathfinding).  

#### 2.1.2 Integration Testing 
   - Ensures that individual components (data validation, graph building, pathfinding, REST API) interoperate smoothly.  

#### 2.1.3 System Testing
   - Verifies end-to-end functionality from CSV input to REST output.  
   - Checks overall performance, including the 1-second response target for a typical path query.

#### 2.1.4 Performance Testing
   - Confirms the system can handle large datasets within the required response time.  
   - Verifies CSV validation can complete in about 1 minute for up to 30 million lines.  
   - Monitors memory and CPU usage if feasible.

#### 2.1.5 API Testing
   - Specifically tests the REST API’s correctness, reliability, and error handling for normal and erroneous inputs.

### 2.2 Testing Types

#### 2.2.1 Functional Testing
   - Verifies that each feature (e.g., generating a path within 10% margin, correct JSON/XML format) meets the specified requirements.  

#### 2.2.2 Performance Testing
   - Ensures the system responds in under 1 second for typical queries.  
   - Confirms CSV verification can handle large files quickly (1 minute target for ~30M lines).  

#### 2.2.3 Data Integrity Testing 
   - Uses the validation tool to confirm that the CSV forms a proper DAG with no disconnected subgraphs or negative/zero travel times.  

#### 2.2.4 Regression Testing
   - Runs automatically after each push to detect if any previously working functionality has broken.

**Error Severity**  
- **Fatal errors** (via `checkValue(int actual, int expected)`)  
  Throw exceptions and halt the test. These must be fixed before release.  
- **Non-fatal errors** (via `checkAndLog(int actual, int expected)`)  
  Log warnings but let the test pipeline continue. These are tracked and should be resolved.

### 2.3 Testing Tools

- **C++17** for primary development.  
- **GitHub Actions** (Ubuntu-latest) for automated CI.   
- **cURL** or a custom C++ client for REST API testing (checking JSON vs. XML outputs).  
- **Additional Tools**:   Dedicated load-testing utilities for large-scale performance validation.

---

## 3. Test Environment

### 3.1 Hardware Requirements

- **CI Environment**: Ubuntu-latest runner on GitHub Actions.  
- **Local Environment**: Modern multi-core CPU (≥8 GB RAM) to mimic real usage.  
- **Network Constraints**: Minimal, since REST calls are typically localhost.

### 3.2 Software Requirements

- **Operating System**: Ubuntu-latest for CI. Tested on Windows 11 and macOS .  
- **Compiler**: g++ 9+ with build-essential for C++17.  
- **Libraries**: only STL 

---

## 4. Test Deliverables

### 4.1 Test Documentation

- **Test Cases**: Detailed descriptions of purpose, inputs, expected outputs, severity.  
- **CI Scripts**: GitHub Actions workflow (YAML) for building and running tests automatically.  
- **Sample Data**:  CSV files for checks.  

### 4.2 Test Reports
<!-- TO COMPLETE -->
- **CI Logs**: Pass/fail summaries, performance metrics, memory usage (if measured).  
- **Issue Tracker**: Document all high-priority or recurring bugs.  
- **Final Summary**: Conclusive stats on coverage, performance times, success rates.

---

## 5. Testing Areas

### 5.1 REST API Testing

- **Endpoints**: `/quickest_path_system?format=<json|xml>&landmark_1=<id>&landmark_2=<id>`  
- **Checks**:  
  1. Valid inputs produce a JSON/XML response with correct travel time and path.  
  2. Invalid inputs (e.g., missing parameters, nonexistent landmarks) produce appropriate HTTP error codes and messages.  
  3. Response must meet the 1-second performance requirement for typical queries.

### 5.2 Performance Testing

- **Response Times**: Must remain under 1 second for typical pathfinding queries on a standard laptop.  
- **Load / Stress**: If resources allow, test concurrent requests.  
- **CSV Verification**: In ideal conditions, verifying 30 million lines in ~1 minute. A progress bar indicates the state; if no progress after 10 seconds, warn the user.

### 5.3 Data Integrity Testing

- **Valid CSV**: Confirm the file is recognized as a DAG with no loops, no negative or zero edge weights, and full connectivity.  
- **Malformed CSV**: Missing landmarks, negative times, duplicates. The tool should either fail gracefully or log appropriate errors.  
- **Adjacency Matrix**: Confirm correctness of adjacency mapping, ensuring no contradictory or duplicate entries.

### 5.4 Path Calculation Testing

- **Correctness**: Use smaller, known graphs to confirm the path does not exceed 10% of the true shortest route.  
- **Heuristics**: Verify approximate solutions maintain the performance/time trade-off.  
- **Edge Cases**: Identical source/destination, incomplete data, extremely large node IDs, etc.

---

## 6. Test Cases
*load test case document*
<!-- ### 6.1 API Test Cases

1. **Valid Request**  
   - **Input**: `GET /quickest_path_system?format=json&landmark_1=1000&landmark_2=2000`  
   - **Expected**: 200 OK, JSON response with travel time + list of landmarks.  
   - **Time**: <1 second, with correct data structure.  

2. **Invalid Landmarks**  
   - **Input**: `GET /quickest_path_system?format=xml&landmark_1=-1&landmark_2=9999999999`  
   - **Expected**: HTTP error code (400 or 404), no path found.  

3. **Missing Parameters**  
   - **Input**: `GET /quickest_path_system?landmark_1=300`  
   - **Expected**: HTTP error code or error message about missing parameters.  

4. **Format Override**  
   - **Input**: `GET /quickest_path_system?format=xml&landmark_1=123&landmark_2=456`  
   - **Expected**: Properly formatted XML with the correct path details.

### 6.2 Performance Test Cases

1. **Baseline Single Query**  
   - **Test**: Send a valid single request to measure response time.  
   - **Expected**: <1 second, logs any time above threshold as fatal.  

2. **Concurrent Queries**  
   - **Test**: Send multiple (e.g., 10–50) parallel requests to check for performance degradation.  
   - **Expected**: Each query should remain near the 1-second mark; if not, investigate.  

3. **CSV Verification**  
   - **Test**: Provide a large CSV (up to 30M lines if feasible) and measure time.  
   - **Expected**: Completes near 1 minute on typical hardware. If it stalls or far exceeds this, log fatal or non-fatal errors as appropriate.

### 6.3 Data Validation Test Cases

1. **Well-Formed CSV**  
   - **Data**: Proper DAG, no negative or zero weights, fully connected.  
   - **Expected**: “Validation Passed,” adjacency matrix created, no error logs.  

2. **Malformed CSV**  
   - **Data**: Negative/zero times, missing columns, duplicates.  
   - **Expected**: Tool fails gracefully or logs errors indicating invalid lines.  

3. **Disconnected Graph**  
   - **Data**: Large CSV missing connections between subsets of nodes.  
   - **Expected**: “Fatal” errors or a detailed message explaining disconnected components. -->

---

## 7. Testing Schedule

### 7.1 Timeline

- **Unit Tests**: Start week 3 as modules are developed (CSV parsing, pathfinding).  
- **Integration Tests**: Once data validation integrates with pathfinding.  
- **System Tests**: When the REST API is live, ensuring end-to-end coverage.  
- **Performance / Load Tests**: Closer to final delivery or after major optimization.  
- **Continuous Integration**: Every commit triggers unit + some integration tests in GitHub Actions.

### 7.2 Test Execution

- **Prioritization**: Fatal checks (e.g., correct output, no crashes) come first.  
- **Non-Fatal Warnings**: Logged but do not block merges unless they accumulate.  
- **Artifacts**: Each CI run logs results in real time for regression analysis.  
- **Local vs. Remote**: Developers may run smaller tests locally, with GitHub Actions providing a more standardized environment.

---

## 8. Risk Management

### 8.1 Testing Risks

- **Large Data Constraints**: Handling 24+ million nodes or verifying 30M lines is computationally heavy, potentially causing timeouts in CI or local environments.  
- **Edge Case Gaps**: Overly focusing on performance might skip testing rare or tricky scenarios, leading to hidden logic bugs.  

### 8.2 Contingency Plans

- **Performance Bottlenecks**: If queries exceed 1 second, refine heuristics or optimize data structures. Possibly segment CSV validation in chunks if 1-minute target is not met.  
- **Limited Resources**: Use scaled-down CSV subsets for daily CI runs, schedule monthly or milestone-based large-scale checks.  
<!-- - **Unexpected Errors**: Thorough logging in the adjacency matrix and pathfinding modules helps debug issues quickly. not correct? -->

---

## 9. Success Criteria

### 9.1 Performance Metrics

- **1-Second Query**: On typical laptop hardware, each path request must return within 1 second.  
- **10% Margin**: The returned path must not exceed 110% of the optimal route.  
- **CSV Verification**: Ideally completes in about 1 minute for ~30M lines, with a visible progress bar.  

### 9.2 Quality Metrics

- **Error Handling**: Fatal errors must be fixed before release. Non-fatal warnings are tracked and should be addressed promptly.  
- **Documentation**: Well-commented code, user manual, and up-to-date specifications ensure easy maintenance.  

---

## 10. Reporting

### 10.1 Test Results

- **GitHub Actions Logs**: Provide pass/fail and timing data.  
- **Issue Tracker**: Document all high-priority bugs and track their resolution.
- **Performance Logs**: Summaries of query response times and CSV validation durations.

### 10.2 Status Reports

- **Frequency**: Each push.  
- **Content**: Number of tests passing, open bugs, performance changes.  
- **Distribution**: Tech Lead, Software Engineer and Quality Assurance.

---

## 11. Approval & Sign-Off


- **Project Manager**: _______________________ *(Date: ________)  
- **Program Manager**: _______________________ *(Date: ________)  
- **Tech Lead**: _____________________________ *(Date: ________)  
- **Software Engineer**: _____________________ *(Date: ________)  
- **QA (Author)**: ___________________________ *(Date: ________)  
- **Technical Writer**: ______________________ *(Date: ________)  
