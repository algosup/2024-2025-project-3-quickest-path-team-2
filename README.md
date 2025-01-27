<h1 style="text-align: center">Team 2 - Quickest Path System</h1>
<br>

## 📖 About
Quickest Path System (or **QPS**) is a terminal program and was developed as a team project for ALGOSUP. It allows the user to find the quickest path in time from a landmark A to a landmark B.
<br>
These landmarks are the United States roads.

<details>
    <summary><b>Who are we?</b></summary>

|                                                                                              | Name                | Role                | Links |           
|----------------------------------------------------------------------------------------------|---------------------|---------------------|-------------------------------------------------------------------------------------------------------------------------|
| <img src="https://ca.slack-edge.com/T07N4K3NA3Z-U07NK3NMANP-gea5dac389e4-192" width="120px"> | LEFIN Mattéo        | **Project Manager**    | [LinkedIn](https://www.linkedin.com/in/matt%C3%A9o-lefin-380272293/)  \| [GitHub](https://github.com/Mattstar64)          |
| <img src="https://ca.slack-edge.com/T07N4K3NA3Z-U07NK6MCR0A-g4cac1c20a04-192" width="120px"> | ADAM Enoal          | **Program Manager**   | [LinkedIn](https://www.linkedin.com/in/enoal-adam-02552932a/)         \| [GitHub](https://github.com/EnoGame29)           |
| <img src="https://ca.slack-edge.com/T07N4K3NA3Z-U07P7V3H7ME-g3ffdd245b21-512" width="120px"> | DESPEAUX Guillaume  | **Technical Leader**     | [LinkedIn](https://www.linkedin.com/in/guillaume-despaux/)            \| [GitHub](https://github.com/GuillaumeDespaux)    |
| <img src="https://avatars.githubusercontent.com/u/145991354?v=4" width="120px"> | Mathis LEBEL  | **Software Engineer**| [LinkedIn](https://www.linkedin.com/in/mathis-lebel-429114293/)            \| [GitHub](https://github.com/mathislebel)    | 
| <img src="https://avatars.githubusercontent.com/u/146001004?s=64&v=4" width="120px">| RIFF Michel | **Quality Assurance** |[LinkedIn](https://www.linkedin.com/in/michel-riff-693007293/)            \| [GitHub](https://github.com/MichelRiff)    |
| <img src="https://avatars.githubusercontent.com/u/145991254?s=64&v=4" width="120px">| Gayat Camille | **Technical Writter** |[LinkedIn](https://www.linkedin.com/in/camille-g-a89114293/)            \| [GitHub](https://github.com/CamilleGayat)    |


</details>
<br>

## ⌨️ Programming language

This project has been conceived using the C++ programming language.
<br>
<br>

## ✏️ 📋 Details
We had approximately 5 weeks to complete the project, during which we implemented:

- A Data Verification tool

- A path finding algorithm 

- A REST API
<br>

The project was an excellent opportunity to understand how data structures and algorithms work which are essential in today's world.
<br>

## 🚀 How to launch the programs?

<details>
<summary>Requirements</summary>

### A compiler

First, ensure you have a compiler installed:

#### For MacOS
macOS comes with a pre-installed compiler. To verify:
- Open a terminal.
- Type the following command:
    - g++ --version

You should see output similar to this:

`yaml`

`Apple clang version 16.0.0 (clang-1600.0.26.6)
Target: arm64-apple-darwin24.2.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin`

- Ensure you see the line:
    - Apple clang version 16.0.0 (clang-1600.0.26.6)

- If the compiler is not installed, install Xcode Command Line Tools by running:
    - bash
    - xcode-select --install

#### For Windows

Windows does not have a built-in compiler. You will need to install MinGW (Minimalist GNU for Windows). Follow these steps:

- Download MinGW: Visit MinGW Installation Guide or download directly from SourceForge.

- Install MinGW:
During installation, ensure you select the options to install the C++ compiler.

- Add the bin directory of MinGW to your system’s PATH environment variable. This allows you to use the g++ command from any terminal.

- Verify Installation: Open Command Prompt and run:
    - g++ --version

You should see something like:

`csharp`

`g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0`
</details>

<details>
<summary>Launch the CSV Verification Code</summary>

### Launch the CSV Verification Code

#### For MacOS

- Navigate to the directory containing the source code:
    - cd src
- Compile the C++ verification program using clang++ or g++:<br>
    - g++ -o verification main_verification.cpp verification.cpp -std=c++17 -pthread
 - Run the compiled program:
    - ./verification
    <br><br>

#### For Windows

- Open a Command Prompt or Terminal and navigate to the directory containing the source code:
    - cd src
- Compile the C++ verification program using g++ (or your preferred compiler):
    - g++ -std=c++11 verification.cpp -o verification.exe
- Run the compiled program:
    - verification.exe

#### Additional Notes:
If you encounter any issues with the compiler setup on Windows, refer to the official
MinGW InstallationDocumentation.

On macOS, the default clang++ compiler supports the -std=c++11 flag, so no additional setup should be required.
</details>
<br>
<details>
<summary>Launch the quickest path system</summary>

### Launch the quickest path system

#### For MacOS

- Navigate to the directory containing the source code:
    - cd src
- Compile the C++ Quickest Path System program using clang++ or g++:<br>
    - g++ -o shortest_path main.cpp graph.cpp preprocessing.cpp -std=c++17 -pthread
 - Run the compiled program:
    - ./verification
    <br><br>

#### For Windows

- Open a Command Prompt or Terminal and navigate to the directory containing the source code:
    - cd src
- Compile the C++ verification program using g++ (or your preferred compiler):
    - g++ -std=c++11 main.cpp graph.cpp preprocessing.cpp -o shortest_path.exe
- Run the compiled program:
    - verification.exe


#### Steps to Compile and Run the Program

You can compile and run the program directly in the terminal of Visual Studio Code after cloning the repository:

- Open the repository folder in VS Code.
- Open the integrated terminal in VS Code (Ctrl+** on Windows/Linux, **Cmd+ on macOS).
- Compile the program:
    - g++ -std=c++11 main.cpp graph.cpp preprocessing.cpp -o shortest_path.exe
- Run the program:
    - ./verification

#### Additional Notes:
If you encounter any issues with the compiler setup on Windows, refer to the official
MinGW InstallationDocumentation.

On macOS, the default clang++ compiler supports the -std=c++11 flag, so no additional setup should be required.