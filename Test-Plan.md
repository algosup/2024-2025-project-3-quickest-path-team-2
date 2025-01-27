<br />
<div alig="center">
    <h1 align="center"> Test Plan </h1>
    <p align="center">
        <strong> Quickest Path in C++ - Team 2's project</strong>
        <br />

</div>
</br>

<details>
<summary>
      <h4 style="display: inline-block">Table of Contents</h4>
</summary>

- [1. Introduction](#1-introduction)
  - [1.1 Purpose](#11-purpose)
  - [1.2 Project Overview](#12-project-overview)
  - [1.3 Testing Scope](#13-testing-scope)
- [2. Test Strategy](#2-test-strategy)
  - [2.1 Testing Levels](#21-testing-levels)
    - [2.1.1 Unit Testing](#211-unit-testing)
    - [2.1.2 Integration Testing](#212-integration-testing)
    - [2.1.3 System Testing](#213-system-testing)
    - [2.1.4 Performance Testing](#214-performance-testing)
    - [2.1.5 API Testing](#215-api-testing)
  - [2.2 Testing Types](#22-testing-types)
    - [2.2.1 Functional Testing](#221-functional-testing)
    - [2.2.2 Performance Testing](#222-performance-testing)
    - [2.2.3 Data Integrity Testing](#223-data-integrity-testing)
    - [2.2.4 Regression Testing](#224-regression-testing)
  - [2.3 Testing Tools](#23-testing-tools)
- [3. Test Environment](#3-test-environment)
  - [3.1 Hardware Requirements](#31-hardware-requirements)
  - [3.2 Software Requirements](#32-software-requirements)
- [4. Test Deliverables](#4-test-deliverables)
  - [4.1 Test Documentation](#41-test-documentation)
  - [4.2 Test Reports](#42-test-reports)
- [5. Testing Areas](#5-testing-areas)
  - [5.1 REST API Testing](#51-rest-api-testing)
  - [5.2 Performance Testing](#52-performance-testing)
  - [5.3 Data Integrity Testing](#53-data-integrity-testing)
  - [5.4 Path Calculation Testing](#54-path-calculation-testing)
- [6. Test Cases](#6-test-cases)
- [7. Testing Schedule](#7-testing-schedule)
  - [7.1 Timeline](#71-timeline)
  - [7.2 Test Execution](#72-test-execution)
- [8. Risk Management](#8-risk-management)
  - [8.1 Testing Risks](#81-testing-risks)
  - [8.2 Contingency Plans](#82-contingency-plans)
- [9. Success Criteria](#9-success-criteria)
  - [9.1 Performance Metrics](#91-performance-metrics)
  - [9.2 Quality Metrics](#92-quality-metrics)
- [10. Reporting](#10-reporting)
  - [10.1 Test Results](#101-test-results)
  - [10.2 Status Reports](#102-status-reports)
- [11. Approval \& Sign-Off](#11-approval--sign-off)

 
</details>

---

## 1. Introduction

### 1.1 Purpose

In order to validate the **Quickest Path in C++** project, this document outlines an overarching strategy to ensure each software component meets its expected functionality, performance, and reliability. It also clarifies how issues will be reported, mitigated, and tracked, delivering maximum transparency to all stakeholders.

### 1.2 Project Overview

This project focuses on computing the quickest path between two landmarks within the United States. 
Implemented in C++, the application processes a large CSV file (*USA-roads.csv*) that contains landmark IDs and associated travel times. The system exposes a single REST API endpoint accepting a source and destination landmark, then returning the total travel time and the series of landmarks constituting the path. Given the data size of approximately 24 million nodes, performance optimization is paramount, and approximation heuristics are allowed as long as the travel time does not exceed 10% of the shortest possible route. 

Additionally, the project provides a data validation tool to confirm that the CSV file forms a Directed Acyclic Graph (DAG) and that the graph is fully connected. Verification of extremely large CSV files (e.g., up to 30 million lines) should ideally complete in about one minute. A progress bar in the command prompt will show the verification status, and if it remains stuck for more than 10 seconds, a warning is logged for potential issues.

Below is a simplified schematic of how CSV data flows through validation and graph-building processes to the REST API, which ultimately serves client requests:

```mermaid
flowchart LR
    A[USA-roads.csv] --> B[Data Validation Tool]
    B[Data Validation Tool] --> C[GraphBuilder]
    C[GraphBuilder] --> D[Pathfinding Logic]
    D[Pathfinding Logic] --> E[REST API Server]
    E[REST API Server] --> F[Client]
```

> [!NOTE]
> Verification of extremely large CSV files must complete in ~1 minute, with a command-line progress bar showing status. If no progress is detected after 10 seconds, a warning must appear.

### 1.3 Testing Scope

<p align="justify"> This Test Plan addresses: </p>
Data ingestion from CSV (including DAG verification, negative/zero time checks, and disconnected nodes)
Graph construction (adjacency matrix or alternative structure) ensuring memory/performance constraints
Pathfinding with heuristics that remain within 10% of the optimal route
REST API correctness and performance for queries
Edge-case scenarios like identical source/destination and malformed data
Tests for extremely large datasets may require specialized hardware or offline scheduling. Routine checks (smaller CSV subsets) will run on GitHub Actions, ensuring continuous validation for daily integration.

---

## 2. Test Strategy

### 2.1 Testing Levels

#### 2.1.1 Unit Testing 
   - Focuses on small modules—like CSV parsing or adjacency matrix building—verifying each function or class in isolation.

#### 2.1.2 Integration Testing 
   - Checks whether these individual modules work cohesively (e.g., validated data transferring seamlessly to the pathfinding algorithm).

#### 2.1.3 System Testing
   - Involves sending genuine queries to the REST API using real or mock CSV files, assessing end-to-end behavior.

#### 2.1.4 Performance Testing
   - Ensures large data sets can be processed swiftly, verifying the 1-second query response and ~1-minute CSV validation.

#### 2.1.5 API Testing
   - Specifically targets the single GET endpoint, ensuring correct input handling, JSON/XML response formats, and appropriate error codes for invalid parameters.

### 2.2 Testing Types

#### 2.2.1 Functional Testing
   - Checking if requirements—like generating a correct route or verifying CSV for negative times—are satisfied.

#### 2.2.2 Performance Testing
   - Ensures the system responds in under 1 second for typical queries.  
   - Confirms CSV verification can handle large files quickly (1 minute target for ~30M lines).  

#### 2.2.3 Data Integrity Testing 
   - Confirming the graph remains a DAG, ensuring no disconnected subgraphs or invalid fields.  

#### 2.2.4 Regression Testing
   - Runs automatically after each push to detect if any previously working functionality has broken. Re-running crucial tests after merges or fixes to prevent the reintroduction of old issues.

> [IMPORTANT]**Error Severity**  
> - **Fatal errors** (via `checkValue(int actual, int expected)`)  
>  Throw exceptions and halt the test. These must be fixed before release.  
>- **Non-fatal errors** (via `checkAndLog(int actual, int expected)`)  
>  Log warnings but let the test pipeline continue. These are tracked and should be resolved.

### 2.3 Testing Tools
- **C++17** for primary development.  
- **GitHub Actions** (Ubuntu-latest) for automated CI.   
- **cURL** or a custom C++ client for REST API testing (checking JSON vs. XML outputs).  
- **Additional Tools**:   Dedicated load-testing utilities for large-scale performance validation.

---

## 3. Test Environment

### 3.1 Hardware Requirements

<div align="center">
  <table>
    <thead>
      <tr>
        <th>Environment</th>
        <th>Hardware</th>
        <th>Comments</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>GitHub Actions (CI)</td>
        <td>2-core CPU, ~7 GB RAM, Ubuntu-latest runner</td>
        <td>Automated workflows on every push/PR</td>
      </tr>
      <tr>
        <td>Local Developer Machine</td>
        <td>≥8 GB RAM, modern multi-core CPU</td>
        <td>Enables debug builds, smaller CSV subsets</td>
      </tr>
      <tr>
        <td>High-Power Server (Optional)</td>
        <td>16+ GB RAM, multi-core CPU cluster</td>
        <td>For verifying 30M lines in ~1 minute, if needed</td>
      </tr>
    </tbody>
  </table>
</div>

### 3.2 Software Requirements

<p align="justify"> The QA pipeline relies on <strong>Ubuntu-latest</strong> for compiling and testing. The <em>g++ 9+</em> compiler is mandatory to ensure C++17 compliance. We do not depend on external libraries other than the STL and minimal HTTP libraries or frameworks for the REST server. Node.js (v20) is optionally configured on GitHub Actions if needed for script-based tasks. </p>

> [!NOTE] 
> Some local testing may take place on Windows 11 or macOS for compatibility checks, but official CI validation is done under Linux for consistency.

---

## 4. Test Deliverables

### 4.1 Test Documentation

Below are some examples of the parts QA will maintain:

<details> <summary><ins>Test Cases Inventory</ins></summary>
A living document enumerating each test with:

- Purpose and context
- Detailed setup instructions
- Expected outcome
- Severity classification (fatal vs. non-fatal)

This may be maintained in .md files or via a GitHub Issues “TestCase” template.

</details> <details> <summary><ins>CI Workflow Scripts</ins></summary>
The YAML configs that specify build steps (install g++, compile the code, run tests).
Also includes any specialized tasks, such as uploading artifacts or performance logs.

</details> <details> <summary><ins>Sample CSV Data</ins></summary>
A curated set of smaller CSV files (some valid, some intentionally malformed) for local quick runs and unit tests. For instance:

- mini_valid.csv: DAG with a few edges
- mini_invalid.csv: Negative times, disconnected subgraphs
- performance.csv: A scaled subset, taking the csv files from the requirements
</details>

### 4.2 Test Reports

<p align="justify"> After each test run on GitHub Actions (triggered by pushes or pull requests), a structured log is produced. This log details the build status, pass/fail statistics, and potential memory/performance data. The QA workflow can also be configured to send out automated emails with these results, summarizing pass/fail counts, coverage (if measured), and direct links to the relevant logs or artifacts. </p>

> [!NOTE] 
> Failure escalation can be configured so that when a workflow fails, key stakeholders receive real-time notifications (email, Slack, etc.). If consistent failures arise, a summary email or issue is automatically created highlighting repeated or high-severity issues.

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

This section provides a comprehensive set of test cases covering CSV validation, REST API functionality, performance thresholds, data integrity, pathfinding correctness, and edge scenarios. Each test scenario outlines the specific purpose, environment needs, steps, and expected outcomes. In practice, these test may be stored as individual files in the QA folder, or as GitHub Issues referencing the relevant scenario.

<details>
<summary><strong>6.1 CSV Validation Tests</strong></summary><br/>

**<ins>Test Case #CV-1: Negative or Zero Times</ins>**  
- **Goal**: Confirm that lines with negative or zero travel times are flagged as fatal errors.  
- **Preconditions**: The project is compiled, and a CSV file named `MixedValidity.csv` (or any file known to contain negative/zero times) is in the `/src/data` directory.  
- **Steps**:  
  1. Run the data validation tool on `MixedValidity.csv`.  
  2. Observe the console output.  
- **Expected**:  
  - The tool logs an error message indicating a negative/zero time was detected.  
  - The validation process exits with a fatal status (cannot proceed).  

<br/>

**<ins>Test Case #CV-2: Duplicate Lines</ins>**  
- **Goal**: Ensure that repeated connections (e.g., `7,8,5822` duplicated) are identified and handled.  
- **Preconditions**: The CSV file contains at least one pair of identical lines.  
- **Steps**:  
  1. Execute the validation tool on a CSV with duplicates.  
  2. Monitor the console for warnings or errors.  
- **Expected**:  
  - The tool either flags a warning or merges duplicates gracefully, depending on design.  
  - Duplicate lines do not crash or stall the validation.  

<br/>

**<ins>Test Case #CV-3: Missing Landmarks or Time</ins>**  
- **Goal**: Confirm that CSV lines lacking either the first landmark, second landmark, or time field produce an error.  
- **Preconditions**: CSV file with lines like `,16,34871` or `16,17,` or incomplete columns.  
- **Steps**:  
  1. Run the validation tool on the malformed CSV.  
  2. Observe output for error handling.  
- **Expected**:  
  - Missing fields cause the tool to log a fatal error, halting validation.

<br/>

**<ins>Test Case #CV-4: Large CSV Performance Check</ins>**  
- **Goal**: Validate that processing ~30 million lines completes in ~1 minute on recommended hardware.  
- **Preconditions**: A large synthetic or real CSV file is available; environment must meet minimal hardware specs.  
- **Steps**:  
  1. Provide the large CSV to the validation tool.  
  2. Start a timer and verify the progress bar updates regularly.  
  3. Check final completion time.  
- **Expected**:  
  - Validation finishes in around 60 seconds.  
  - Progress bar never remains stuck for >10s.  

<br/>

**<ins>Test Case #CV-5: Disconnected Graph Detection</ins>**  
- **Goal**: Check whether data validation flags CSV data that fails connectivity (e.g., separate clusters).  
- **Preconditions**: CSV with at least two disconnected subgraphs.  
- **Steps**:  
  1. Run the validation tool on the CSV with disjoint sets of landmarks.  
  2. Observe if the tool logs a connectivity error.  
- **Expected**:  
  - Tool logs “Graph is not fully connected” or an equivalent error.  
  - Validation fails (cannot proceed to pathfinding).  

</details>

<details>
<summary><strong>6.2 REST API Tests</strong></summary><br/>

**<ins>Test Case #API-1: Valid Query (JSON)</ins>**  
- **Goal**: Confirm that a valid GET request returns a JSON response with the correct time and path.  
- **Preconditions**: A properly validated CSV is loaded, server is running on `localhost:8080`.  
- **Steps**:  
  1. `GET /quickest_path_system?format=json&landmark_1=100&landmark_2=200`  
  2. Check response time and format.  
- **Expected**:  
  - 200 OK status, JSON body including `"time": <int>` and `"steps": [...]` structure.  
  - Response under 1 second for typical queries.

<br/>

**<ins>Test Case #API-2: Valid Query (XML)</ins>**  
- **Goal**: Ensure that XML output is correct when format=xml is requested.  
- **Preconditions**: Same environment as above.  
- **Steps**:  
  1. `GET /quickest_path_system?format=xml&landmark_1=123&landmark_2=456`  
  2. Observe the returned XML.  
- **Expected**:  
  - Well-formed XML with root `<response>` tag, `<time>` element, and `<steps>` sub-elements.  
  - Completion under 1 second.  

<br/>

**<ins>Test Case #API-3: Invalid Landmark IDs</ins>**  
- **Goal**: Confirm the server gracefully handles requests where the landmarks are out of range or missing.  
- **Preconditions**: CSV loaded, server is listening.  
- **Steps**:  
  1. `GET /quickest_path_system?format=json&landmark_1=-1&landmark_2=9999999999`  
  2. Check HTTP response code and body.  
- **Expected**:  
  - Possibly `400 Bad Request` or `404 Not Found`, with a short message stating the request is invalid.  
  - The server must not crash.  

<br/>

**<ins>Test Case #API-4: Missing Parameters</ins>**  
- **Goal**: Verify incomplete queries produce a proper error rather than a silent fail.  
- **Preconditions**: Normal environment.  
- **Steps**:  
  1. `GET /quickest_path_system?landmark_1=300` with no `landmark_2`.  
  2. Observe the result.  
- **Expected**:  
  - HTTP error code (400 or 422), with a message about missing parameters.  

<br/>

**<ins>Test Case #API-5: Concurrent Requests</ins>**  
- **Goal**: Measure how multiple simultaneous GET queries behave, checking for timeouts or performance dips.  
- **Preconditions**: Possibly use a concurrency tool or custom script.  
- **Steps**:  
  1. Send 10–50 parallel GET requests with valid parameters.  
  2. Track average response time, success/failure rates.  
- **Expected**:  
  - Majority of responses complete in <1 second.  
  - No deadlocks or crashes occur, though some slight overhead is acceptable.

</details>

<details>
<summary><strong>6.3 Performance Tests</strong></summary><br/>

**<ins>Test Case #PT-1: Single Query Baseline</ins>**  
- **Goal**: Validate that an average query completes under 1 second on typical hardware.  
- **Preconditions**: The server is running with a mid-sized CSV (1–5 million lines).  
- **Steps**:  
  1. Issue a GET request from cURL or Postman to the path endpoint.  
  2. Record the time from request to first byte or full response.  
- **Expected**:  
  - 95%+ of queries respond under 1 second.  

<br/>

**<ins>Test Case #PT-2: Extended Load Simulation</ins>**  
- **Goal**: Check if repeated queries (e.g., 100 requests in quick succession) degrade the server’s performance.  
- **Preconditions**: Use a simple script or load tool like `ab` (ApacheBench) or `hey`.  
- **Steps**:  
  1. Launch 100–200 requests, each to a typical path (e.g., `landmark_1=50,landmark_2=900`).  
  2. Collect average and 95th percentile response times.  
- **Expected**:  
  - No meltdown or out-of-memory errors.  
  - Mean response near 1 second, 95th percentile under 2 seconds.  

<br/>

**<ins>Test Case #PT-3: CSV Verification Throughput</ins>**  
- **Goal**: Confirm the validation tool processes ~30 million lines in about 1 minute.  
- **Preconditions**: High-powered local or cloud environment, large CSV.  
- **Steps**:  
  1. Time the validation run from start to finish.  
  2. Watch the command prompt progress bar for any stalls.  
- **Expected**:  
  - Completion near 1 minute.  
  - No stalls >10 seconds.  

</details>

<details>
<summary><strong>6.4 Data Integrity Tests</strong></summary><br/>

**<ins>Test Case #DI-1: DAG Enforcement</ins>**  
- **Goal**: Ensure no cycles are permitted in the CSV’s adjacency data.  
- **Preconditions**: A CSV intentionally containing loops (e.g., `9,9,7211` or circular references among 3 landmarks).  
- **Steps**:  
  1. Run the validation tool.  
  2. Monitor logs or final pass/fail status.  
- **Expected**:  
  - Detection of a loop yields a fatal error.  

<br/>

**<ins>Test Case #DI-2: Connectivity Verification</ins>**  
- **Goal**: Confirm the CSV forms a single connected component, no isolated clusters.  
- **Preconditions**: CSV with multiple subgraphs or well-formed single subgraph.  
- **Steps**:  
  1. Execute the validation tool.  
  2. If the graph is not fully connected, check for relevant error messages.  
- **Expected**:  
  - Non-connected data is flagged.  
  - Fully connected data passes.  

<br/>

**<ins>Test Case #DI-3: Adjacency Matrix Consistency</ins>**  
- **Goal**: Confirm that each valid CSV line properly populates the adjacency matrix (or adjacency list) without duplicates or overwrites.  
- **Preconditions**: CSV with known pairs.  
- **Steps**:  
  1. Run validation in debug mode or with logging.  
  2. Check logs to confirm each line is mapped correctly.  
- **Expected**:  
  - Each entry is inserted once, no collisions or mismatches.  

</details>

<details>
<summary><strong>6.5 Path Calculation Tests</strong></summary><br/>

**<ins>Test Case #PC-1: Basic Shortest Path</ins>**  
- **Goal**: Ensure a known small graph returns the exact shortest route.  
- **Preconditions**: Replace large CSV with a tiny test CSV (e.g., 5–10 edges) whose best path is known.  
- **Steps**:  
  1. Run server with the small CSV.  
  2. Query the path from `1` to `5`.  
  3. Compare returned steps/time to the known optimal route.  
- **Expected**:  
  - The route matches the known minimal cost.  
  - The time is within 0–10% of the known best path (in this case, it should be exact if the graph is small).

<br/>

**<ins>Test Case #PC-2: 10% Approximation Check on Large Graph</ins>**  
- **Goal**: Verify that with heuristics enabled, the route does not exceed 110% of the absolute shortest path.  
- **Preconditions**: A CSV where we can approximate the true shortest path or have an authoritative reference.  
- **Steps**:  
  1. Query a path that might have multiple routes (e.g., `landmark_1=1000, landmark_2=2000`).  
  2. Compare the returned travel time to the best known route.  
- **Expected**:  
  - The system does not exceed 110% of the known optimal.  

<br/>

**<ins>Test Case #PC-3: Source == Destination</ins>**  
- **Goal**: Confirm that if the same landmark is used for start and end, the travel time is `0`, and the route is trivially that single landmark.  
- **Preconditions**: The CSV is valid.  
- **Steps**:  
  1. `GET /quickest_path_system?format=json&landmark_1=500&landmark_2=500`  
- **Expected**:  
  - The JSON or XML returns `"time": 0` and steps of length 1 (just `500`).  

<br/>

**<ins>Test Case #PC-4: Nonexistent Path</ins>**  
- **Goal**: Confirm that the system returns an error or “no path found” if the landmarks are unreachable.  
- **Preconditions**: CSV with at least two disconnected clusters.  
- **Steps**:  
  1. Query a path bridging disconnected nodes.  
  2. Observe error message or code.  
- **Expected**:  
  - HTTP 404 or an error body stating no path is available.  

<br/>

**<ins>Test Case #PC-5: Large Node IDs with Realistic Times</ins>**  
- **Goal**: Confirm the system can handle queries for high-range landmarks (e.g., 20 million) in the CSV index.  
- **Preconditions**: A CSV file enumerating node IDs that go up to ~20 million or more.  
- **Steps**:  
  1. Query a valid route that uses high IDs.  
  2. Ensure system responds in <1 second.  
- **Expected**:  
  - Proper route is returned.  
  - No integer overflow or array-bound errors.  

</details>

<details>
<summary><strong>6.6 Edge & Special Cases</strong></summary><br/>

**<ins>Test Case #EC-1: Progress Bar Idle</ins>**  
- **Goal**: Check the command-line progress bar for CSV validation logs a warning if it remains idle for >10 seconds.  
- **Preconditions**: CSV validation is started with a massive or artificially throttled read.  
- **Steps**:  
  1. Launch the validation tool with environment constraints that slow I/O.  
  2. Monitor whether the progress bar prints a “Warning: No progress in 10 seconds” or similar.  
- **Expected**:  
  - A warning is visible if the progress bar doesn’t update.  

<br/>

**<ins>Test Case #EC-2: Self-Loop Landmark</ins>**  
- **Goal**: Confirm that lines referencing the same node as source and destination (e.g., `9,9,7211`) yield a validation failure.  
- **Preconditions**: CSV with a self-loop entry.  
- **Steps**:  
  1. Run validation.  
  2. Check logs for “Loop Detected.”  
- **Expected**:  
  - Fatal error; cannot proceed to pathfinding.  

<br/>

**<ins>Test Case #EC-3: Minimal CSV with One Edge</ins>**  
- **Goal**: Confirm the system can handle extremely small input with just one connection.  
- **Preconditions**: A CSV containing something like `1,2,100`.  
- **Steps**:  
  1. Validate CSV (should pass).  
  2. Launch server, query from 1 to 2.  
- **Expected**:  
  - 200 OK, time = 100, steps = [1,2].  

<br/>

**<ins>Test Case #EC-4: Repeated Large Queries</ins>**  
- **Goal**: Evaluate whether sending a large volume of queries (e.g., 1000 consecutive requests) eventually exhausts resources or times out.  
- **Preconditions**: The server is compiled with optimizations.  
- **Steps**:  
  1. Use a script to call the REST endpoint 1000 times.  
  2. Observe memory usage or CPU spikes.  
- **Expected**:  
  - No memory leaks, no crash, consistent sub-second or near-sub-second responses.

<br/>

**<ins>Test Case #EC-5: Handling of Extremely High Times**  
- **Goal**: Confirm the system can parse and store large time values (e.g., 1,000,000).  
- **Preconditions**: CSV lines with large integers for travel times.  
- **Steps**:  
  1. Validate the CSV.  
  2. Query any path that includes these edges.  
- **Expected**:  
  - No overflow.  
  - The path is correctly calculated using large weights.

</details>

---

## 7. Testing Schedule

### 7.1 Timeline


<table>
  <thead>
    <tr>
      <th style="text-align: center;">Phase</th>
      <th style="text-align: center;">Scope</th>
      <th>Approx. Date</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align: center;">Unit Testing</td>
      <td>CSV parser, adjacency matrix builder, pathfinding algorithm</td>
      <td style="text-align: center;">Weeks 3-4</td>
    </tr>
    <tr>
      <td style="text-align: center;">Integration</td>
      <td>Data validation tool + pathfinder + partial CSV usage</td>
      <td style="text-align: center;">Week 4</td>
    </tr>
    <tr>
      <td style="text-align: center;">System Tests</td>
      <td>End-to-end verification with a real or moderately sized CSV (~1M lines)</td>
      <td style="text-align: center;">Weeks 3-4</td>
    </tr>
    <tr>
      <td style="text-align: center;">Performance</td>
      <td>Stress tests, 24+ million nodes if feasible, 1-second path queries check</td>
      <td style="text-align: center;">Weeks 4-5</td>
    </tr>
    <tr>
      <td style="text-align: center;">Final QA</td>
      <td>Polishing, final regression checks, sign-off for release</td>
      <td style="text-align: center;">Week 5</td>
    </tr>
  </tbody>
</table>


### 7.2 Test Execution

- **Prioritization**: Fatal checks (e.g., correct output, no crashes) come first.  
- **Non-Fatal Warnings**: Logged but do not block merges unless they accumulate.  
- **Artifacts**: Each CI run logs results in real time for regression analysis.  
- **Local vs. Remote**: Developers may run smaller tests locally, with GitHub Actions providing a more standardized environment.

---

## 8. Risk Management

### 8.1 Testing Risks

<table>
  <thead>
    <tr>
      <th>Potential Risk or Issue</th>
      <th>Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Resource Limitations</td>
      <td>Standard GitHub Actions runners might timeout or run out of memory while verifying extremely large CSV inputs.</td>
    </tr>
    <tr>
      <td>Late-Found Bugs</td>
      <td>If performance issues or major disconnections are discovered close to final release, schedule pressure may hamper thorough fixes.</td>
    </tr>
    <tr>
      <td>Insufficient Edge Testing</td>
      <td>Overemphasis on performance or mainline scenarios might miss obscure edge cases.</td>
    </tr>
  </tbody>
</table>

### 8.2 Contingency Plans

- **Performance Bottlenecks**: If queries exceed 1 second, refine heuristics or optimize data structures. Possibly segment CSV validation in chunks if 1-minute target is not met.  
- **Limited Resources**: Use scaled-down CSV subsets for daily CI runs, schedule weekly or milestone-based large-scale checks.  

---

## 9. Success Criteria

### 9.1 Performance Metrics

- **1-Second Query**: On typical laptop hardware, each path request must return within 1 second.  
- **10% Margin**: The returned path must not exceed 110% of the optimal route.  
- **CSV Verification**: Ideally completes in about 1 minute for ~30M lines, with a visible progress bar.  

### 9.2 Quality Metrics

- **No Blocking (Fatal) Bugs**: Prior to release, all fatal issues must be addressed. Non-fatal ones are prioritized by severity and tracked if they do not jeopardize final stability.
- **Documentation**: Code must remain well-commented and consistent with technical specs. The user manual and readme must accurately reflect final usage instructions.

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
