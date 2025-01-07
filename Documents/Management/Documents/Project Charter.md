# Project Charter

---

## <u>Project : Quickest Path</u> 

### Purpose

The objective of this project is to develop a <u>high-performance software solution</u> that calculates the <u>quickest path between two landmarks in the United States of America</u>.

### Description


### Objectives

- Develop the project using C++ programing language for optimal performance.
- Use the provided DataSource for Landmarks.
- The software will expose its functionality through a REST API running on an HTTP server (localhost) The API will include a single GET endpoint with the following features: 
    - Input: IDs of the source and destination landmarks. 
    - Output: Travel time and the ordered list of landmarks in the path. 
    - Response Formats: Support both XML and JSON for response payloads. . 
- The API must handle all queries within 1 second on a typical laptop.

### Project Specification

- A DataSource indicating the different posibilities of landmark A's and B's
- Develop an Algorithm that will select the quickest path using the DataSource.


### Deliverables

| Name                               | Type                | Deadline     |
| ---------------------------------- | ------------------- | ------------ |
| Functional Specifications Document | Document (markdown) | 02/07/2025   |
| Technical Specifications Document  | Document (markdown) | 02/07/2025   |
| Weekly Reports                     | Document (markdown) | Every Friday evening |
| Test Plan                          | Document (markdown) | 02/07/2025   |
| User Manual                        | Document (markdown) | 02/07/2025
| Final Product                      | Program             | 02/07/2025   |

### Project Scope

| In Scope                         |
| -------------------------------- |
|Time and Space Complexity: Big O notation for the main algorithms.|
|REST API Implementation: Demonstrating the ability to handle multiple formats (XML and JSON). |
|Test Suite: Tests to validate correctness, performance, and compliance with the 10% approximation rule. |
|Data Validation Tool: A utility to verify the integrity of the provided CSV file. 


| Out of Scope                            |
| --------------------------------------- |
| Http design|
|

### Projects Milestones

| Milestone                | Deadline  |
| ------------------------ | --------- |
| End of the project       | 02/07/2025|

### Roles and Responsabilities

| Name                      | Role                     | Image                                                                           | Link                                                           | Responsabilities                                                                                                                                                                                                              |
| ------------------------- | ------------------------ | ------------------------------------------------------------------------------- | -------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Mattéo LEFIN**          | <u>Project Manager</u>   | [<img src="https://avatars.githubusercontent.com/u/146164921?v=4" width="75px">](https://github.com/Mattstar64)  | [Matteo\'s Github Profile](https://github.com/Mattstar64)      | The Project Manager will <u>plan and develop the project ideas</u> and also <u>monitor Project Progress, set Deadlines and solves issue that may possibly arise</u>                                                           |
| **Enoal ADAM**           | <u>Program Manager</u>   | [<img src="https://avatars.githubusercontent.com/u/182214526?s=64&v=4" width="75px">](https://github.com/EnoGame29) | [Enoal's Github Profile](https://github.com/EnoGame29)       | The Program Manager will <u>plan and design the program</u> and proactively <u>monitor its progress</u>, <u>resolving issues and initiating appropriate corrective actions</u>.                                      |
| **Guillaume DESPAUX**           | <u>Technical Leader</u>         | [<img src="https://avatars.githubusercontent.com/u/146001117?s=64&v=4" width="75px">](https://github.com/GuillaumeDespaux)   | [Guillaume's Github Profile](https://github.com/GuillaumeDespaux)      | The Technical Leader will <u>oversee the technical aspects of the software engineering team by making architectural and design decisions</u>, <u>guiding team members in technical matters</u>, and <u>supervising system modifications</u>. |
| **Mathis LEBEL** | <u>Software Engineer</u> | [<img src="https://avatars.githubusercontent.com/u/145991354?v=4" width="75px"> ](https://github.com/mathislebel)  | [Mathis Github Profile](https://github.com/mathislebel)       | The Software Engineer will <u>program the software</u> on the decided program languages.|
| **Michel Riff**         | <u>Quality Assurance</u> | [<img src="https://avatars.githubusercontent.com/u/146001004?s=64&v=4" width="75px">](https://github.com/MichelRiff)  | [Michel's Github Profile](https://github.com/MichelRiff)    | The Quality Assurance will <u>ensure that the product meets the established quality standard and industry benchmarks</u>.|
| **Camille GAYAT**      | <u>Technical Writter</u> | [<img src="https://avatars.githubusercontent.com/u/145991254?v=4" width="75px">](https://github.com/CamilleGayat)  | [Camille's Github Profile](https://github.com/CamilleGayat)     | The Technical Writter will <u>create a user-friendly document that explains how to use the product and some technical information to it</u>.                                                                                                                 |