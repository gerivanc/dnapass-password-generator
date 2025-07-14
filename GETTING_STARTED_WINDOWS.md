# Getting Started with DNAPass Password Generator on Windows

Welcome to the **DNAPass Password Generator**, a secure and customizable tool for generating robust passwords inspired by DNA sequences! This guide provides step-by-step instructions for installing and using the **DNAPass Password Generator** on Windows using a command-line interface (CLI). Whether you're securing personal accounts or generating cryptographic keys, this guide will help you get started quickly and efficiently.

---

## 📋 Prerequisites

Before diving in, ensure your Windows environment is ready:

- **Operating System**: Windows 10 or later.
- **C++ Compiler**: A C++17-compliant compiler, such as MinGW (with `g++`) or Microsoft Visual Studio (with `cl`). Download options:
  - **MinGW**: Available from [MinGW-w64](https://www.mingw-w64.org/) or via a package manager like `choco` (`choco install mingw`).
  - **MSVC**: Included in Visual Studio with the C++ development workload, downloadable from [visualstudio.microsoft.com](https://visualstudio.microsoft.com).
- **Git**: Required for cloning the repository. Download from [git-scm.com](https://git-scm.com/download/win).
- **Internet Connection**: Required for cloning the repository from GitHub.

---

## 🛠️ Installation

The **DNAPass Password Generator** is built in C++ and requires compilation from source code. Below are the steps to install and compile the project on Windows.

1. **Install Git**:
   - **Download Git**: Visit [git-scm.com](https://git-scm.com/download/win) and download the latest version of Git for Windows.
   - **Run the Installer**:
     - Follow the installation wizard, accepting the default settings unless you have specific preferences.
     - Ensure the option “Add Git to PATH” is selected (usually enabled by default) to make Git accessible in Command Prompt or PowerShell.
   - **Verify Git Installation**:
     Open Command Prompt (`cmd`) or PowerShell and run:
     ```powershell
     git --version
     ```
     If installed correctly, you’ll see output like `git version 2.x.x`. If you get an error (e.g., `'git' is not recognized`), ensure Git was added to your system PATH. You can fix this by reinstalling Git and selecting the “Add Git to PATH” option, or manually adding the Git executable path (e.g., `C:\Program Files\Git\bin`) to your system’s environment variables:
     - Press `Win + R`, type `sysdm.cpl`, and go to **Advanced > Environment Variables**.
     - Under **System Variables**, find `Path`, edit it, and add the Git bin directory (e.g., `C:\Program Files\Git\bin`).

2. **Install a C++ Compiler**:
   - **Option 1: MinGW**:
     - Download and install MinGW-w64 from [MinGW-w64](https://www.mingw-w64.org/) or via a package manager like Chocolatey:
       ```powershell
       choco install mingw
       ```
     - Verify installation:
       ```powershell
       g++ --version
       ```
       Ensure the output shows a version supporting C++17 (e.g., GCC 7.0+).
   - **Option 2: MSVC (Visual Studio)**:
     - Download and install Visual Studio from [visualstudio.microsoft.com](https://visualstudio.microsoft.com).
     - During installation, select the “Desktop development with C++” workload.
     - Verify installation by opening the **Developer Command Prompt for Visual Studio** and running:
       ```powershell
       cl
       ```

3. **Clone the Repository**:
   In Command Prompt or PowerShell, navigate to a directory where you want to store the project (e.g., `C:\Projects`):
   ```powershell
   git clone https://github.com/gerivanc/dnapass-password-generator.git
   cd dnapass-password-generator
