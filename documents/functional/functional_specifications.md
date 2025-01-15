<div align="center">

# Functional Specifications

---

**Project** : Quickest Path <br>
**Team** : 2 <br>
**Created by** : Enoal ADAM <br>
**Creation Date** : 01/06/2024 <br>
**Updated** : 01/06/2024 <br>

---

</div>

<details>
<summary>Table of Contents</summary>

- [Functional Specifications](#functional-specifications)
  - [1.Introduction](#1introduction)
    - [1.1 Project Overview](#11-project-overview)
    - [1.2 Document Purpose](#12-document-purpose)
    - [1.3 Personas](#13-personas)
    - [1.4 Stakeholders and Representatives](#14-stakeholders-and-representatives)
  - [2. Application Overview](#2-application-overview)
    - [2.1 What is our software used for?](#21-what-is-our-software-used-for)
    - [2.2 What the application used to work?](#22-what-the-application-used-to-work)
  - [3. Hardware/Software](#3-hardwaresoftware)
    - [3.1 Hardware](#31-hardware)
    - [3.2 Software](#32-software)
    - [3.3 Signature](#33-signature)
  - [4. How to use it?](#4-how-to-use-it)
  - [5. Platforms compatibility](#5-platforms-compatibility)
    - [5.1 Windows](#51-windows)
    - [5.2 MacOS](#52-macos)
  - [6. Non-functional requirements](#6-non-functional-requirements)
    - [6.1 Response/Performance \& Reliability](#61-responseperformance--reliability)
    - [6.2 Testability](#62-testability)
    - [6.3 Flexibility](#63-flexibility)
  - [7. Future improvements](#7-future-improvements)
  - [8. Complementary Information](#8-complementary-information)
  - [Glossary](#glossary)

</details>

## 1.Introduction

This document is the functional specifications of the 3rd Project of the year called Quickest Path. You can found bellow the name and the role of each member of the team:

| Name              | Role              | Description                                                                                                                                                                              | GitHub Link | LinkedIn Link |
| ----------------- | ----------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------- | ------------- |
| Mattéo LEFIN      | Project Manager   | Responsible for project management, including timelines, planning, and team coordination. Have a role in the choices of the functional aspects of the project                            | link        | link          |
| Enoal ADAM        | Program Manager   | Decides of the functional aspects of the project, interfaces and so on. Manages functional specification development and client communication for the project.                           | link        | link          |
| Guillaume DESPAUX | Technical Leader  | Guides technical decisions and translates functional requirements into scalable technical solutions. Choices the coding standards, how the language will be use into the project.        | link        | link          |
| Mathis LEBEL      | Software Engineer | Develops and implements codebase, ensures code quality and is governed by technical aspects to create the software.                                                                      | link        | link          |
| Michel RIFF       | Quality Assurance | Creates tests to validate the quality of the software, that is to say, search for any types of problems, find how to optimize the code and report these issues to the Software Engineer. | link        | link          |
| Camille GAYAT     | Technical Writer  | Creates an understandable end-user documentation to facilitate the usage of the software.                                                                                                | link        | link          |

### 1.1 Project Overview

The aim of the project is to create a software that find the quickest path between two landmarks in the United States. To achieve this request, we have to use the C++ language[^1]. We decide to name our software "QPS", aka "Quickest Path System", a played of words among GPS "Global Positioning System" and the name of the project "Quickest Path".

### 1.2 Document Purpose

This document is here to provide all the functional specification of the project. We will cover topics such as who is able to use the software, how you can use the software (briefly), how it functionally works and the features we decide to skip for now but which can be implemented later.
If you reach for technical aspects of the project, such as how the C++ works, the project conventions, how the algorithm is use specifically, please refer you to the [technical specification](../technical/technical_specification.md)

### 1.3 Personas

**Workers** : All the workers who use an application to commute in order to avoid traffic jams and take the shortest/quickest route.
**Travel buffs** : Persons who love travel around his country or the world and want to find the quickest way to go to his destination.
**Map enthusiasts** : All the people who adore maps and love being part of a user community for a specific application.

### 1.4 Stakeholders and Representatives

| Representative           | Role   | Expectation                                                  |
| ------------------------ | ------ | ------------------------------------------------------------ |
| Franck JEANNIN (ALGOSUP) | Client | Project timelines respected and a usable software at the end |

## 2. Application Overview

In this section, we will talk about the software (in broad outline). To do this, some technical terms are going to be employed to ensure the consistency of the explanations. If you don't know the used worlds, you can take a gaze to the Glossary at the end (by the little chips next to them).

### 2.1 What is our software used for?<!--Like a GPS to move between 2 points-->

The software is a GPS like, a software that use some algorithms[^2] to define for you the quickest path between two points, landmarks to be precise. When you start it, after some verifications on our side, it will be ask you to enter your current place and where you want to go. The answer will be send in a specific format (JSON[^3] or XML[^4]) and you will be able to know the optimized path.
To know the error rate or any percentage directly link to a performance section, please look at [3.1 Hardware](#31-hardware).

### 2.2 What the application used to work?<!--The Algorithm (can be explained with a graph), the code (language) and more-->

To operate, the software is based on algorithms, a finite sequence of specific instructions, the Dijkstra[^5] one. Here is a graph to explain how the algorithm works:
<center>

![Dijkstra Algorithm](..\images\functional\Disjktsra_Algorithm.gif) </center>

The final result looks like this --> <img src="..\images\functional\Final_Dijkstra.png" alt="Dijkstra Final Path" style="width: 250px">

Since this algorithm is needed to be implement by each person when he created his code to use it, we decided to code ours using the C++ language[^6].

## 3. Hardware/Software<!--Can be more precise-->

### 3.1 Hardware<!--Might be a performance section-->

### 3.2 Software<!--Can be "User interface (UI)" for the Software ; UI is a nice to have but we have already the plan-->

### 3.3 Signature<!--What I made Friday-->

## 4. How to use it?<!--How to use it briefly (use the CMD e.g.) but not how use it clearly-->

## 5. Platforms compatibility<!--Platforms where the software are used and sure to be used on-->

<!--Can transform the following under-titles in a array ; ALSO, indicate that the mobile platforms won't be compatible with the software for now-->

### 5.1 Windows

### 5.2 MacOS

## 6. Non-functional requirements

### 6.1 Response/Performance & Reliability

### 6.2 Testability<!--Redirecting through the Test plan is a good thing-->

### 6.3 Flexibility<!--The possibility to implement/improve our software ; can indicate that i'm going to develop on the Future Improvement just after-->

## 7. Future improvements

## 8. Complementary Information<!--Link to the others doc-->

## Glossary